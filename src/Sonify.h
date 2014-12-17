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

namespace Sonify {
    
struct AudioSourceData {
    Kinematic::Chain * chain;
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
    void reset(Kinematic::Tree * tree);
    void addSources(Kinematic::Tree * tree);
    void process(float * output, int bufferSize, int nChannels);
    void processSource(float * output, int bufferSize, AudioSourceData& source);
};
    
};


#endif /* defined(__ofForest__Sonify__) */
