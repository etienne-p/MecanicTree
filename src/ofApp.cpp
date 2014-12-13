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
    tree->base.set(.5f * ofGetWidth(), .8f * ofGetHeight());
    float len = rootLength * (float)(rootNodeCount - 1) / (float)rootNodeCount;
    addBranches(tree, branchAngleOffset, rootNodeCount  - parentJointOffset, len, branchDepth);
}

void ofApp::setupUI(){
    
    gui = new ofxUICanvas();
    
    // Tree Parameters (they require a tree rebuild)
    gui->addIntSlider("ROOT_NODE_COUNT", 2, 64, rootNodeCount);
    gui->addSlider("ROOT_LENGTH", 20.f, 1200.f, rootLength);
    gui->addIntSlider("PARENT_JOINT_OFFSET", 1, 24, parentJointOffset);
    gui->addIntSlider("BRANCH_DEPTH", 0, 24, branchDepth);
    gui->addSlider("BRANCH_ANGLE_OFFSET", 0.f, 1.2f, branchAngleOffset);
    
    
    
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);

}

void ofApp::guiEvent(ofxUIEventArgs &e){
    
    string name = e.getName();
    
    if (name == "ROOT_NODE_COUNT"){
        rootNodeCount = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
        makeTree();
    }
    else if(name == "ROOT_LENGTH"){
        rootLength = ((ofxUISlider*)e.getSlider())->getScaledValue();
        makeTree();
    }
    else if(name == "PARENT_JOINT_OFFSET"){
        parentJointOffset = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
        makeTree();
    }
    else if(name == "BRANCH_DEPTH"){
        branchDepth = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
        makeTree();
    }
    else if(name == "BRANCH_ANGLE_OFFSET"){
        branchAngleOffset = ((ofxUISlider*)e.getSlider())->getScaledValue();
        makeTree();
    }
    
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
