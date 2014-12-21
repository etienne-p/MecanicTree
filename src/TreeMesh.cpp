//
//  ChainMesh.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-19.
//
//

#include "TreeMesh.h"

TreeMesh::TreeMesh(){
    resolution = 4;
}

void TreeMesh::setTree(Tree * arg){
    tree = arg;
    vertices.resize(tree->countElements() * verticesPerElement());
    vbo.clear();
    vbo.setVertexData(&vertices[0], vertices.size(), GL_DYNAMIC_DRAW);
}

void TreeMesh::update(){
    verticeIndex = 0;
    updateNode(tree);
    vbo.updateVertexData(&vertices[0], vertices.size());
}

void TreeMesh::updateNode(Tree * node){
    for (int i = 0, len = node->cartesianPoints.size() - 1; i < len; i++){
        updateTrianglesForElement(node->cartesianPoints[i], node->cartesianPoints[i + 1]);
    }
    for (int i = 0, len = node->childs.size(); i < len; i++){
        updateNode(node->childs[i]);
    }
}

void TreeMesh::draw(){
    vbo.draw(GL_TRIANGLES, 0, vertices.size());
}

void TreeMesh::updateTrianglesForElement(const ofVec2f & segA, const ofVec2f & segB){
    
    float ratio = .5f;
    float radius = 5.0f;
    
    ofVec3f a = segA;
    ofVec3f b = segB;
    ofVec3f forward(0, 0, 1);
    ofVec3f s = b - a;
    ofVec3f m = a + ratio * s;
    
    forward.cross(b - a);
    forward.normalize();
    forward *= radius;
    
    ofQuaternion rot;
    vector<ofVec3f> mPts(resolution);
    
    // mid vertex
    for (int i = 0; i < resolution; i++){
        rot.makeRotate(i * 360.0f / (float)resolution, s);
        mPts[i] = m;// + rot * forward;
    }
    
    for (int i = 0; i < resolution; i++){
        vertices[verticeIndex++].set(a);
        vertices[verticeIndex++].set(mPts[i]);
        vertices[verticeIndex++].set(mPts[i + 1]);
        vertices[verticeIndex++].set(b);
        vertices[verticeIndex++].set(mPts[i]);
        vertices[verticeIndex++].set(mPts[i + 1]);
    }
}



