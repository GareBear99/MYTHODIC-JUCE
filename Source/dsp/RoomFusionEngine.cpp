#include "RoomFusionEngine.h"
#include "../util/ParameterLayout.h"

namespace mythodic::dsp
{
    void RoomFusionEngine::prepare (double sampleRate, int samplesPerBlock)
    {
        juce::ignoreUnused (samplesPerBlock);
        juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock), 1 };
        delayL_.prepare (spec);
        delayR_.prepare (spec);
        delayL_.setDelay (static_cast<float> (sampleRate * 0.017));
        delayR_.setDelay (static_cast<float> (sampleRate * 0.023));
        delayL_.reset();
        delayR_.reset();
    }

    void RoomFusionEngine::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        roomAmount_    = apvts.getRawParameterValue (mythodic::params::roomAmount)->load();
        roomDucking_   = apvts.getRawParameterValue (mythodic::params::roomDucking)->load();
        earlyLateBias_ = apvts.getRawParameterValue (mythodic::params::earlyLateBias)->load();
        roomTone_      = static_cast<int> (apvts.getRawParameterValue (mythodic::params::roomTone)->load());
    }

    void RoomFusionEngine::process (juce::dsp::AudioBlock<float> block, const AnalysisFrame& analysis, const DecisionFrame& decisions) noexcept
    {
        if (block.getNumChannels() < 2)
            return;

        auto* left = block.getChannelPointer (0);
        auto* right = block.getChannelPointer (1);

        const float toneMul = roomTone_ == 0 ? 0.75f : roomTone_ == 2 ? 1.15f : 1.0f;
        const float duck = 1.0f - roomDucking_ * analysis.centerPriority * 0.5f;
        const float blend = roomAmount_ * (0.6f + 0.25f * decisions.fuse + 0.15f * decisions.density) * duck * toneMul;
        const float cross = 0.15f + earlyLateBias_ * 0.25f;

        for (size_t i = 0; i < block.getNumSamples(); ++i)
        {
            const float l = left[i];
            const float r = right[i];

            const float dl = delayL_.popSample (0);
            const float dr = delayR_.popSample (0);
            delayL_.pushSample (0, l + dr * cross);
            delayR_.pushSample (0, r + dl * cross);

            left[i] = l + dl * blend;
            right[i] = r + dr * blend;
        }
    }
}
