#include "PluginProcessor.h"
#include "PluginEditor.h"

MythodicAudioProcessor::MythodicAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMS", mythodic::params::createParameterLayout())
{
}

void MythodicAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    analysis_.prepare (sampleRate, samplesPerBlock);
    masking_.prepare (sampleRate, samplesPerBlock);
    overlap_.prepare (sampleRate, samplesPerBlock);
    tone_.prepare (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    spatial_.prepare (sampleRate, samplesPerBlock);
    room_.prepare (sampleRate, samplesPerBlock);
    safety_.prepare (sampleRate, samplesPerBlock);
}

void MythodicAudioProcessor::releaseResources() {}

bool MythodicAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void MythodicAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    juce::ScopedNoDenormals noDenormals;

    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block (buffer);

    analysis_.updateParameters (apvts);
    masking_.updateParameters (apvts);
    overlap_.updateParameters (apvts);
    tone_.updateParameters (apvts);
    spatial_.updateParameters (apvts);
    room_.updateParameters (apvts);
    safety_.updateParameters (apvts);

    const auto analysisFrame = analysis_.analyze (block);
    const auto maskFrame = masking_.compute (block, analysisFrame);
    const auto decisionFrame = overlap_.decide (analysisFrame, maskFrame);

    tone_.process (block, decisionFrame);
    spatial_.process (block, analysisFrame, decisionFrame);
    room_.process (block, analysisFrame, decisionFrame);

    const auto outputGainDb = apvts.getRawParameterValue (mythodic::params::outputGainDb)->load();
    buffer.applyGain (juce::Decibels::decibelsToGain (outputGainDb));

    safety_.process (block);
}

void MythodicAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto state = apvts.copyState(); auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void MythodicAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xmlState = getXmlFromBinary (data, sizeInBytes))
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorEditor* MythodicAudioProcessor::createEditor()
{
    return new MythodicAudioProcessorEditor (*this);
}
