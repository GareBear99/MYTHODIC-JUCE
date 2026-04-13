#pragma once
#include <JuceHeader.h>
#include "Types.h"

namespace mythodic::dsp
{
    class SpatialEngine
    {
    public:
        void prepare (double sampleRate, int samplesPerBlock);
        void updateParameters (juce::AudioProcessorValueTreeState& apvts);
        void process (juce::dsp::AudioBlock<float> block, const AnalysisFrame& analysis, const DecisionFrame& decisions) noexcept;

    private:
        double sampleRate_ = 44100.0;
        float orbit_ = 0.35f;
        float halo_ = 0.30f;
        float depth_ = 0.30f;
        float airSpread_ = 0.25f;
        float centerSanctity_ = 0.80f;
        float monoGuard_ = 0.85f;
        float subMonoHz_ = 120.0f;

        juce::dsp::LinkwitzRileyFilter<float> lowMidSplitL_;
        juce::dsp::LinkwitzRileyFilter<float> lowMidSplitR_;
    };
}
