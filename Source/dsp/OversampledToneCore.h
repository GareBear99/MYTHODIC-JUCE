#pragma once
#include <JuceHeader.h>
#include "Types.h"

namespace mythodic::dsp
{
    class OversampledToneCore
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock, int numChannels);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        void process (juce::dsp::AudioBlock<float> block, const DecisionFrame& decisions);

    private:
        void rebuildOversamplingIfNeeded();
        float shapeSample (float x) const noexcept;

        double sampleRate_ = 44100.0;
        int blockSize_ = 512;
        int channels_ = 2;
        int oversampleChoice_ = 0;
        int lastFactorPow_ = -1;
        float driveDb_ = 6.0f;
        float toneMix_ = 1.0f;
        int toneMode_ = 0;

        std::unique_ptr<juce::dsp::Oversampling<float>> oversampling_;
        juce::dsp::Gain<float> preGain_;
    };
}
