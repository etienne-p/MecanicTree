//
//  Tree.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-08.
//
//

#include "Tree.h"


TreeNode::TreeNode(float offset, int jointCount, float length) : Chain(offset, jointCount, length){
    parentJointIndex = 0;
    dofBaseValue = .5f;
    dofDecreaseFactor = 1;
}

TreeNode::~TreeNode(){
    while(!childs.empty()) {
        delete childs.back();
        childs.pop_back();
    }
    parent = NULL;
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

void TreeNode::setMaxUpdatesPerJoint(int value){
    maxUpdatesPerJoint = value;
    for (int i = 0, len = childs.size(); i < len; i++){
        childs[i]->setMaxUpdatesPerJoint(value);
    }
}

void TreeNode::setJointDelta(float value){
    jointDelta = value;
    for (int i = 0, len = childs.size(); i < len; i++){
        childs[i]->setJointDelta(value);
    }
}

void TreeNode::setAwakeDistance(float value){
    awakeDistance = value;
    for (int i = 0, len = childs.size(); i < len; i++){
        childs[i]->setAwakeDistance(value);
    }
}

void TreeNode::setFriction(float value){
    friction = value;
    for (int i = 0, len = childs.size(); i < len; i++){
        childs[i]->setFriction(value);
    }
}

void TreeNode::setDOF(float baseValue, float decreaseFactor){
    dofBaseValue = baseValue;
    dofDecreaseFactor = decreaseFactor;
    Chain::setDOF(baseValue, decreaseFactor);
    for (int i = 0, len = childs.size(); i < len; i++){
        childs[i]->setDOF(baseValue, decreaseFactor);
    }
}

void TreeNode::setDOFBaseValue(float baseValue){
    setDOF(baseValue, dofDecreaseFactor);
}

void TreeNode::setDOFDecreaseFactor(float decreaseFactor){
    setDOF(dofBaseValue, decreaseFactor);
}

int TreeNode::countElements(){
    int count = elements.size();
    for (int i = 0, len = childs.size(); i < len; i++){
        count += childs[i]->countElements();
    }
    return count;
}