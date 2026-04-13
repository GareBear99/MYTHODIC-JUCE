#pragma once
#include <JuceHeader.h>

namespace mythodic::params
{
    inline const juce::String mythAmount      { "mythAmount" };
    inline const juce::String qualityMode     { "qualityMode" };
    inline const juce::String outputGainDb    { "outputGainDb" };

    inline const juce::String fuseAmount      { "fuseAmount" };
    inline const juce::String separateAmount  { "separateAmount" };
    inline const juce::String crownAmount     { "crownAmount" };
    inline const juce::String maskSensitivity { "maskSensitivity" };
    inline const juce::String phaseLock       { "phaseLock" };
    inline const juce::String transientProtect{ "transientProtect" };
    inline const juce::String density         { "density" };

    inline const juce::String toneMode        { "toneMode" };
    inline const juce::String toneDriveDb     { "toneDriveDb" };
    inline const juce::String toneMix         { "toneMix" };
    inline const juce::String oversampleMode  { "oversampleMode" };

    inline const juce::String orbit           { "orbit" };
    inline const juce::String halo            { "halo" };
    inline const juce::String depth           { "depth" };
    inline const juce::String airSpread       { "airSpread" };
    inline const juce::String centerSanctity  { "centerSanctity" };
    inline const juce::String subMonoHz       { "subMonoHz" };
    inline const juce::String monoGuard       { "monoGuard" };

    inline const juce::String roomAmount      { "roomAmount" };
    inline const juce::String roomDucking     { "roomDucking" };
    inline const juce::String roomTone        { "roomTone" };
    inline const juce::String earlyLateBias   { "earlyLateBias" };

    inline const juce::String ceilingDbtp     { "ceilingDbtp" };
    inline const juce::String safeMode        { "safeMode" };

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
}
