//
//  Tree.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-08.
//
//

#include "Tree.h"

namespace Kinematic {
    
    // recursive
    void Tree::setTarget(ofVec2f target, TreeNode node){
        node.branch.target.set(target);
        for (int i = 0, len = node.childs.size(); i < len; i++){
            setTarget(target, node.childs[i]);
        }
    }
    
    void Tree::setTarget(ofVec2f target){
        setTarget(target, root);
    }
    
    void Tree::update(TreeNode node){
    
    }

    void Tree::update(){
        
        // recursively update, starting from root
    
    }

};