//
//  ChainMesh.h
//  ofForest
//
//  Created by Etienne on 2014-12-19.
//
//

#ifndef __ofForest__ChainMesh__
#define __ofForest__ChainMesh__

#include "ofMain.h"
#include "ofVbo.h"
#include "Tree.h"

class TreeMesh {

public:

    TreeMesh();
    void setTree(Tree * arg);
    void update();
    void draw();
    int getResolution();
    void setResolution(int val);
    
    float depthToRadiusFactor;
    float radiusOffset;
    
private:
    void resetVbo();
    void updateNode(Tree * node, int depth);
    void updateTrianglesForElement(const ofVec2f & segA, const ofVec2f & segB, int depth);
    inline int verticesPerElement(){
        return resolution * 6;
    }
    int resolution;
    int verticeIndex;
    vector<ofVec3f> vertices;
    vector<ofVec3f> normals;
    ofVbo vbo;
    Tree * tree;
    
};

#endif /* defined(__ofForest__ChainMesh__) */
