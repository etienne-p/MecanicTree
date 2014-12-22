#pragma once

#include "ofMain.h"
#include "Tree.h"
#include "TreeMesh.h"
#include "Sonify.h"
#include "ofxUI.h"
#include "RingBuffer.h"
#include "KonamiCode.h"

class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float rootLength;
    float rootNodeCount;
    int parentJointOffset;
    int branchDepth;
    float branchAngleOffset;
    int kinematicUpdateRate;
    
    Tree * tree;
    TreeMesh * treeMesh;
    void makeTree();
    void addBranches(TreeNode * tree, float dAngle, int jointCount, float length, int depth);
    
    ofLight light;
    
    ofxUICanvas * gui;
    void setupUI();
    void guiEvent(ofxUIEventArgs &e);
    
    void syncBranchesParamsOnGui();
    
    AudioGenerator * audioGenerator;
    
    void audioRequested(float * output, int bufferSize, int nChannels);
    void audioReceived(float * input, int bufferSize, int nChannels);
    ofSoundStream soundStream;
    RingBuffer<float> * buffer;
    
    KonamiCode guiCode;
    
    ofMaterial material;
    ofColor materialColor;
    
    
};
