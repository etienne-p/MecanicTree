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
    depthToRadiusFactor = 1.0f;
}

void TreeMesh::setTree(Tree * arg){
    tree = arg;
    resetVbo();
}

int TreeMesh::getResolution(){
    return resolution;
}

void TreeMesh::setResolution(int val){
    resolution = val;
    resetVbo();
}

void TreeMesh::resetVbo(){
    vertices.resize(tree->countElements() * verticesPerElement());
    normals.resize(vertices.size());
    vbo.clear();
    vbo.setVertexData(&vertices[0], vertices.size(), GL_DYNAMIC_DRAW);
    vbo.setNormalData(&normals[0], normals.size(), GL_DYNAMIC_DRAW);
}

void TreeMesh::update(){
    verticeIndex = 0;
    updateNode(tree, 0);
    vbo.updateVertexData(&vertices[0], vertices.size());
    vbo.updateNormalData(&normals[0], normals.size());
}

void TreeMesh::updateNode(Tree * node, int depth){
    depth += node->parentJointIndex;
    for (int i = 0, len = node->elements.size(); i < len; i++){
        updateTrianglesForElement(node->cartesianPoints[i], node->cartesianPoints[i + 1], depth + i);
    }
    for (int i = 0, len = node->childs.size(); i < len; i++){
        updateNode(node->childs[i], depth);
    }
}

void TreeMesh::draw(){
    vbo.draw(GL_TRIANGLES, 0, vertices.size());
}

void TreeMesh::updateTrianglesForElement(const ofVec2f & segA, const ofVec2f & segB, int depth){
    
    float ratio = .1f;
    float radius = (tree->elements.size() - depth) * depthToRadiusFactor;
    
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
    float dAngle = 360.0f / (float)resolution;
    for (int i = 0; i < resolution; i++){
        rot.makeRotate(i * dAngle, s);
        mPts[i].set(m + rot * forward);
    }
    
    for (int i = 0; i < resolution; i++){
        
        vertices[verticeIndex++].set(a);
        normals[verticeIndex].set(a - m);
        
        vertices[verticeIndex++].set(mPts[i]);
        normals[verticeIndex].set(mPts[i] - m);
        
        vertices[verticeIndex++].set(mPts[(i + 1) % resolution]);
        normals[verticeIndex].set(mPts[(i + 1) % resolution] - m);
        
        vertices[verticeIndex++].set(b);
        normals[verticeIndex].set(b - m);
        
        vertices[verticeIndex++].set(mPts[i]);
        normals[verticeIndex].set(mPts[i] - m);
        
        vertices[verticeIndex++].set(mPts[(i + 1) % resolution]);
        normals[verticeIndex].set(mPts[(i + 1) % resolution] - m);
    }
}



