#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    float rootLength = 600.f;
    float rootNodeCount = 24;
    tree = new Tree(0, rootNodeCount, rootLength);
    tree->base.set(.5f * ofGetWidth(), .8f * ofGetHeight());
    
    float len = rootLength * (float)(rootNodeCount - 1) / (float)rootNodeCount;
    addBranches(tree, .4f, rootNodeCount  - 2, len, 5);
}

//--------------------------------------------------------------
void ofApp::addBranches(TreeNode * tree, float dAngle, int jointCount, float length, int depth){
    
    if (depth < 0 || jointCount < 2) return;
    
    float len = length * (float)(jointCount - 2) / (float)jointCount;
    
    TreeNode * b0 = tree->addChild(2, -dAngle, jointCount , length);
    
    addBranches(b0, dAngle * .8f, jointCount - 2, len, depth - 1);
    
    TreeNode * b1 = tree->addChild(2, dAngle, jointCount, length);
    
    addBranches(b1, dAngle * .8f, jointCount - 2, len, depth - 1);
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
