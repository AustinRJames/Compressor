/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ChannelStripAudioProcessorEditor  :
    public juce::AudioProcessorEditor,
    
    public juce::ComboBox::Listener
                                        
{
public:
    ChannelStripAudioProcessorEditor (ChannelStripAudioProcessor&);
    ~ChannelStripAudioProcessorEditor() override;
                    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
   // void sliderValueChanged(juce::Slider *slider) override;
    void comboBoxChanged(juce::ComboBox *comboBox) override;
    void attackTimeChanged(juce::Slider *slider) ;
    void releaseTimeChanged(juce::Slider *slider) ;
    
    std::vector<std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChannelStripAudioProcessor& audioProcessor;
    
    juce::ComboBox ratioSelector;
    
    juce::Slider thresholdSlider;
    juce::Slider attackTimeSlider;
    juce::Slider releaseTimeSlider;
    
    juce::Label releaseTimeLabel;
    juce::Label attackTimeLabel;
    juce::Label ratioLabel;
    juce::Label thresholdLabel;
    
    
    
    
    
    

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripAudioProcessorEditor)
};
