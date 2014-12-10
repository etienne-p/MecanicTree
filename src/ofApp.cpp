#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    float rootLength = 420.f;
    float rootNodeCount = 12;
    tree = new Tree(0, rootNodeCount, rootLength);
    tree->chain->base.set(.5f * ofGetWidth(), .5f * ofGetHeight());
    
    float len = rootLength * (float)(rootNodeCount - 1) / (float)rootNodeCount;
    addBranches(tree, .8f, rootNodeCount  - 1, len, 3);
}

//--------------------------------------------------------------
void ofApp::addBranches(TreeNode * tree, float dAngle, int jointCount, float length, int depth){
    
    if (depth < 0 || jointCount < 3) return;
    
    float len = length * (float)(jointCount - 1) / (float)jointCount;
    
    TreeNode * b0 = tree->addChild(-dAngle, 1, jointCount, length);
    addBranches(b0, dAngle, jointCount / 2, len * .5f, depth - 1);
    
    TreeNode * b1 = tree->addChild(dAngle, 1, jointCount, length);
    addBranches(b1, dAngle, jointCount - 1, len, depth - 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < 24; i++) tree->update();
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
