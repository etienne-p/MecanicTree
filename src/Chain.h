//
//  Kinematics.h
//  ofForest
//
//  Created by etienne cella on 2014-12-06.
//
//

#ifndef __ofForest__Chain__
#define __ofForest__Chain__

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
    
    float offsetAngle; // depends on parent
    float baseAngle; // rotate whole
    ofVec2f base;
    ofVec2f target;
    vector<ChainElement> elements;
    vector<ofVec2f> cartesianPoints;
    float dJoint;
    
    Chain(float offset, int jointCount, float length);
    void update();
    void reset();
    void draw();
    float getAbsoluteAngle(int index);
    
private:

    float evalAngleToTarget();
    float evalJointDelta();
    void updateCartesianPoints();
    
    // state
    float error;
    int elementIndex;
    int updatesForCurrentIndex;
};
    
}

#endif /* defined(__ofForest__Chain__) */
