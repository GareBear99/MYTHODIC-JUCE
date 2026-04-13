#pragma once
#include <JuceHeader.h>
#include "dsp/AnalysisEngine.h"
#include "dsp/MaskingModel.h"
#include "dsp/OverlapDecisionCore.h"
#include "dsp/OversampledToneCore.h"
#include "dsp/SpatialEngine.h"
#include "dsp/RoomFusionEngine.h"
#include "dsp/SafetyOutput.h"
#include "util/ParameterLayout.h"

class MythodicAudioProcessor final : public juce::AudioProcessor
{
public:
    MythodicAudioProcessor();
    ~MythodicAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.20; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

    [[nodiscard]] float getLastPeak() const noexcept { return safety_.getLastPeak(); }
    [[nodiscard]] float getEstimatedTruePeak() const noexcept { return safety_.getEstimatedTruePeak(); }

private:
    mythodic::dsp::AnalysisEngine analysis_;
    mythodic::dsp::MaskingModel masking_;
    mythodic::dsp::OverlapDecisionCore overlap_;
    mythodic::dsp::OversampledToneCore tone_;
    mythodic::dsp::SpatialEngine spatial_;
    mythodic::dsp::RoomFusionEngine room_;
    mythodic::dsp::SafetyOutput safety_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MythodicAudioProcessor)
};
