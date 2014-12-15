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
        
        volumeInterpolationFactor = 0.01f;
        pitchInterpolationFactor = 0.01f;
        
        SndfileHandle file;
        // https://www.freesound.org/people/danbert75/sounds/223248/
        file = SndfileHandle("/Users/viking/Dev/of_v0.8.3_osx_release/apps/myApps/offorest/bin/data/fx.wav");
        int numFrames = file.frames();
        
        float buffer [numFrames]; // will be destroyed when it falls out of scope
        file.read (buffer, numFrames);
        
        for (int i = 0; i < numFrames; i++){
            sourceBuffer.push_back(buffer[i]); // TODO: best way?
        }
        sourceBuffer.push_back(buffer[0]);
    }
    
    void AudioGenerator::clearSources(){
        sources.clear();
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
        
        if (sources.size() > 40) return;
    
        for (int i = 0, len = tree->childs.size(); i < len; i++){
            addSources(tree->childs[i]);
        }
    }
    
    void AudioGenerator::process(float * output, int bufferSize, int nChannels){
        for (int i = 0, len = sources.size(); i < len; i++){
            processSource(output, bufferSize, nChannels, sources[i]);
        }
    }

    void AudioGenerator::processSource(float * output, int bufferSize, int nChannels, AudioSourceData& source){
        
        int len = sourceBuffer.size() - 1;
        float alpha = 0;
        float currentPitch = source.pitch;
        float currentVolume = source.volume;
        float currentPosition = source.position;
        
        Kinematic::ChainElement * elt = &(source.chain->elements[source.chain->elementIndex]);
        float dJoint = abs(elt->joint - elt->prevJoint);
        float targetVolume = min(.8f, dJoint * 1000);
        float targetPitch = min(2.f, 0.5f + dJoint * 100.f);
        
        
        for (int i = 0; i < bufferSize; i++){
            int fpos = floorf(currentPosition);
            alpha = currentPosition - fpos;
            float sample = 0.5 * (alpha * sourceBuffer[fpos] + (1 - alpha) * sourceBuffer[fpos + 1]);
            currentVolume += volumeInterpolationFactor * (targetVolume - currentVolume);
            output[i * nChannels] = output[i * nChannels + 1] = sample * currentVolume;
            currentPitch += pitchInterpolationFactor * (targetPitch - currentPitch);
            currentPosition = fmod(len + currentPosition + currentPitch, len);
        }
        
        source.position = currentPosition;
        source.volume = currentVolume;
        source.pitch = currentPitch;
    }
}