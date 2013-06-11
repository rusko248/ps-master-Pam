//
//  RuskoCollisions.h
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/5/13.
//
//

#ifndef __Rusko_adventures__RuskoCollisions__
#define __Rusko_adventures__RuskoCollisions__

#include <iostream>

#include "Framework.h"
#include "Room.h"
#include "ParticleManager.h"
#include "Sound.h"
#include "RuskoPhysics.h"

extern ParticleManager *particles;
extern RuskoPhysics *ruskoPhys;
extern Sound *systemSound;

extern const int FLOOR_POS;
extern STVector3 worldPos;
extern STVector3 futurePos;

extern float worldAngle;

extern bool dead;
extern bool torchOn;

extern fireCircleEmitter *torchFire;

using namespace std;

class RuskoCollisions
{
public:
    RuskoCollisions(Room* room);
    ~RuskoCollisions();
    void checkForCollisions();
    void reset();
    bool lateralMovement;
    bool torchesAllLit;
    
protected:
    bool collisionOccuring;
    bool colliding(ObsBound *one, ObsBound *two);
    void reactToCollision(ObsBound* offendingObject);
    Room* room;
    ObsBound *ruskoBound;
    vector<ObsBound> obsList;
    bool fallIntoPit;
    
    int numTorches;
    int numTorchesLit;
    
};

#endif /* defined(__Rusko_adventures__RuskoCollisions__) */
