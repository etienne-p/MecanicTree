#include "ofApp.h"

// TODO: add konami code to display / hide UI

//--------------------------------------------------------------
void ofApp::setup(){
    
    tree = NULL;
    rootNodeCount = 12;
    rootLength = 600.f;
    parentJointOffset = 2;
    branchDepth = 3;
    branchAngleOffset = .4f;
    kinematicUpdateRate = 1;
    
    buffer = new RingBuffer<float>(4096);
    audioGenerator = new AudioGenerator();
    audioGenerator->loadSample(ofToDataPath("fx.wav"));
    
    treeMesh = new TreeMesh();
    
    light.setPointLight();
    light.setAttenuation(.5f);
    light.setPosition(ofVec3f(ofGetWidth() / 2, 0, 100));
    light.setAmbientColor(ofColor::black);
    light.setDiffuseColor(ofColor::steelBlue);
    light.setSpecularColor(ofColor::white);
    
    ofSetSmoothLighting(true);
    ofEnableDepthTest();
    
    makeTree();
    setupUI();
    
    //soundStream.setup(this, 2, 0, 44100, 256, 4);
    
    vector<int> v;
    v.push_back(103);
    v.push_back(117);
    v.push_back(105);
    v.push_back(357);
    guiCode.setCode(v);
}

void ofApp::makeTree(){
    
    if (tree != NULL) {
        audioGenerator->clearSources();
        delete tree;
    }
    
    tree = new Tree(0, rootNodeCount, rootLength);
    tree->base.set(.5f * ofGetWidth(), .96f * ofGetHeight());
    float len = rootLength * (float)(rootNodeCount - 1) / (float)rootNodeCount;
    addBranches(tree, branchAngleOffset, rootNodeCount  - parentJointOffset, len, branchDepth);
    
    treeMesh->setTree(tree);
    audioGenerator->reset(tree);
}

void ofApp::setupUI(){
    
    gui = new ofxUICanvas();
    
    // APP Parameters (they require a tree rebuild)
    gui->addSpacer();
    gui->addLabel("APP");
    gui->addIntSlider("PHYSICS_UPDATE_RATE", 1, 32, kinematicUpdateRate);
    
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
    
    // Audio Parameters
    gui->addSpacer();
    gui->addLabel("AUDIO");
    gui->addSlider("VOL_INTERP_FACTOR", 0, 0.001f, audioGenerator->volumeInterpolationFactor);
    gui->addSlider("PITCH_INTERP_FACTOR", 0, 0.001f, audioGenerator->pitchInterpolationFactor);
    gui->addSlider("JOINT_VOL_FACTOR", 0, 400, audioGenerator->dJointToVolumeFactor);
    gui->addSlider("JOINT_PITCH_FACTOR", 0, 400, audioGenerator->dJointToPitchFactor);
    gui->addSlider("JOINT_PITCH_OFFSET", 0, 4.f, audioGenerator->dJointToPitchOffset);
    gui->addSlider("VOLUME", 0, 10, audioGenerator->volume);
    
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    gui->loadSettings("settings.xml");
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e){
    
    string name = e.getName();
    
    // App Params
    if (name == "PHYSICS_UPDATE_RATE"){
        kinematicUpdateRate = ((ofxUIIntSlider*)e.getSlider())->getScaledValue();
    }
    
    // Tree Params
    else if (name == "ROOT_NODE_COUNT"){
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
    
    // Audio Params
    else if(name == "VOL_INTERP_FACTOR"){
        audioGenerator->volumeInterpolationFactor = (((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "PITCH_INTERP_FACTOR"){
        audioGenerator->pitchInterpolationFactor = (((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "JOINT_VOL_FACTOR"){
        audioGenerator->dJointToVolumeFactor = (((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "JOINT_PITCH_FACTOR"){
        audioGenerator->dJointToPitchFactor = (((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "JOINT_PITCH_OFFSET"){
        audioGenerator->dJointToPitchOffset = (((ofxUISlider*)e.getSlider())->getScaledValue());
    }
    else if(name == "VOLUME"){
        audioGenerator->volume = (((ofxUISlider*)e.getSlider())->getScaledValue());
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
    TreeNode * b1 = tree->addChild(parentJointOffset, dAngle, jointCount, length);
    
    addBranches(b0, dAngle * .8f, jointCount - parentJointOffset, len, depth - 1);
    addBranches(b1, dAngle * .8f, jointCount - parentJointOffset, len, depth - 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < kinematicUpdateRate; i++) tree->update();
    treeMesh->update();
    
    /*int bufferSize = (buffer->getWriteAvail() / 2) * 2; // prevent odd length
    float * tmpBuffer = new float[bufferSize];
    audioGenerator->process(tmpBuffer, bufferSize / 2, 2);
    buffer->write(tmpBuffer, bufferSize);
    delete[] tmpBuffer;*/
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(light.getDiffuseColor());
    
    
    ofEnableLighting();
    light.enable();
    treeMesh->draw();
    light.disable();
    ofDisableLighting();
    light.draw();
    tree->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(guiCode.pushKey(key)){
        gui->enable();
    } else if (key == 32){
        gui->disable();
    }
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
    light.setPosition(ofVec3f(ofGetWidth() / 2, 0, 100));
    tree->base.set(.5f * (float)w, .96f * (float)h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::audioRequested(float *output, int bufferSize, int nChannels){
    if (bufferSize * nChannels > buffer->getReadAvail()){
        ofLogNotice("Audio buffer underflow!");
    }
    buffer->read(output, min(bufferSize * nChannels, buffer->getReadAvail()));
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input,int bufferSize,int nChannels){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    gui->saveSettings("settings.xml");
    delete gui;
}
