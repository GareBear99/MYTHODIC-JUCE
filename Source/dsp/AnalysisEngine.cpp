#include "AnalysisEngine.h"
#include "../util/ParameterLayout.h"
#include <cmath>

namespace mythodic::dsp
{
    void AnalysisEngine::prepare (double sampleRate, int samplesPerBlock)
    {
        sampleRate_ = sampleRate;
        blockSize_ = samplesPerBlock;
    }

    void AnalysisEngine::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        transientProtect_ = apvts.getRawParameterValue (mythodic::params::transientProtect)->load();
        centerSanctity_   = apvts.getRawParameterValue (mythodic::params::centerSanctity)->load();
    }

    AnalysisFrame AnalysisEngine::analyze (juce::dsp::AudioBlock<float> block) noexcept
    {
        AnalysisFrame frame;
        if (block.getNumChannels() < 2 || block.getNumSamples() == 0)
            return frame;

        const auto* left = block.getChannelPointer (0);
        const auto* right = block.getChannelPointer (1);

        float absSumL = 0.0f, absSumR = 0.0f;
        float diffSum = 0.0f, sumSum = 0.0f;
        float transient = 0.0f;
        float peak = 0.0f;

        float prevMid = 0.0f;
        for (size_t i = 0; i < block.getNumSamples(); ++i)
        {
            const float l = left[i];
            const float r = right[i];
            const float mid = 0.5f * (l + r);
            const float side = 0.5f * (l - r);

            absSumL += std::abs (l);
            absSumR += std::abs (r);
            diffSum += std::abs (side);
            sumSum += std::abs (mid);
            transient += std::abs (mid - prevMid);
            prevMid = mid;
            peak = std::max (peak, std::max (std::abs (l), std::abs (r)));
        }

        const float n = static_cast<float> (block.getNumSamples());
        const float avgMid = sumSum / n;
        const float avgSide = diffSum / n;

        frame.transientDensity = juce::jlimit (0.0f, 1.0f, (transient / n) * (0.5f + 0.5f * transientProtect_));
        frame.tonalStability   = juce::jlimit (0.0f, 1.0f, 1.0f - frame.transientDensity);
        frame.diffuseAmount    = juce::jlimit (0.0f, 1.0f, avgSide / (avgMid + 1.0e-5f));
        frame.sideEnergy       = juce::jlimit (0.0f, 1.0f, avgSide);
        frame.centerPriority   = juce::jlimit (0.0f, 1.0f, avgMid * centerSanctity_);
        frame.monoRisk         = juce::jlimit (0.0f, 1.0f, avgSide / (avgMid + avgSide + 1.0e-5f));
        frame.peakLevel        = peak;
        return frame;
    }
}
