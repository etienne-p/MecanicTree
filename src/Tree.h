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
    
class TreeNode {
    
public:
    
    TreeNode(float offset, int jointCount, float length);
    void update();
    void draw();
    void reset();
    void setTarget(ofVec2f target);
    TreeNode * addChild(float offset, int parentJoint, int jointCount, float length);
    
    Chain * chain;
    TreeNode * parent;
    vector<TreeNode*> childs;
    int parentJointIndex;
};
    
typedef TreeNode Tree;
    
}

#endif /* defined(__ofForest__Tree__) */
