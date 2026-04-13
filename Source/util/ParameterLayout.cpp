#include "ParameterLayout.h"

namespace mythodic::params
{
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        using namespace juce;

        std::vector<std::unique_ptr<RangedAudioParameter>> p;

        auto zeroToOne     = NormalisableRange<float> (0.0f, 1.0f, 0.001f);
        auto outputDbRange = NormalisableRange<float> (-24.0f, 12.0f, 0.01f);
        auto driveRange    = NormalisableRange<float> (0.0f, 24.0f, 0.01f);
        auto subRange      = NormalisableRange<float> (60.0f, 180.0f, 1.0f);
        auto ceilingRange  = NormalisableRange<float> (-3.0f, -0.1f, 0.01f);

        p.push_back (std::make_unique<AudioParameterFloat>  (mythAmount, "Myth", zeroToOne, 0.50f));
        p.push_back (std::make_unique<AudioParameterChoice> (qualityMode, "Quality", StringArray { "Live", "Mix", "Render" }, 1));
        p.push_back (std::make_unique<AudioParameterFloat>  (outputGainDb, "Output", outputDbRange, 0.0f));

        p.push_back (std::make_unique<AudioParameterFloat>  (fuseAmount, "Fuse", zeroToOne, 0.50f));
        p.push_back (std::make_unique<AudioParameterFloat>  (separateAmount, "Separate", zeroToOne, 0.50f));
        p.push_back (std::make_unique<AudioParameterFloat>  (crownAmount, "Crown", zeroToOne, 0.50f));
        p.push_back (std::make_unique<AudioParameterFloat>  (maskSensitivity, "Mask Sensitivity", zeroToOne, 0.60f));
        p.push_back (std::make_unique<AudioParameterFloat>  (phaseLock, "Phase Lock", zeroToOne, 0.50f));
        p.push_back (std::make_unique<AudioParameterFloat>  (transientProtect, "Transient Protect", zeroToOne, 0.70f));
        p.push_back (std::make_unique<AudioParameterFloat>  (density, "Density", zeroToOne, 0.50f));

        p.push_back (std::make_unique<AudioParameterChoice> (toneMode, "Tone Mode", StringArray { "Velvet", "Edge", "Myth" }, 0));
        p.push_back (std::make_unique<AudioParameterFloat>  (toneDriveDb, "Drive", driveRange, 6.0f));
        p.push_back (std::make_unique<AudioParameterFloat>  (toneMix, "Tone Mix", zeroToOne, 1.0f));
        p.push_back (std::make_unique<AudioParameterChoice> (oversampleMode, "Oversampling", StringArray { "Auto", "x2", "x4", "x8" }, 0));

        p.push_back (std::make_unique<AudioParameterFloat>  (orbit, "Orbit", zeroToOne, 0.35f));
        p.push_back (std::make_unique<AudioParameterFloat>  (halo, "Halo", zeroToOne, 0.30f));
        p.push_back (std::make_unique<AudioParameterFloat>  (depth, "Depth", zeroToOne, 0.30f));
        p.push_back (std::make_unique<AudioParameterFloat>  (airSpread, "Air Spread", zeroToOne, 0.25f));
        p.push_back (std::make_unique<AudioParameterFloat>  (centerSanctity, "Center Sanctity", zeroToOne, 0.80f));
        p.push_back (std::make_unique<AudioParameterFloat>  (subMonoHz, "Sub Mono", subRange, 120.0f));
        p.push_back (std::make_unique<AudioParameterFloat>  (monoGuard, "Mono Guard", zeroToOne, 0.85f));

        p.push_back (std::make_unique<AudioParameterFloat>  (roomAmount, "Room Amount", zeroToOne, 0.20f));
        p.push_back (std::make_unique<AudioParameterFloat>  (roomDucking, "Room Ducking", zeroToOne, 0.50f));
        p.push_back (std::make_unique<AudioParameterChoice> (roomTone, "Room Tone", StringArray { "Dark", "Neutral", "Bright" }, 1));
        p.push_back (std::make_unique<AudioParameterFloat>  (earlyLateBias, "Early/Late", zeroToOne, 0.40f));

        p.push_back (std::make_unique<AudioParameterFloat>  (ceilingDbtp, "Ceiling", ceilingRange, -1.0f));
        p.push_back (std::make_unique<AudioParameterBool>   (safeMode, "Safe Mode", true));

        return { p.begin(), p.end() };
    }
}
