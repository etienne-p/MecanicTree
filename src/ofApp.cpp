#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    tree = NULL;
    rootNodeCount = 24;
    rootLength = 600.f;
    parentJointOffset = 2;
    branchDepth = 5;
    branchAngleOffset = .4f;
    
    makeTree();
    setupUI();
    
}

void ofApp::makeTree(){
    
    if (tree != NULL) delete tree;
    
    tree = new Tree(0, rootNodeCount, rootLength);
    tree->base.set(.5f * ofGetWidth(), .96f * ofGetHeight());
    float len = rootLength * (float)(rootNodeCount - 1) / (float)rootNodeCount;
    addBranches(tree, branchAngleOffset, rootNodeCount  - parentJointOffset, len, branchDepth);
}

void ofApp::setupUI(){
    
    gui = new ofxUICanvas();
    
    // Tree Parameters (they require a tree rebuild)
    gui->addSpacer();
    gui->addLabel("TREE");
    gui->addIntSlider("ROOT_NODE_COUNT", 2, 64, rootNodeCount);
    gui->addSlider("ROOT_LENGTH", 20.f, 1200.f, rootLength);
    gui->addIntSlider("PARENT_JOINT_OFFSET", 1, 24, parentJointOffset);
    gui->addIntSlider("BRANCH_DEPTH", 0, 24, branchDepth);
    gui->addSlider("BRANCH_ANGLE_OFFSET", 0.f, 1.2f, branchAngleOffset);
    
    // Branch Parameters
    gui->addSpacer();
    gui->addLabel("BRANCH");
    gui->addSlider("JOINT_DELTA", 0.f, 1.f, tree->jointDelta);
    gui->addSlider("AWAKE_DISTANCE", 0.f, 600.f, tree->awakeDistance);
    gui->addSlider("FRICTION", 0.f, 1.f, tree->friction);
    gui->addSlider("DOF_BASE_VALUE", 0.f, 2.f,tree->dofBaseValue);
    gui->addSlider("DOF_DECREASE_FACTOR", 0.f, 1.f,tree->dofDecreaseFactor);
    gui->addIntSlider("MAX_UPDATES_PER_JOINT", 1, 32, tree->maxUpdatesPerJoint);
    
    gui->autoSizeToFitWidgets();
        
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e){
    
    string name = e.getName();
    
    // Tree Params
    if (name == "ROOT_NODE_COUNT"){
        rootNodeCount = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
        makeTree();
        syncBranchesParamsOnGui();
    }
    else if(name == "ROOT_LENGTH"){
        rootLength = ((ofxUISlider*)e.getSlider())->getScaledValue();
        makeTree();
        syncBranchesParamsOnGui();
    }
    else if(name == "PARENT_JOINT_OFFSET"){
        parentJointOffset = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
        makeTree();
        syncBranchesParamsOnGui();
    }
    else if(name == "BRANCH_DEPTH"){
        branchDepth = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
        makeTree();
        syncBranchesParamsOnGui();
    }
    else if(name == "BRANCH_ANGLE_OFFSET"){
        branchAngleOffset = ((ofxUISlider*)e.getSlider())->getScaledValue();
        makeTree();
        syncBranchesParamsOnGui();
    }
    
    // Branch Params
    else if(name == "JOINT_DELTA"){
        tree->setJointDelta(((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "AWAKE_DISTANCE"){
        tree->setAwakeDistance(((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "FRICTION"){
        tree->setFriction(((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "DOF_BASE_VALUE"){
        tree->setDOFBaseValue(((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "DOF_DECREASE_FACTOR"){
        tree->setDOFDecreaseFactor(((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "MAX_UPDATES_PER_JOINT"){
        tree->setMaxUpdatesPerJoint(((ofxUIIntSlider*)e.getSlider())->getScaledValue());
    }
    
}

//--------------------------------------------------------------
void ofApp::syncBranchesParamsOnGui(){
    tree->setJointDelta(((ofxUISlider*)gui->getWidget("JOINT_DELTA"))->getScaledValue());
    tree->setAwakeDistance(((ofxUISlider*)gui->getWidget("AWAKE_DISTANCE"))->getScaledValue());
    tree->setFriction(((ofxUISlider*)gui->getWidget("FRICTION"))->getScaledValue());
    tree->setDOFBaseValue(((ofxUISlider*)gui->getWidget("DOF_BASE_VALUE"))->getScaledValue());
    tree->setDOFDecreaseFactor(((ofxUISlider*)gui->getWidget("DOF_DECREASE_FACTOR"))->getScaledValue());
    tree->setMaxUpdatesPerJoint(((ofxUIIntSlider*)gui->getWidget("MAX_UPDATES_PER_JOINT"))->getScaledValue());
}

//--------------------------------------------------------------
void ofApp::addBranches(TreeNode * tree, float dAngle, int jointCount, float length, int depth){
    
    if (depth < 0 || jointCount < 2) return;
    
    float len = length * (float)(jointCount - parentJointOffset) / (float)jointCount;
    
    TreeNode * b0 = tree->addChild(parentJointOffset, -dAngle, jointCount , length);
    
    addBranches(b0, dAngle * .8f, jointCount - parentJointOffset, len, depth - 1);
    
    TreeNode * b1 = tree->addChild(parentJointOffset, dAngle, jointCount, length);
    
    addBranches(b1, dAngle * .8f, jointCount - parentJointOffset, len, depth - 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    //for (int i = 0; i < 8; i++) tree->update();
    tree->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    tree->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    tree->setTarget(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    tree->setTarget(ofVec2f(x, y));
    tree->reset();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    tree->base.set(.5f * (float)w, .96f * (float)h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
