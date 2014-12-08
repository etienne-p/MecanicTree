//
//  Kinematics.h
//  ofForest
//
//  Created by etienne cella on 2014-12-06.
//
//

#ifndef __ofForest__Kinematics__
#define __ofForest__Kinematics__

#include "ofMain.h"

namespace Kinematic {
    
struct ChainElement {
    float link;
    float joint;
    float dof;
    float velocity;
};

class Chain {
    
public:
    
    ofVec2f base;
    ofVec2f target;
    vector<ChainElement> elements;
    float dJoint;
    
    Chain();
    void update();
    void reset();
    void draw();
    
    // state
    int elementIndex;
    
private:

    vector<ofVec2f> cartesianPoints;
    
    float evalAngleToTarget();
    float evalJointDelta();
    void updateCartesianPoints();
    
    // state
    float error;
    int updatesForCurrentIndex;
};
    
}

#endif /* defined(__ofForest__Kinematics__) */
