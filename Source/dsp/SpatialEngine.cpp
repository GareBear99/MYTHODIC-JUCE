#include "SpatialEngine.h"
#include "../util/ParameterLayout.h"

namespace mythodic::dsp
{
    void SpatialEngine::prepare (double sampleRate, int samplesPerBlock)
    {
        sampleRate_ = sampleRate;
        juce::dsp::ProcessSpec spec { sampleRate_, static_cast<juce::uint32> (samplesPerBlock), 1 };
        lowMidSplitL_.prepare (spec);
        lowMidSplitR_.prepare (spec);
        lowMidSplitL_.reset();
        lowMidSplitR_.reset();
        lowMidSplitL_.setType (juce::dsp::LinkwitzRileyFilterType::lowpass);
        lowMidSplitR_.setType (juce::dsp::LinkwitzRileyFilterType::lowpass);
        lowMidSplitL_.setCutoffFrequency (subMonoHz_);
        lowMidSplitR_.setCutoffFrequency (subMonoHz_);
    }

    void SpatialEngine::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        orbit_          = apvts.getRawParameterValue (mythodic::params::orbit)->load();
        halo_           = apvts.getRawParameterValue (mythodic::params::halo)->load();
        depth_          = apvts.getRawParameterValue (mythodic::params::depth)->load();
        airSpread_      = apvts.getRawParameterValue (mythodic::params::airSpread)->load();
        centerSanctity_ = apvts.getRawParameterValue (mythodic::params::centerSanctity)->load();
        monoGuard_      = apvts.getRawParameterValue (mythodic::params::monoGuard)->load();
        subMonoHz_      = apvts.getRawParameterValue (mythodic::params::subMonoHz)->load();
        lowMidSplitL_.setCutoffFrequency (subMonoHz_);
        lowMidSplitR_.setCutoffFrequency (subMonoHz_);
    }

    void SpatialEngine::process (juce::dsp::AudioBlock<float> block, const AnalysisFrame& analysis, const DecisionFrame& decisions) noexcept
    {
        if (block.getNumChannels() < 2)
            return;

        auto* left = block.getChannelPointer (0);
        auto* right = block.getChannelPointer (1);
        const float sideScale = juce::jlimit (0.2f, 1.8f,
            1.0f + orbit_ * 0.45f + halo_ * 0.20f + airSpread_ * 0.15f
            - monoGuard_ * analysis.monoRisk * 0.6f - centerSanctity_ * decisions.crown * 0.25f);
        const float midScale = juce::jlimit (0.7f, 1.4f, 1.0f + centerSanctity_ * 0.15f + decisions.crown * 0.10f);
        const float subMonoMix = juce::jlimit (0.0f, 1.0f, 0.65f + monoGuard_ * 0.35f);

        for (size_t i = 0; i < block.getNumSamples(); ++i)
        {
            const float l = left[i];
            const float r = right[i];
            float mid = 0.5f * (l + r);
            float side = 0.5f * (l - r);

            mid *= midScale;
            side *= sideScale;

            const float lowL = lowMidSplitL_.processSample (l);
            const float lowR = lowMidSplitR_.processSample (r);
            const float lowMid = 0.5f * (lowL + lowR);

            float outL = mid + side;
            float outR = mid - side;

            outL = juce::jmap (subMonoMix, outL, lowMid + (outL - lowL) * (1.0f + depth_ * 0.05f));
            outR = juce::jmap (subMonoMix, outR, lowMid + (outR - lowR) * (1.0f + depth_ * 0.05f));

            left[i] = outL;
            right[i] = outR;
        }
    }
}
