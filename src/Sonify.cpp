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

namespace Sonify {

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
        buffer.resize(bufferSize);
        for (int i = 0; i < bufferSize; i++){
            buffer[i] = tmp[i];
        }
        return true;
    }
    
    void AudioGenerator::reset(Kinematic::Tree * tree){
        if (sources.size() > 0) clearSources();
        addSources(tree);
    }
    
    void AudioGenerator::addSources(Kinematic::Tree * tree){
        
        AudioSourceData source;
        source.chain = tree;
        source.volume = 0;
        source.pitch = 1.f;
        source.position = 0;
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
        
        int sourceBufferSize = buffer.size();
        float alpha = 0;
        float currentPitch = source.pitch;
        float currentVolume = source.volume;
        float currentPosition = source.position;
        
        Kinematic::ChainElement * elt = &(source.chain->elements[source.chain->elementIndex]);
        float dJoint = abs(elt->velocity);
        float targetVolume = min(1.0f, dJoint * dJointToVolumeFactor);
        float targetPitch = min(2.f, dJointToPitchOffset + dJoint * dJointToPitchFactor);
        
        for (int i = 0; i < bufferSize; i++){
            float fpos = floorf(currentPosition);
            alpha = currentPosition - fpos;
            float sample = .5f * (alpha * buffer[(int)fpos] + (1.0f - alpha) * buffer[(int)(fpos + 1)]);
            currentVolume += volumeInterpolationFactor * (targetVolume - currentVolume);
            output[i] += sample * currentVolume;
            currentPitch += pitchInterpolationFactor * (targetPitch - currentPitch);
            currentPosition = fmod(currentPosition + currentPitch, sourceBufferSize);
        }
        
        source.position = currentPosition;
        source.volume = currentVolume;
        source.pitch = currentPitch;
    }
}