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
    tStep = 0;
}

RuskoPhysics::~RuskoPhysics(){
    
}

void RuskoPhysics::jump(bool moving){
    movingDuringJump = moving;
    if(onGround || boxContact){
        onGround = false;
        boxContact = false;
        yPos += 1;
        yVel += 6;
    }
}

void RuskoPhysics::setOnGround(bool groundContact){
    onGround = groundContact;
    yPos = yInitial;
}

void RuskoPhysics::setOnBox(bool boxContact){
    this->boxContact = boxContact;
    if(boxContact){
        yVel = 0;
        yAccel = 0;
    }
}

void RuskoPhysics::reset(){
    yPos = yInitial;
    yVel = 0;
    yAccel = 0;
    onGround = true;
    inPit = false;
}

void RuskoPhysics::setInPit(bool pitContact){
    inPit = pitContact;
}

void RuskoPhysics::update(float timeStep){
    tStep = timeStep;
    if(onGround || boxContact){
        yVel = 0;
        yAccel = 0;
        jumpOn = false;
    }else{
        yAccel = -9.8;
    }
    yVel = yVel + yAccel*timeStep;
    float deltaY = yVel*timeStep;
    yPos = yPos + deltaY;
    if(yPos < 1 && !boxContact && !inPit){
        cout << "setting ground" << endl;
        setOnGround(true);
    }
    if(yPos < -10) dead = true;
}