#pragma once
#include <JuceHeader.h>
#include "Types.h"

namespace mythodic::dsp
{
    class OverlapDecisionCore
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        DecisionFrame decide (const AnalysisFrame& analysis, const MaskFrame& mask) const noexcept;

    private:
        float fuseBias_ = 0.5f;
        float separateBias_ = 0.5f;
        float crownBias_ = 0.5f;
        float densityBias_ = 0.5f;
    };
}
