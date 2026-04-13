#pragma once

namespace mythodic::dsp
{
    struct AnalysisFrame
    {
        float transientDensity = 0.0f;
        float tonalStability   = 0.0f;
        float diffuseAmount    = 0.0f;
        float sideEnergy       = 0.0f;
        float monoRisk         = 0.0f;
        float centerPriority   = 0.0f;
        float peakLevel        = 0.0f;
    };

    struct MaskFrame
    {
        float maskScore        = 0.0f;
        float phaseConflict    = 0.0f;
        float harmonicAffinity = 0.0f;
    };

    struct DecisionFrame
    {
        float fuse             = 0.5f;
        float separate         = 0.5f;
        float crown            = 0.5f;
        float density          = 0.5f;
    };
}
