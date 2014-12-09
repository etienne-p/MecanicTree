//
//  Tree.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-08.
//
//

#include "Tree.h"

namespace Kinematic {
    
    TreeNode::TreeNode(float offset, int len){
        chain = new Chain(offset, len);
    }
    
    void TreeNode::addChild(float offset, int len){
        childs.push_back(new TreeNode(offset, len));
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
            childs[i]->chain->baseAngle = chain->getAbsoluteAngle(3);
            childs[i]->chain->base.set(chain->cartesianPoints[3]);
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