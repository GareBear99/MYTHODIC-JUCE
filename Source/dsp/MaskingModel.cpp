#include "MaskingModel.h"
#include "../util/ParameterLayout.h"
#include <cmath>

namespace mythodic::dsp
{
    void MaskingModel::prepare (double, int) {}

    void MaskingModel::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        maskSensitivity_ = apvts.getRawParameterValue (mythodic::params::maskSensitivity)->load();
        phaseLock_       = apvts.getRawParameterValue (mythodic::params::phaseLock)->load();
    }

    MaskFrame MaskingModel::compute (juce::dsp::AudioBlock<float> block, const AnalysisFrame& analysis) noexcept
    {
        MaskFrame frame;
        if (block.getNumChannels() < 2 || block.getNumSamples() == 0)
            return frame;

        const auto* left = block.getChannelPointer (0);
        const auto* right = block.getChannelPointer (1);

        float dot = 0.0f;
        float ll = 0.0f;
        float rr = 0.0f;

        for (size_t i = 0; i < block.getNumSamples(); ++i)
        {
            dot += left[i] * right[i];
            ll += left[i] * left[i];
            rr += right[i] * right[i];
        }

        const float denom = std::sqrt (ll * rr) + 1.0e-6f;
        const float corr = dot / denom;

        frame.phaseConflict = juce::jlimit (0.0f, 1.0f, 0.5f * (1.0f - corr) * (0.5f + 0.5f * phaseLock_));
        frame.maskScore = juce::jlimit (0.0f, 1.0f, (analysis.centerPriority + analysis.sideEnergy) * 0.5f * maskSensitivity_ + analysis.monoRisk * 0.4f);
        frame.harmonicAffinity = juce::jlimit (0.0f, 1.0f, (1.0f - frame.phaseConflict) * analysis.tonalStability);
        return frame;
    }
}
