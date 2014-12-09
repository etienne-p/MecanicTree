#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    tree = new Tree(0, 6);
    tree->addChild(-.4f, 3);
    tree->addChild(.4f, 3);
}

//--------------------------------------------------------------
void ofApp::update(){
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
