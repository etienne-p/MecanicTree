#pragma once

#include "ofMain.h"
#include "Tree.h"
#include "ofxUI.h"

using namespace Kinematic;

class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
    void draw();
    
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
    
    
    Tree * tree;
    void makeTree();
    void addBranches(TreeNode * tree, float dAngle, int jointCount, float length, int depth);
    
    ofxUICanvas * gui;
    void setupUI();
    void guiEvent(ofxUIEventArgs &e);
};
