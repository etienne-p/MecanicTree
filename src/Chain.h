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

struct ChainElement {
    float link;
    float joint;
    //float prevJoint;
    float dof;
    float velocity;
};

class Chain {
    
public:
    
    float friction;
    float offsetAngle; // depends on parent
    float baseAngle; // rotate whole
    ofVec2f base;
    ofVec2f target;
    vector<ChainElement> elements;
    vector<ofVec2f> cartesianPoints;
    float jointDelta;
    float awakeDistance;
    int maxUpdatesPerJoint;
    
    Chain(float offset, int jointCount, float length);
    void update();
    void reset();
    void draw();
    float getAbsoluteAngle(int index);
    void setDOF(float initValue, float decreaseFactor);
    
    int elementIndex;
    
    
protected:

    float evalAngleToTarget(ofVec2f target_);
    float evalJointDelta(ofVec2f target_);
    void updateCartesianPoints();
    
    // state
    float error;
    int updatesForCurrentIndex;
};

#endif /* defined(__ofForest__Chain__) */
