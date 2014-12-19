//
//  Tree.h
//  ofForest
//
//  Created by Etienne on 2014-12-08.
//
//

#ifndef __ofForest__Tree__
#define __ofForest__Tree__

#include "ofMain.h"
#include "Chain.h"

class TreeNode : public Chain {
    
public:
    
    TreeNode(float offset, int jointCount, float length);
    ~TreeNode();
    void update();
    void draw();
    void reset();
    void setTarget(ofVec2f target_);
    TreeNode * addChild(int parentJoint, float offset, int jointCount, float length);
    
    TreeNode * parent;
    vector<TreeNode*> childs;
    int parentJointIndex;
    
    void setJointDelta(float value);
    void setAwakeDistance(float value);
    void setFriction(float value);
    void setMaxUpdatesPerJoint(int value);
    
    // DOF
    float dofBaseValue, dofDecreaseFactor;
    void setDOFBaseValue(float baseValue);
    void setDOFDecreaseFactor(float decreaseFactor);
    void setDOF(float baseValue, float decreaseFactor);
};
    
typedef TreeNode Tree;

#endif /* defined(__ofForest__Tree__) */
