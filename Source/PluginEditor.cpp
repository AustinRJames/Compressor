/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChannelStripAudioProcessorEditor::ChannelStripAudioProcessorEditor (ChannelStripAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200  );
    
    //sliderAttachments = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "threshold", thresholdSlider);
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, "threshold", thresholdSlider));
    
    addAndMakeVisible(thresholdLabel);
    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.attachToComponent(&thresholdSlider, true);

    addAndMakeVisible(releaseTimeLabel);
    releaseTimeLabel.setText("Release Time", juce::dontSendNotification);
    releaseTimeLabel.attachToComponent(&releaseTimeSlider, false);
    
    addAndMakeVisible(attackTimeLabel);
    attackTimeLabel.setText("Attack Time", juce::dontSendNotification);
    attackTimeLabel.attachToComponent(&attackTimeSlider, true);
    
    addAndMakeVisible(ratioLabel);
    ratioLabel.setText("Ratio", juce::dontSendNotification);
    ratioLabel.attachToComponent(&ratioSelector, true);
    
    thresholdSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100,25);
    thresholdSlider.setRange(-50, 10, 0.10);
    thresholdSlider.setTextValueSuffix("dB");
    thresholdSlider.setBounds(250, 125, 250, 60);
    addAndMakeVisible(thresholdSlider);
    
    ratioSelector.addListener(this);
    ratioSelector.addItem("1:1", 1);
    ratioSelector.addItem("2:1", 2);
    ratioSelector.addItem("3:1", 3);
    ratioSelector.addItem("4:1", 4);
    ratioSelector.addItem("5:1", 5);
    ratioSelector.addItem("6:1", 6);
    ratioSelector.addItem("7:1", 7);
    ratioSelector.addItem("8:1", 8);
    ratioSelector.addItem("9:1", 9);
    ratioSelector.addItem("10:1", 10);
    ratioSelector.setBounds(300, 35, 150, 75);
    addAndMakeVisible(ratioSelector);



    attackTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 75, 25);
    attackTimeSlider.setRange(1, 1000, 1);
    attackTimeSlider.setTextValueSuffix("ms");
    attackTimeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attackTimeSlider.setBounds(10, 100, 150, 100);
    addAndMakeVisible(attackTimeSlider);
    
    

    releaseTimeSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 75, 25);
    releaseTimeSlider.setRange(1, 1000, 1);
    releaseTimeSlider.setTextValueSuffix("ms");
    releaseTimeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    releaseTimeSlider.setBounds(10, 5, 150, 100);
    addAndMakeVisible(releaseTimeSlider);


    
    
    
}

ChannelStripAudioProcessorEditor::~ChannelStripAudioProcessorEditor()
{
}

//==============================================================================
void ChannelStripAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ChannelStripAudioProcessorEditor::resized()
{
    thresholdSlider.setBounds(getLocalBounds());
}


void ChannelStripAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox){
    if (comboBox == &ratioSelector){
        if(ratioSelector.getSelectedId() == 1){
            audioProcessor.ratio = 1;
        }
        if(ratioSelector.getSelectedId() == 2){
            audioProcessor.ratio = 2;
        }
        if(ratioSelector.getSelectedId() == 3){
            audioProcessor.ratio = 3;
        }
        if(ratioSelector.getSelectedId() == 4){
            audioProcessor.ratio = 4;
        }
        if(ratioSelector.getSelectedId() == 5){
            audioProcessor.ratio = 5;
        }
        if(ratioSelector.getSelectedId() == 6){
            audioProcessor.ratio = 6;
        }        if(ratioSelector.getSelectedId() == 7){
            audioProcessor.ratio = 7;
        }
        if(ratioSelector.getSelectedId() == 8){
            audioProcessor.ratio = 8;
        }
        if(ratioSelector.getSelectedId() == 9){
            audioProcessor.ratio = 9;
        }
        if(ratioSelector.getSelectedId() == 10){
            audioProcessor.ratio = 10;
        }
    }
    
}

void ChannelStripAudioProcessorEditor::attackTimeChanged(juce::Slider *slider){
    if(slider == &attackTimeSlider){
        audioProcessor.attackTime = attackTimeSlider.getValue();
        
    }
    
}

void ChannelStripAudioProcessorEditor::releaseTimeChanged(juce::Slider *slider){
    if(slider == &releaseTimeSlider){
        audioProcessor.releaseTime = releaseTimeSlider.getValue();
    }
}
