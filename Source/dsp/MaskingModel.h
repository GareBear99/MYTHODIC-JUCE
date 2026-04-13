#pragma once
#include <JuceHeader.h>
#include "Types.h"

namespace mythodic::dsp
{
    class MaskingModel
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        MaskFrame compute (juce::dsp::AudioBlock<float> block, const AnalysisFrame& analysis) noexcept;

    private:
        float maskSensitivity_ = 0.6f;
        float phaseLock_ = 0.5f;
    };
}
