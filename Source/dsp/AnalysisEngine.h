#pragma once
#include <JuceHeader.h>
#include "Types.h"

namespace mythodic::dsp
{
    class AnalysisEngine
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        AnalysisFrame analyze (juce::dsp::AudioBlock<float> block) noexcept;

    private:
        double sampleRate_ = 44100.0;
        int blockSize_ = 512;
        float transientProtect_ = 0.7f;
        float centerSanctity_ = 0.8f;
    };
}
