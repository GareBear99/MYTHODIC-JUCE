#include "OverlapDecisionCore.h"
#include "../util/ParameterLayout.h"

namespace mythodic::dsp
{
    void OverlapDecisionCore::prepare (double, int) {}

    void OverlapDecisionCore::updateParameters (juce::AudioProcessorValueTreeState& apvts)
    {
        fuseBias_     = apvts.getRawParameterValue (mythodic::params::fuseAmount)->load();
        separateBias_ = apvts.getRawParameterValue (mythodic::params::separateAmount)->load();
        crownBias_    = apvts.getRawParameterValue (mythodic::params::crownAmount)->load();
        densityBias_  = apvts.getRawParameterValue (mythodic::params::density)->load();
    }

    DecisionFrame OverlapDecisionCore::decide (const AnalysisFrame& a, const MaskFrame& m) const noexcept
    {
        DecisionFrame d;

        const float separateScore = 0.50f * m.maskScore + 0.25f * m.phaseConflict + 0.25f * a.monoRisk;
        const float fuseScore     = 0.65f * m.harmonicAffinity + 0.20f * a.tonalStability + 0.15f * (1.0f - m.phaseConflict);
        const float crownScore    = 0.60f * a.centerPriority + 0.25f * m.maskScore + 0.15f * a.transientDensity;

        d.separate = juce::jlimit (0.0f, 1.0f, separateScore * separateBias_);
        d.fuse     = juce::jlimit (0.0f, 1.0f, fuseScore * fuseBias_);
        d.crown    = juce::jlimit (0.0f, 1.0f, crownScore * crownBias_);
        d.density  = juce::jlimit (0.0f, 1.0f, (0.5f * d.fuse + 0.3f * d.crown + 0.2f * d.separate) * (0.5f + 0.5f * densityBias_));
        return d;
    }
}
