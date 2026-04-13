#include "PluginEditor.h"
#include "util/ParameterLayout.h"

MythodicAudioProcessorEditor::MythodicAudioProcessorEditor (MythodicAudioProcessor& p)
    : AudioProcessorEditor (&p), processor_ (p)
{
    setSize (980, 620);

    titleLabel_.setText ("MYTHODIC", juce::dontSendNotification);
    titleLabel_.setFont (juce::FontOptions (28.0f, juce::Font::bold));
    titleLabel_.setJustificationType (juce::Justification::centredLeft);
    addAndMakeVisible (titleLabel_);

    subtitleLabel_.setText ("Overlap Intelligence • Spatial-Spectral Tone Shaping", juce::dontSendNotification);
    subtitleLabel_.setJustificationType (juce::Justification::centredLeft);
    addAndMakeVisible (subtitleLabel_);

    meterLabel_.setJustificationType (juce::Justification::centredRight);
    addAndMakeVisible (meterLabel_);

    configureSlider (myth_, mythLabel_, "Myth");
    configureSlider (fuse_, fuseLabel_, "Fuse");
    configureSlider (crown_, crownLabel_, "Crown");
    configureSlider (orbit_, orbitLabel_, "Orbit");
    configureSlider (halo_, haloLabel_, "Halo");
    configureSlider (output_, outputLabel_, "Output");

    mythAttachment_ = std::make_unique<Attachment> (processor_.apvts, mythodic::params::mythAmount, myth_);
    fuseAttachment_ = std::make_unique<Attachment> (processor_.apvts, mythodic::params::fuseAmount, fuse_);
    crownAttachment_ = std::make_unique<Attachment> (processor_.apvts, mythodic::params::crownAmount, crown_);
    orbitAttachment_ = std::make_unique<Attachment> (processor_.apvts, mythodic::params::orbit, orbit_);
    haloAttachment_ = std::make_unique<Attachment> (processor_.apvts, mythodic::params::halo, halo_);
    outputAttachment_ = std::make_unique<Attachment> (processor_.apvts, mythodic::params::outputGainDb, output_);

    startTimerHz (24);
}

void MythodicAudioProcessorEditor::configureSlider (juce::Slider& slider, juce::Label& label, const juce::String& text)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 22);
    addAndMakeVisible (slider);

    label.setText (text, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

void MythodicAudioProcessorEditor::timerCallback()
{
    const auto peakDb = juce::Decibels::gainToDecibels (processor_.getLastPeak(), -100.0f);
    const auto tpDb = juce::Decibels::gainToDecibels (processor_.getEstimatedTruePeak(), -100.0f);
    meterLabel_.setText ("Peak " + juce::String (peakDb, 1) + " dB  |  Est. TP " + juce::String (tpDb, 1) + " dB", juce::dontSendNotification);
    repaint();
}

void MythodicAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();
    g.fillAll (juce::Colour::fromRGB (9, 10, 16));

    juce::ColourGradient bg (juce::Colour::fromRGB (31, 20, 61), bounds.getTopLeft(),
                             juce::Colour::fromRGB (8, 11, 19), bounds.getBottomRight(), false);
    g.setGradientFill (bg);
    g.fillRoundedRectangle (bounds.reduced (12.0f), 26.0f);

    auto orbArea = getLocalBounds().reduced (220, 110).toFloat();
    const auto center = orbArea.getCentre();
    const float radius = juce::jmin (orbArea.getWidth(), orbArea.getHeight()) * 0.40f;

    for (int i = 0; i < 5; ++i)
    {
        const float r = radius * (1.0f - 0.17f * static_cast<float> (i));
        const auto colour = i % 2 == 0 ? juce::Colour::fromRGBA (160, 92, 255, 95)
                                       : juce::Colour::fromRGBA (255, 183, 72, 70);
        g.setColour (colour);
        g.drawEllipse (center.x - r, center.y - r, r * 2.0f, r * 2.0f, 2.0f);
    }

    g.setColour (juce::Colour::fromRGBA (78, 241, 230, 70));
    g.fillEllipse (center.x - radius * 0.42f, center.y - radius * 0.42f, radius * 0.84f, radius * 0.84f);

    g.setColour (juce::Colours::white.withAlpha (0.90f));
    g.setFont (juce::FontOptions (18.0f, juce::Font::bold));
    g.drawFittedText ("Overlap Orb", orbArea.toNearestInt(), juce::Justification::centred, 1);
}

void MythodicAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (24);
    auto header = area.removeFromTop (58);
    titleLabel_.setBounds (header.removeFromLeft (320));
    subtitleLabel_.setBounds (header.removeFromLeft (420));
    meterLabel_.setBounds (header);

    auto footer = area.removeFromBottom (220);
    const int knobW = footer.getWidth() / 6;

    auto placeKnob = [knobW, &footer] (juce::Slider& s, juce::Label& l)
    {
        auto cell = footer.removeFromLeft (knobW);
        l.setBounds (cell.removeFromTop (24));
        s.setBounds (cell.reduced (8));
    };

    placeKnob (myth_, mythLabel_);
    placeKnob (fuse_, fuseLabel_);
    placeKnob (crown_, crownLabel_);
    placeKnob (orbit_, orbitLabel_);
    placeKnob (halo_, haloLabel_);
    placeKnob (output_, outputLabel_);
}
