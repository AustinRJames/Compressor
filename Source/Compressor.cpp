/*
  ==============================================================================

    Compressor.cpp
    Created: 3 Mar 2021 1:59:08pm
    Author:  Austin James

  ==============================================================================
*/

#include "Compressor.h"

void Compressor::setup(double sampleRate, int samplesPerBlock){
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    
    gain.prepare(spec);
    gain.reset();
    
    compression.prepare(spec);
}

void Compressor::setRatio(float ratio){
    
    compression.setRatio(ratio);
}

void Compressor::setThreshold(float threshold){
    compression.setThreshold(threshold);
    
}

void Compressor::setAttack(float attackTimeMs){
    
    compression.setAttack(attackTimeMs);
    
}

void Compressor::setRelease(float releaseTimeMs){
    
    compression.setRelease(releaseTimeMs);
    
}

void Compressor::setParameters(float threshold, float ratio, float attackTime, float releaseTime){
    
    setRatio(ratio);
    setThreshold(threshold);
    setRelease(releaseTime);
    setAttack(attackTime);
    
}

void Compressor::process(dsp::ProcessContextReplacing<float> (block)){
    
    compression.process(block);
    
    
}
