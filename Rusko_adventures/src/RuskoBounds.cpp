//
//  RuskoBounds.cpp
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/5/13.
//
//

#include "RuskoBounds.h"

RuskoBounds::RuskoBounds(){
    obsList = new vector<ObsBound*>();
}

RuskoBounds::~RuskoBounds(){
    
}

void RuskoBounds::setRoom(Room* room){
    this->room = room;
    floorBounds = room->getFloor();
}

void RuskoBounds:: reset(){
    
}

bool RuskoBounds::inBounds(){
    
}

bool RuskoBounds::inBounds(STVector3 futurePos){
    float fwidth = floorBounds->fwidth;
    float flength = floorBounds->flength;
    if (futurePos.x <= -fwidth || futurePos.x >= 0) return false;
    if (futurePos.z >= flength || futurePos.z <= 0) return false;
    return true;
}