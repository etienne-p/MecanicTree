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
#include "Kinematics.h"

namespace Kinematic {
    
class TreeNode {
    
public:
    
    TreeNode(float offset, int len);
    void update();
    void draw();
    void reset();
    void setTarget(ofVec2f target);
    void addChild(float offset, int len);
    
    Chain * chain;
    TreeNode * parent;
    vector<TreeNode*> childs;
};
    
typedef TreeNode Tree;
    
}

#endif /* defined(__ofForest__Tree__) */
