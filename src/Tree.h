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

namespace Kinematic {
    
class TreeNode : public Chain {
    
public:
    
    TreeNode(float offset, int jointCount, float length);
    void update();
    void draw();
    void reset();
    void setTarget(ofVec2f target_);
    TreeNode * addChild(int parentJoint, float offset, int jointCount, float length);
    
    TreeNode * parent;
    vector<TreeNode*> childs;
    int parentJointIndex;
};
    
typedef TreeNode Tree;
    
}

#endif /* defined(__ofForest__Tree__) */
