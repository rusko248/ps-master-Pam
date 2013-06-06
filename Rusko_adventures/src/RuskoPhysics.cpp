//
//  RuskoPhysics.cpp
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/4/13.
//
//

#include "RuskoPhysics.h"


RuskoPhysics::RuskoPhysics(float start){
    yPos = start;
    yVel = 0;
    yAccel = 0;
    onGround = true;
}

RuskoPhysics::~RuskoPhysics(){
    
}

void RuskoPhysics::jump(){
    onGround = false;
    yVel += 10;
    cout << "Jumping" << endl;
}

void RuskoPhysics::setOnGround(bool groundContact){
    onGround = groundContact;
}

void RuskoPhysics::reset(float start){
    yPos = yPos;
    yVel = 0;
    yAccel = 0;
    onGround = true;
}

void RuskoPhysics::update(float timeStep){
    if(onGround){
        yVel = 0;
        yAccel = 0;
    }else{
        yAccel = -9.8;
    }
    yVel = yVel + yAccel*timeStep;
    yPos = yPos + yVel*timeStep;
}