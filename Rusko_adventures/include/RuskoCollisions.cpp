//
//  RuskoCollisions.cpp
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/5/13.
//
//

#define NOMINMAX
#define _USE_MATH_DEFINES

#include "RuskoCollisions.h"

RuskoCollisions::RuskoCollisions(Room *room){
    this->room = room;
    
    lateralMovement = true;
    fallIntoPit = false;
    //Set rusko bound
    ruskoBound = new ObsBound();
    ruskoBound->type = 'r';
    ruskoBound->bcir.radius = 1;
    ruskoBound->bcir.x = 0;
    ruskoBound->bcir.y = 0;
    ruskoBound->bcir.z = 0;
    
    room->getObList(obsList);
    numTorches = room->getNumTorches();
    numTorchesLit = 0;
    printf("num of torches is %i \n", numTorches);
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
    if(dead) return;
    if(fallIntoPit) return;
    lateralMovement = true;
    ruskoPhys->setOnBox(false);
    
    //if Rusko is on a pit
    if(room->isPit()){
        cout << "pit" << endl;
        fallIntoPit = true;
        ruskoPhys->setOnGround(false);
        ruskoPhys->setInPit(true);
        systemSound->die();
        return;
    }
    
    //if Rusko is on spikes
    if(room->isSpikes()){
        dead = true;
        systemSound->die();
        return;
    }
    
    //if Rusko falls in a pit
    if(!fallIntoPit){//test to see if rusko is on the floor
        float nextYDelta = ruskoPhys->yVel*1/10;
        if(fabs(worldPos.y - nextYDelta - FLOOR_POS) < .33){
            ruskoPhys->setOnGround(true);
        }
    }
    
    //if Rusko is in front of torch
    if(room->isTorch() >= 0){
        ObsBound* offendingObject = &obsList.at(room->isTorch());
        cout << room->isTorch() << endl;
        if(offendingObject->bcir.hit == false){
            cout << "Torch identified" << endl;
            //vector3 torchPos = vector3(offendingObject->bcir.x, offendingObject->bcir.y + offendingObject->bcir.radius, offendingObject->bcir.z);
            if(torchOn){
                numTorchesLit++; //one more torch has been lit
                if (numTorchesLit == numTorches) torchesAllLit = true;
                vector3 torchPos = vector3(offendingObject->bcir.x, offendingObject->bcir.y + .7, offendingObject->bcir.z);
                torchFire->addDisplayPos(torchPos);
                systemSound->lightTorch();
                cout << "Torch lit" << endl;
            }
        }
        offendingObject->bcir.hit = true;
    }
    
    //if Rusko is about to walk into box
    if (room->isWalkToBox()){
        cout << "in front of box" << endl;
        lateralMovement = false;
    } else lateralMovement = true;
    
    
    for(int obj = 0; obj < obsList.size(); obj++){
        if(colliding(ruskoBound, &obsList.at(obj))){
            //reactToCollision(&obsList.at(obj));
            return;//???
        }
    }

	room->getObList(obsList);
}

void RuskoCollisions::reactToCollision(ObsBound* offendingObject){
    char type = offendingObject->type;
    switch (type) {
		case TORCH:{
            //if(offendingObject->bcir.hit == false){
//                cout << "Torch identified" << endl;
//                numTorchesLit++; //one more torch has been lit
//                if (numTorchesLit == numTorches) {
//                    torchesAllLit = true;   
//                }
                
                //vector3 torchPos = vector3(offendingObject->bcir.x, offendingObject->bcir.y + offendingObject->bcir.radius, offendingObject->bcir.z);
//                if(torchOn){
//                    vector3 torchPos = vector3(offendingObject->bcir.x, offendingObject->bcir.y + .7, offendingObject->bcir.z);
//                    torchFire->addDisplayPos(torchPos);
//                    systemSound->lightTorch();
//                    cout << "Torch lit" << endl;
//                }
            //}
            //offendingObject->bcir.hit = true;
			break;
        }
		case BOX:{
            float boxEpsilon = ruskoBound->bcir.radius * .5;
            boxEpsilon = 1;
            float relativePos = offendingObject->bcir.y + worldPos.y;
            float radiusSum = ruskoBound->bcir.radius + offendingObject->bcir.radius;
            
            float ruskoBottom = ruskoBound->bcir.y - ruskoBound->bcir.radius;
            float boxTop = offendingObject->bcir.y + worldPos.y + offendingObject->bcir.radius;
            float boxTop2 = boxTop + (ruskoPhys->yVel + ruskoPhys->yAccel*ruskoPhys->tStep)*ruskoPhys->tStep;
        
            float ruskoTop = ruskoBound->bcir.y + ruskoBound->bcir.radius;
            float boxBottom = offendingObject->bcir.y + worldPos.y - offendingObject->bcir.radius;
            float boxBottom2 = boxBottom + (ruskoPhys->yVel + ruskoPhys->yAccel*ruskoPhys->tStep)*ruskoPhys->tStep;
            
            if(ruskoBottom > boxTop2 && ruskoBottom < boxTop){
                ruskoPhys->setOnBox(true);
                ruskoPhys->yPos = boxTop - worldPos.y + ruskoBound->bcir.radius;
                return;
            }else if(ruskoTop > boxBottom2 && ruskoTop < boxBottom){
                ruskoPhys->yVel = 0;
            }else{
                lateralMovement = false;//Set can't move in x or z
            }
            /*
             if((ruskoBound->bcir.y - (relativePos)) >= (radiusSum - boxEpsilon)){//above box
                 cout << "Above" << endl;
                 ruskoPhys->yVel = 0;
                 ruskoPhys->setOnBox(true);
             }else if((relativePos - ruskoBound->bcir.y) >= (radiusSum - boxEpsilon)){//below box
                ruskoPhys->yVel = 0;
                 cout << "Below" << endl;
             }else if((ruskoBound->bcir.y - (relativePos + ruskoPhys->yVel*ruskoPhys->tStep)) >= (radiusSum - boxEpsilon)){
                 cout << "Above" << endl;
                 ruskoPhys->yVel = 0;
                 ruskoPhys->setOnBox(true);
             }
             else{//hitting the side of the box
                 lateralMovement = false;//Set can't move in x or z
             }
             */
			break;
        }
            /*
		case SPIKES:
            cout << "spikes" << endl;
            dead = true;
            systemSound->die();
			break;
		case PIT:
            cout << "pit" << endl;
            dead = true;
            fallIntoPit = true;
            ruskoPhys->setOnGround(false);
            systemSound->die();
			break;
             */
    }
}

void RuskoCollisions:: reset(){
    fallIntoPit = false;
    torchesAllLit = false;
}