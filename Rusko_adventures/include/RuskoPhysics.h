//
//  RuskoPhysics.h
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/4/13.
//
//

#ifndef __Rusko_adventures__RuskoPhysics__
#define __Rusko_adventures__RuskoPhysics__

#include <iostream>
#include "ParticleManager.h"
#include "RuskoPhysics.h"
#include "Sound.h"

extern Sound *systemSound;

extern ParticleManager *particles;

extern bool jumpOn;
extern bool dead;

using namespace std;

class RuskoPhysics
{
public:
    RuskoPhysics(float start);
    ~RuskoPhysics();
    void jump(bool moving);
    void update(float timeStep);
    void setOnGround(bool groundContact);
    void setOnBox(bool boxContact);
    void setInPit(bool pitContact);
    void reset();
    float yPos;
    float yVel;
    float yAccel;
    bool movingDuringJump;
    float tStep;
    
    bool boxContact; //moved here to access for collisions

    
protected:
    float yInitial;
    bool onGround;
    //bool boxContact;
    bool inPit;
    
};
#endif /* defined(__Rusko_adventures__RuskoPhysics__) */
