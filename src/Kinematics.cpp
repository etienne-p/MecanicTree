//
//  Kinematics.cpp
//  ofForest
//
//  Created by etienne cella on 2014-12-06.
//
//

#include "Kinematics.h"

namespace Kinematic {

    Chain::Chain(){
        
        base.set(200.f, 200.f);
        dJoint = .1f;
        
        float r = 100.f;
        float d = 0.4;
        elements.clear();
        for (int i = 0; i < 8; i++){
            ChainElement elt;
            elt.joint = 0;
            r *= .8f;
            elt.link = r;
            elements.push_back(elt);
        }
        
        reset();
    };
    
    void Chain::reset(){
        cartesianPoints.resize(elements.size() + 1);
        updateCartesianPoints();
        elementIndex = elements.size() - 1;
    };
    
    void Chain::update(){
        elements[elementIndex].joint += evalJointDelta();
        updateCartesianPoints();
        elementIndex = elementIndex < 1 ? elements.size() - 1 : elementIndex - 1;
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
    
    void Chain::updateCartesianPoints(){
        
        cartesianPoints[0].set(base);
        float offsetX = base.x, offsetY = base.y, angle = 0;
        
        for (int i = 0, len = elements.size(); i < len; i++){
            angle += elements[i].joint;
            offsetX += elements[i].link * cos(angle);
            offsetY += elements[i].link * sin(angle);
            cartesianPoints[i + 1].set(offsetX, offsetY);
        }
    };

}