//
//  Sonify.h
//  ofForest
//
//  Created by etienne cella on 2014-12-13.
//
//

#ifndef __ofForest__Sonify__
#define __ofForest__Sonify__

#include <iostream>
#include "Chain.h"
#include "Tree.h"
#include <sndfile.hh>

struct AudioSourceData {
    Chain * chain;
    float volume;
    float pitch;
    float position;
};
    
class AudioGenerator{
    
public:
    
    vector<AudioSourceData> sources;
    vector<float> buffer;
    float volume;
    
    float volumeInterpolationFactor;
    float pitchInterpolationFactor;
    float dJointToVolumeFactor;
    float dJointToPitchFactor;
    float dJointToPitchOffset;
    
    AudioGenerator();
    ~AudioGenerator();
    bool loadSample(string path);
    void clearSources();
    void reset(Tree * tree);
    void addSources(Tree * tree);
    void process(float * output, int bufferSize, int nChannels);
    void processSource(float * output, int bufferSize, AudioSourceData& source);
    
    // http://stackoverflow.com/questions/1125666/how-do-you-do-bicubic-or-other-non-linear-interpolation-of-re-sampled-audio-da
    static float InterpolateHermite4pt3oX(float x0, float x1, float x2, float x3, float t);
};

#endif /* defined(__ofForest__Sonify__) */
