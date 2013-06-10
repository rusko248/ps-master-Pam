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
    if(boxContact){
        cout << "On Box" << endl;
        yVel = 0;
        yAccel = 0;
    }
}

void RuskoPhysics::reset(){
    yPos = yInitial;
    yVel = 0;
    yAccel = 0;
    onGround = true;
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
    if(yPos < 1 && !boxContact){
        cout << "setting ground" << endl;
        setOnGround(true);
    }
    cout << yPos << " " << yVel << " " << yAccel << endl;
}