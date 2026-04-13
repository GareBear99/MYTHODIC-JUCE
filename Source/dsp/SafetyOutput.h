#pragma once
#include <JuceHeader.h>

namespace mythodic::dsp
{
    class SafetyOutput
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        void process (juce::dsp::AudioBlock<float> block) noexcept;

        [[nodiscard]] float getLastPeak() const noexcept { return lastPeak_; }
        [[nodiscard]] float getEstimatedTruePeak() const noexcept { return estimatedTruePeak_; }

    private:
        float ceilingDbtp_ = -1.0f;
        bool safeMode_ = true;
        float lastPeak_ = 0.0f;
        float estimatedTruePeak_ = 0.0f;
    };
}
