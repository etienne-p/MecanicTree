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
    
struct TreeNode {
    Chain branch;
    TreeNode * parent;
    vector<TreeNode> childs; // use pointers?
};

class Tree {
    
public:
    
    Tree();
    void update();
    void update(TreeNode node);
    void draw();
    void setTarget(ofVec2f target);
    void setTarget(ofVec2f target, TreeNode node);
    
private:
    
    TreeNode root;
};
    
}

#endif /* defined(__ofForest__Tree__) */
