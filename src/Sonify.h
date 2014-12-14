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
    Kinematic::ChainElement * elt;
    float volume;
    float pitch;
    float currentFrame;
};
    
class AudioGenerator{
    
public:
    
    vector<AudioSourceData> sources;
    vector<float> sourceBuffer;
    
    AudioGenerator();
    void clearSources();
    void reset(Kinematic::Tree * tree);
    void process(float * output, int bufferSize, int nChannels);
    void processSource(float * output, int bufferSize, AudioSourceData& source);
};
    
};


#endif /* defined(__ofForest__Sonify__) */
