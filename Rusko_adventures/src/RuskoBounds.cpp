//
//  RuskoBounds.cpp
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/5/13.
//
//

#define NOMINMAX
#define _USE_MATH_DEFINES

#include "RuskoBounds.h"

RuskoBounds::RuskoBounds(){
}

RuskoBounds::~RuskoBounds(){
    
}

void RuskoBounds::setRoom(Room* room){
    this->room = room;
    floorBounds = room->getFloor();
}


bool RuskoBounds::inBounds(STVector3 futurePos){
    float fwidth = floorBounds->fwidth;
    float flength = floorBounds->flength;
    if (futurePos.x <= -fwidth || futurePos.x >= 0) return false;
    if (futurePos.z >= flength || futurePos.z <= 0) return false;
    return true;
}