//
//  RuskoCollisions.cpp
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/5/13.
//
//

#include "RuskoCollisions.h"

RuskoCollisions::RuskoCollisions(Room *room){
    this->room = room;
    
    //Set rusko bound
    ruskoBound = new ObsBound();
    ruskoBound->type = 'r';
    ruskoBound->bcir.radius = 1;
    ruskoBound->bcir.x = 0;
    ruskoBound->bcir.y = 0;
    ruskoBound->bcir.z = 0;
    
    room->getObList(obsList);
}

RuskoCollisions::~RuskoCollisions(){

}

bool RuskoCollisions::colliding(ObsBound *one, ObsBound *two){
    //Collision occurs if distance between centers is less than or equal to sum of radii
    float distance = sqrtf(powf((one->bcir.x - two->bcir.x), 2) + powf((one->bcir.y - two->bcir.y), 2) + powf((one->bcir.z - two->bcir.z), 2));
    float radiiSum = one->bcir.radius + two->bcir.radius;
    if(distance <= radiiSum) return true;
    return false;
}

void RuskoCollisions::checkForCollisions(){
    for(int obj = 0; obj < obsList.size(); obj++){
        if(colliding(ruskoBound, &obsList.at(obj))){
            reactToCollision(&obsList.at(obj));
            return;//???
        }
    }
}

void RuskoCollisions::reactToCollision(ObsBound* offendingObject){
    char type = offendingObject->type;
    switch (type) {
		case TORCH:
			break;
		case BOX:
            //if above box
            //if below box
            //if hitting the side of the box
			break;
		case SPIKES:
			break;
		case PIT:
			break;
    }
}

void RuskoCollisions:: reset(){
    
}