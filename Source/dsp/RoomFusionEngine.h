#pragma once
#include <JuceHeader.h>
#include "Types.h"

namespace mythodic::dsp
{
    class RoomFusionEngine
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        void process (juce::dsp::AudioBlock<float> block, const AnalysisFrame& analysis, const DecisionFrame& decisions) noexcept;

    private:
        float roomAmount_ = 0.20f;
        float roomDucking_ = 0.50f;
        float earlyLateBias_ = 0.40f;
        int roomTone_ = 1;
        juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayL_ { 48000 };
        juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayR_ { 48000 };
    };
}
