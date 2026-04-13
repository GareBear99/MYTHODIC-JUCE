#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class MythodicAudioProcessorEditor final : public juce::AudioProcessorEditor,
                                           private juce::Timer
{
public:
    explicit MythodicAudioProcessorEditor (MythodicAudioProcessor&);
    ~MythodicAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;
    void configureSlider (juce::Slider& slider, juce::Label& label, const juce::String& text);

    MythodicAudioProcessor& processor_;

    juce::Slider myth_, fuse_, crown_, orbit_, halo_, output_;
    juce::Label mythLabel_, fuseLabel_, crownLabel_, orbitLabel_, haloLabel_, outputLabel_;
    juce::Label titleLabel_, subtitleLabel_, meterLabel_;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> mythAttachment_, fuseAttachment_, crownAttachment_, orbitAttachment_, haloAttachment_, outputAttachment_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MythodicAudioProcessorEditor)
};
