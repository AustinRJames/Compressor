/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Compressor.cpp"

//==============================================================================
ChannelStripAudioProcessor::ChannelStripAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),

    treeState(*this, nullptr, "ThreshParams", createParameterLayout())




#endif
{
    
}


ChannelStripAudioProcessor::~ChannelStripAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout ChannelStripAudioProcessor::createParameterLayout(){
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<AudioParameterFloat>(THRESH_ID,THRESH_NAME, -50.0f, 5.0f, 0.f) );
    
    return {params.begin(), params.end()    };
    
}

//==============================================================================
const juce::String ChannelStripAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChannelStripAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChannelStripAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChannelStripAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChannelStripAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChannelStripAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChannelStripAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChannelStripAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChannelStripAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChannelStripAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChannelStripAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
        
    compress.setup(sampleRate, samplesPerBlock);
    
    
}

void ChannelStripAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChannelStripAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChannelStripAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
 
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dsp::AudioBlock<float> block (buffer);
    
    
    compress.setParameters(threshold, ratio, attackTime, releaseTime);
    
    compress.process(dsp::ProcessContextReplacing<float> (block));


}

//==============================================================================
bool ChannelStripAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChannelStripAudioProcessor::createEditor()
{
    return new ChannelStripAudioProcessorEditor (*this);
}

//==============================================================================
void ChannelStripAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
   
    auto currentState = treeState.copyState();
    std::unique_ptr<XmlElement> xml (currentState.createXml());
    copyXmlToBinary(*xml, destData);
    
    
    
}

void ChannelStripAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

    std::unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes ));
    if (xml && xml->hasTagName("ThreshParams")){
        treeState.replaceState(ValueTree::fromXml(*xml));

    }
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChannelStripAudioProcessor();
}
