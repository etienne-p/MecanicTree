//
//  Kinematics.cpp
//  ofForest
//
//  Created by etienne cella on 2014-12-06.
//
//

#include "Chain.h"

namespace Kinematic {

    Chain::Chain(float offset, int jointCount, float length){
        
        jointDelta = .5f;
        baseAngle = PI * -.5f;
        offsetAngle = offset;
        awakeDistance = 150.f;
        friction = .98f;
        maxUpdatesPerJoint = 24;
        
        float r = length / ((float)jointCount + 1.f);
        elements.clear();
        for (int i = 0; i < jointCount; i++){
            ChainElement elt;
            elt.joint = 0;
            elt.prevJoint = elt.joint;
            elt.link = r;
            elements.push_back(elt);
        }
        
        setDOF(1.6f, .8f);
        reset();
    };
    
    void Chain::setDOF(float initValue, float decreaseFactor){
        float dof = initValue;
        for (int i = elements.size() - 1; i > -1; i--){
            elements[i].dof = dof;
            dof *= decreaseFactor;
        }
    }
    
    void Chain::reset(){
        for (int i = 0, len = elements.size(); i < len; i++){
            elements[i].velocity = 0;
        }
        updatesForCurrentIndex = 0;
        error = FLT_MAX;
        cartesianPoints.resize(elements.size() + 1);
        updateCartesianPoints();
        elementIndex = elements.size() - 1;
    };
    
    void Chain::update(){
        if (cartesianPoints.back().distance(target) < awakeDistance){
            elements[elementIndex].velocity += .01f * evalJointDelta(target);
        } else {
            ofVec2f above = ofVec2f(cartesianPoints.back());
            above.y -= 1;
            elements[elementIndex].velocity += .01f * evalJointDelta(above);
        }
        for (int i = 0, len = elements.size(); i < len; i++){
            float dof = elements[i].dof;
            float joint = elements[i].joint;
            elements[i].prevJoint = joint;
            elements[i].joint = fmax(-dof, fmin(joint + elements[i].velocity, dof));
            elements[i].velocity *= friction;
        }
        updateCartesianPoints();
        bool hitDOF = abs(elements[elementIndex].joint) == elements[elementIndex].dof;
        float newError = target.distance(cartesianPoints.back());
        if (newError >= error || hitDOF || updatesForCurrentIndex > maxUpdatesPerJoint){
            elementIndex = elementIndex < 1 ? elements.size() - 1 : elementIndex - 1;
            updatesForCurrentIndex = 0;
        } else {
            updatesForCurrentIndex++;
        }
        error = newError;
    };
    
    void Chain::draw(){
        for (int i = 0, len = elements.size(); i < len; i++){
            ofSetColor(i == elementIndex ? ofColor::red : ofColor::blue);
            ofLine(cartesianPoints[i], cartesianPoints[i + 1]);
            ofCircle(cartesianPoints[i], 2.f);
        }
        ofSetColor(ofColor::red);
        ofCircle(target, 2.f);
    };
    
    float Chain::evalAngleToTarget(ofVec2f target_){
        ofVec2f toTip = cartesianPoints.back() - cartesianPoints[elementIndex];
        ofVec2f toTarget = target_ - cartesianPoints[elementIndex];
        return toTip.angleRad(toTarget);
    };
    
    float Chain::evalJointDelta(ofVec2f target_){
        return min(jointDelta, max(-jointDelta, evalAngleToTarget(target_)));
    };
    
    float Chain::getAbsoluteAngle(int index){
        float angle = baseAngle + offsetAngle;
        for (int i = 0, len = elements.size(); i <= index; i++){
             angle += elements[i].joint;
        }
        return angle;
    }
    
    void Chain::updateCartesianPoints(){
        
        cartesianPoints[0].set(base);
        float offsetX = base.x, offsetY = base.y, angle = baseAngle + offsetAngle;
        
        for (int i = 0, len = elements.size(); i < len; i++){
            angle += elements[i].joint;
            offsetX += elements[i].link * cos(angle);
            offsetY += elements[i].link * sin(angle);
            cartesianPoints[i + 1].set(offsetX, offsetY);
        }
    };

}