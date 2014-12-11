#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    float rootLength = 600.f;
    float rootNodeCount = 32;
    tree = new Tree(0, rootNodeCount, rootLength);
    tree->chain->base.set(.5f * ofGetWidth(), .8f * ofGetHeight());
    
    float len = rootLength * (float)(rootNodeCount - 1) / (float)rootNodeCount;
    addBranches(tree, .5f, rootNodeCount  - 3, len, 6);
}

//--------------------------------------------------------------
void ofApp::addBranches(TreeNode * tree, float dAngle, int jointCount, float length, int depth){
    
    if (depth < 0 || jointCount < 3) return;
    
    float len = length * (float)(jointCount - 3) / (float)jointCount;
    
    TreeNode * b0 = tree->addChild(-dAngle, 2, jointCount , length);
    
    addBranches(b0, dAngle * .8f, jointCount - 3, len, depth - 1);
    
    TreeNode * b1 = tree->addChild(dAngle, 2, jointCount, length);
    
    addBranches(b1, dAngle * .8f, jointCount - 3, len, depth - 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    //for (int i = 0; i < 24; i++) tree->update();
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
