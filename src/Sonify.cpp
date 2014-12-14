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
        
        SndfileHandle file;
        file = SndfileHandle("/Users/etienne/Dev/of_v0.8.3_osx_release/apps/myApps/ofForest/bin/data/fx.wav");
        int numFrames = file.frames();
        
        float buffer [numFrames]; // will be destroyed when it falls out of scope
        file.read (buffer, numFrames);
        
        for (int i = 0; i < numFrames; i++){
            sourceBuffer.push_back(buffer[i]); // TODO: best way?
        }
    }
    
    void AudioGenerator::clearSources(){
        sources.clear();
    }
    
    void AudioGenerator::reset(Kinematic::Tree * tree){
        
        if (sources.size() > 0) clearSources();
        
        AudioSourceData source;
        source.elt = &(tree->elements[0]);
        source.volume = 0;
        source.pitch = 1.f;
        source.currentFrame = 0;
        
        sources.push_back(source);
    }
    
    void AudioGenerator::process(float * output, int bufferSize, int nChannels){
        for (int i = 0, len = sources.size(); i < 1; i++){
            processSource(output, bufferSize, sources[i]);
        }
    }

    void AudioGenerator::processSource(float * output, int bufferSize, AudioSourceData& source){
        int len = sourceBuffer.size();
        int frame = source.currentFrame;
        for (int i = 0; i < bufferSize; i = i + 2){
            output[i] = sourceBuffer[frame];
            output[i + 1] = sourceBuffer[frame];
            frame = (frame + 1) % len;
        }
        source.currentFrame = frame;
    }
}