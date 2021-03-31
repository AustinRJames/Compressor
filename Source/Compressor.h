/*
  ==============================================================================

    Compressor.h
    Created: 3 Mar 2021 1:59:08pm
    Author:  Austin James

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class Compressor{
    
public:
    

    double processSample(double sampleRate);
    int processMaxBlockSize(int blockSize);
    int processNumChannels(int numChannels);
    
    void setInput(float newInput);
    void setAttack(float attackTimeMs);
    void setRelease(float releaseTimeMs);
    void setRatio(float ratio);
    void setThreshold(float threshold);
    void setup(double sampleRate, int samplesPerBlock);
    
    void setParameters(float threshold, float ratio, float attackTime, float releaseTime);
    
private:
    dsp::Gain<float> gain;
    dsp::ProcessSpec spec;
    dsp::Compressor<float> compression;
    
    float attackTime = 0.0f;
    float releaseTime = 0.0f;
    float input = {0.0f};
    float threshold = 0.0f;
    float ratio = 1.0f;
    
};
