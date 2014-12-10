//
//  Tree.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-08.
//
//

#include "Tree.h"

namespace Kinematic {
    
    TreeNode::TreeNode(float offset, int jointCount, float length){
        chain = new Chain(offset, jointCount, length);
        parentJointIndex = 0;
    }
    
    TreeNode * TreeNode::addChild(float offset, int parentJoint, int jointCount, float length){
        childs.push_back(new TreeNode(offset, jointCount, length));
        childs.back()->parentJointIndex = parentJoint;
        return childs.back();
    }
    
    void TreeNode::setTarget(ofVec2f target){
        chain->target.set(target);
        for (int i = 0, len = childs.size(); i < len; i++){
            childs[i]->setTarget(target);
        }
    }
    
    void TreeNode::update(){
        chain->update();
        for (int i = 0, len = childs.size(); i < len; i++){
            int parentJoint = childs[i]->parentJointIndex;
            childs[i]->chain->baseAngle = chain->getAbsoluteAngle(parentJoint);
            childs[i]->chain->base.set(chain->cartesianPoints[parentJoint]);
            childs[i]->update();
        }
    }
    
    void TreeNode::reset(){
        chain->reset();
        for (int i = 0, len = childs.size(); i < len; i++){
            childs[i]->reset();
        }
    }
    
    void TreeNode::draw(){
        chain->draw();
        for (int i = 0, len = childs.size(); i < len; i++){
           childs[i]->draw();
        }
    }
};