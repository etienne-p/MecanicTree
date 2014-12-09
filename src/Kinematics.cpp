//
//  Kinematics.cpp
//  ofForest
//
//  Created by etienne cella on 2014-12-06.
//
//

#include "Kinematics.h"

namespace Kinematic {

    Chain::Chain(float offset, int len){
        
        base.set(400.f, 400.f);
        dJoint = .1f;
        baseAngle = PI * -.5f;
        offsetAngle = offset;
        
        float r = 16.f;
        float d = .1f;
        elements.clear();
        for (int i = 0; i < len; i++){
            ChainElement elt;
            elt.joint = 0;
            //r *= .9f;
            //d *= 1.1f;
            elt.link = r;
            elt.dof = d;
            elements.push_back(elt);
        }
        
        reset();
    };
    
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
        elements[elementIndex].velocity += .01f * evalJointDelta();
        for (int i = 0, len = elements.size(); i < len; i++){
            elements[i].joint += elements[i].velocity;
            elements[i].joint = min(elements[i].joint, elements[i].dof);
            elements[i].joint = max(elements[i].joint, -elements[i].dof);
            elements[i].velocity *= .9f;
        }
        updateCartesianPoints();
        bool hitDOF = abs(elements[elementIndex].joint) == elements[elementIndex].dof;
        float newError = target.distance(cartesianPoints.back());
        if (newError > error || hitDOF || updatesForCurrentIndex > 48){
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
            ofCircle(cartesianPoints[i], 4.f);
        }
        ofSetColor(ofColor::red);
        ofCircle(target, 4.f);
    };
    
    float Chain::evalAngleToTarget(){
        ofVec2f toTip = cartesianPoints.back() - cartesianPoints[elementIndex];
        ofVec2f toTarget = target - cartesianPoints[elementIndex];
        return toTip.angleRad(toTarget);
    };
    
    float Chain::evalJointDelta(){
        return min(dJoint, max(-dJoint, evalAngleToTarget()));
    };
    
    float Chain::getAbsoluteAngle(int index){
        
        float angle = baseAngle + offsetAngle;

        for (int i = 0, len = elements.size(); i < len; i++){
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