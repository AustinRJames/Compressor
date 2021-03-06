/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Compressor.h"

#define THRESH_ID "threshold"
#define THRESH_NAME "Threshold"

#define RATIO_ID "ratio"
#define RATIO_NAME "Ratio"

#define ATTACKTIME_ID "attackTime"
#define ATTACKTIME_NAME "AttackTime"

#define RELEASETIME_ID "releaseTime"
#define RELEASETIME_NAME "ReleaseTime"



//==============================================================================
/**
*/
class ChannelStripAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ChannelStripAudioProcessor();
    ~ChannelStripAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //float threshold;
    //    int ratio;
    //    float attackTime;
    //    float releaseTime;

    AudioProcessorValueTreeState treeState;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
private:
    
    Compressor compress;
    
    
    dsp::Gain<float> gain;
    dsp::ProcessSpec spec;
    //dsp::Compressor<float> runCompressing;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripAudioProcessor)
};
