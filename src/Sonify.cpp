//
//  Sonify.cpp
//  ofForest
//
//  Created by etienne cella on 2014-12-13.
//
//

// http://ofdsp.blogspot.ca/2011/07/installing-libsndfile-with-xcode.html
// https://github.com/erikd/libsndfile/blob/master/examples/sndfilehandle.cc

#include "Sonify.h"

AudioGenerator::AudioGenerator(){
    
    volumeInterpolationFactor = 0.0001f;
    pitchInterpolationFactor = 0.0001f;
    dJointToVolumeFactor = 50;
    dJointToPitchFactor = 50;
    dJointToPitchOffset = .8f;
    volume = 1;    }

AudioGenerator::~AudioGenerator(){
}

void AudioGenerator::clearSources(){
    sources.clear();
}

bool AudioGenerator::loadSample(string path){
    
    buffer.clear();
    
    SndfileHandle file;
    file = SndfileHandle(path);
    
    if (file.error() != 0){
        ofLogError("AudioGenerator::loadSample [" + path + "] failed: " + file.strError());
        return false;
    }
    
    int bufferSize = file.frames();
    float tmp[bufferSize];
    file.read (tmp, bufferSize);
    buffer.resize(bufferSize + 2);
    for (int i = 0; i < bufferSize; i++){
        buffer[i + 1] = tmp[i];
    }
    buffer[0] = tmp[bufferSize - 1];
    buffer[bufferSize + 1] = tmp[0];
    return true;
}

void AudioGenerator::reset(Tree * tree){
    if (sources.size() > 0) clearSources();
    addSources(tree);
}

void AudioGenerator::addSources(Tree * tree){
    
    AudioSourceData source;
    source.chain = tree;
    source.volume = 0;
    source.pitch = 1.f;
    source.position = ofRandom(1.0f, buffer.size() - 1.0f);
    sources.push_back(source);
    
    for (int i = 0, len = tree->childs.size(); i < len; i++){
        addSources(tree->childs[i]);
    }
}

void AudioGenerator::process(float * output, int bufferSize, int nChannels){
    
    if (buffer.size() < 1){
        ofLogError("AudioGenerator::process called before a sample was loaded (use AudioGenerator::loadSample)");
        memset(output, 0, sizeof(float) * bufferSize * nChannels);
        return;
    }
    
    float monoOutput[bufferSize];
    memset(monoOutput, 0, sizeof(float) * bufferSize);
    for (int i = 0, len = sources.size(); i < len; i++){
        processSource(monoOutput, bufferSize, sources[i]);
    }
    for (int i = 0; i < bufferSize; i++){
        output[i * 2] = output[i * 2 + 1] = monoOutput[i] * volume;
    }
}

void AudioGenerator::processSource(float * output, int bufferSize, AudioSourceData& source){
    
    const float sourceBufferSizeMinus2 = buffer.size() - 2.0f;
    float currentPitch = source.pitch;
    float currentVolume = source.volume;
    float currentPosition = min(max(1.0f, source.position), sourceBufferSizeMinus2 + 1.0f);
    
    ChainElement * elt = &(source.chain->elements[source.chain->elementIndex]);
    float dJoint = abs(elt->velocity);
    float targetVolume = min(1.0f, dJoint * dJointToVolumeFactor);
    float targetPitch = min(2.f, dJointToPitchOffset + dJoint * dJointToPitchFactor);
    
    for (int i = 0; i < bufferSize; i++){
        
        float t = currentPosition - floorf(currentPosition);
        
        int pos = (int)currentPosition;
        
        float sample = InterpolateHermite4pt3oX(buffer[pos - 1], buffer[pos], buffer[pos + 1], buffer[pos + 2], t);
        
        currentVolume += volumeInterpolationFactor * (targetVolume - currentVolume);
        output[i] += sample * currentVolume;
        currentPitch += pitchInterpolationFactor * (targetPitch - currentPitch);
        currentPosition = 1.0f + fmod(currentPosition + currentPitch, sourceBufferSizeMinus2);
    }
    
    source.position = currentPosition;
    source.volume = currentVolume;
    source.pitch = currentPitch;
}

float AudioGenerator::InterpolateHermite4pt3oX(float x0, float x1, float x2, float x3, float t){
    float c0 = x1;
    float c1 = .5f * (x2 - x0);
    float c2 = x0 - (2.5f * x1) + (2 * x2) - (.5f * x3);
    float c3 = (.5f * (x3 - x0)) + (1.5f * (x1 - x2));
    return (((((c3 * t) + c2) * t) + c1) * t) + c0;
}
