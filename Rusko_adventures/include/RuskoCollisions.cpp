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
    
    lateralMovement = true;
    
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
    float distance = sqrtf(powf((one->bcir.x - (two->bcir.x + worldPos.x)), 2) + powf((one->bcir.y - (two->bcir.y + worldPos.y)), 2) + powf((one->bcir.z - (two->bcir.z + worldPos.z)), 2));
    float radiiSum = one->bcir.radius + two->bcir.radius;
    if(distance <= radiiSum) return true;
    return false;
}

void RuskoCollisions::checkForCollisions(){
    lateralMovement = true;
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
		case TORCH:{
            if(offendingObject->bcir.hit == false){
                cout << "Torch identified" << endl;
                fireCircleEmitter *torchFire = new fireCircleEmitter(&particles->particlePool, particles->nextId(), "../Particles/fireRecording.txt");
                vector3 torchPos = vector3(offendingObject->bcir.x + worldPos.x, offendingObject->bcir.y + worldPos.y + offendingObject->bcir.radius, offendingObject->bcir.z + worldPos.z);
                torchFire->resetPos(torchPos);
                particles->addEmitter(torchFire);
                systemSound->lightTorch();
            }
            offendingObject->bcir.hit = true;
			break;
        }
		case BOX:{

            float boxEpsilon = ruskoBound->bcir.radius * .2;

             if(ruskoBound->bcir.y - (offendingObject->bcir.y + worldPos.y) >= (ruskoBound->bcir.radius + offendingObject->bcir.radius) - boxEpsilon){//above box
                ruskoPhys->setOnGround(true);
             }
             if((offendingObject->bcir.y + worldPos.y) - ruskoBound->bcir.y >= (ruskoBound->bcir.radius + offendingObject->bcir.radius) - boxEpsilon){//below box
                ruskoPhys->yVel = 0;
             }
             else{//hitting the side of the box
                 lateralMovement = false;//Set can't move in x or z
             }
			break;
        }
		case SPIKES:
            systemSound->die();
			break;
		case PIT:
            systemSound->die();
			break;
    }
}

void RuskoCollisions:: reset(){
    
}