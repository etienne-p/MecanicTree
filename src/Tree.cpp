//
//  Tree.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-08.
//
//

#include "Tree.h"

namespace Kinematic {
    
    TreeNode::TreeNode(float offset, int jointCount, float length) : Chain(offset, jointCount, length){
        parentJointIndex = 0;
    }
    
    TreeNode * TreeNode::addChild(int parentJoint, float offset, int jointCount, float length){
        childs.push_back(new TreeNode(offset, jointCount, length));
        childs.back()->parentJointIndex = parentJoint;
        return childs.back();
    }
    
    void TreeNode::setTarget(ofVec2f target_){
        target.set(target_);
        for (int i = 0, len = childs.size(); i < len; i++){
            childs[i]->setTarget(target_);
        }
    }
    
    void TreeNode::update(){
        Chain::update();
        for (int i = 0, len = childs.size(); i < len; i++){
            int parentJoint = childs[i]->parentJointIndex;
            childs[i]->baseAngle = getAbsoluteAngle(parentJoint);
            childs[i]->base.set(cartesianPoints[parentJoint]);
            childs[i]->update();
        }
    }
    
    void TreeNode::reset(){
        Chain::reset();
        for (int i = 0, len = childs.size(); i < len; i++){
            childs[i]->reset();
        }
    }
    
    void TreeNode::draw(){
        Chain::draw();
        for (int i = 0, len = childs.size(); i < len; i++){
           childs[i]->draw();
        }
    }
};