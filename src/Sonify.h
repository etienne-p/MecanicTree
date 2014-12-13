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

namespace Sonify {
    
struct AudioSourceData {
    Kinematic::ChainElement * elt;
    float volume;
    float pitch;
};
    
class AudioGenerator{
    
public:
    
    vector<AudioSourceData *> sources;

    AudioGenerator();
    void clearSources();
    void reset(Kinematic::Tree * tree);
    void process(float * output, int bufferSize);
    void processSource(float * output, int bufferSize, AudioSourceData * source);
    
};
    
};


#endif /* defined(__ofForest__Sonify__) */
