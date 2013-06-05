//
//  characterPhysics.cpp
//  libst
//
//  Created by Aaron Damashek on 6/4/13.
//
//

#include "CharacterPhysics.h"

CharacterPhysics::CharacterPhysics(float yPos){
    this->yPos = yPos;
    yVel = 0;
    yAccel = 0;
    onGround = true;
}

CharacterPhysics::~CharacterPhysics(){
    
}

void CharacterPhysics::jump(){
    onGround = false;
    yVel += 3;
}

void CharacterPhysics::setOnGround(bool groundContact){
    onGround = groundContact;
}

void CharacterPhysics::reset(float yPos){
    this->yPos = yPos;
    yVel = 0;
    yAccel = 0;
    onGround = true;
}

void CharacterPhysics::update(float timeStep){
    if(onGround){
        yVel = 0;
        yAccel = 0;
    }else{
        yAccel = -9.8;
    }
    yVel = yVel + yAccel*timeStep;
    yPos = yPos + yVel*timeStep;
}