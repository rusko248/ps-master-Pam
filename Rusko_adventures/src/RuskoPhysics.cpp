//
//  RuskoPhysics.cpp
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/4/13.
//
//

#include "RuskoPhysics.h"


RuskoPhysics::RuskoPhysics(float start){
    yInitial = start;
    yPos = yInitial;
    yVel = 0;
    yAccel = 0;
    onGround = true;
}

RuskoPhysics::~RuskoPhysics(){
    
}

void RuskoPhysics::jump(){
    if(onGround || boxContact){
    onGround = false;
        yPos += .33;
        yVel += 10;
        cout << "Jumping" << endl;
    }
}

void RuskoPhysics::setOnGround(bool groundContact){
    onGround = groundContact;
    yPos = yInitial;
}

void RuskoPhysics::setOnBox(bool boxContact){
    this->boxContact = boxContact;
}

void RuskoPhysics::reset(){
    yPos = yInitial;
    yVel = 0;
    yAccel = 0;
    onGround = true;
}

void RuskoPhysics::update(float timeStep){
    if(onGround || boxContact){
        yVel = 0;
        yAccel = 0;
    }else{
        yAccel = -9.8;
    }
    yVel = yVel + yAccel*timeStep;
    float deltaY = yVel*timeStep;
    yPos = yPos + deltaY;
}