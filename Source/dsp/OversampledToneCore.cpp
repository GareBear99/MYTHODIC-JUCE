#include "OversampledToneCore.h"
#include "../util/ParameterLayout.h"
#include <cmath>

namespace mythodic::dsp
{
    void OversampledToneCore::prepare (double sampleRate, int samplesPerBlock, int numChannels)
    {
        sampleRate_ = sampleRate;
        blockSize_ = samplesPerBlock;
        channels_ = numChannels;
        rebuildOversamplingIfNeeded();

        juce::dsp::ProcessSpec spec { sampleRate_, static_cast<juce::uint32> (blockSize_), static_cast<juce::uint32> (channels_) };
        preGain_.prepare (spec);
    }

    void OversampledToneCore::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        driveDb_          = apvts.getRawParameterValue (mythodic::params::toneDriveDb)->load();
        toneMix_          = apvts.getRawParameterValue (mythodic::params::toneMix)->load();
        toneMode_         = static_cast<int> (apvts.getRawParameterValue (mythodic::params::toneMode)->load());
        oversampleChoice_ = static_cast<int> (apvts.getRawParameterValue (mythodic::params::oversampleMode)->load());
        preGain_.setGainDecibels (driveDb_);
        rebuildOversamplingIfNeeded();
    }

    void OversampledToneCore::rebuildOversamplingIfNeeded()
    {
        const int factorPow = oversampleChoice_ == 1 ? 1 : oversampleChoice_ == 2 ? 2 : oversampleChoice_ == 3 ? 3 : 2;
        if (factorPow == lastFactorPow_ && oversampling_)
            return;

        lastFactorPow_ = factorPow;
        oversampling_ = std::make_unique<juce::dsp::Oversampling<float>> (
            static_cast<size_t> (channels_),
            static_cast<size_t> (factorPow),
            juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR,
            true);

        oversampling_->reset();
        oversampling_->initProcessing (static_cast<size_t> (blockSize_));
    }

    float OversampledToneCore::shapeSample (float x) const noexcept
    {
        switch (toneMode_)
        {
            case 0: return std::tanh (0.95f * x);
            case 1: return std::tanh (1.35f * x);
            case 2: return 0.75f * std::sin (x) + 0.45f * std::tanh (1.15f * x);
            default: return x;
        }
    }

    void OversampledToneCore::process (juce::dsp::AudioBlock<float> block, const DecisionFrame& decisions)
    {
        juce::dsp::ProcessContextReplacing<float> context (block);
        preGain_.process (context);

        auto up = oversampling_->processSamplesUp (block);
        const float enrich = 1.0f + 0.45f * decisions.fuse + 0.20f * decisions.density;

        for (size_t ch = 0; ch < up.getNumChannels(); ++ch)
        {
            auto* s = up.getChannelPointer (ch);
            for (size_t i = 0; i < up.getNumSamples(); ++i)
            {
                const float dry = s[i];
                const float wet = shapeSample (dry * enrich);
                s[i] = dry + (wet - dry) * toneMix_;
            }
        }

        oversampling_->processSamplesDown (block);
    }
}
