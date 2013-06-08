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

using namespace std;

class RuskoPhysics
{
public:
    RuskoPhysics(float start);
    ~RuskoPhysics();
    void jump();
    void update(float timeStep);
    void setOnGround(bool groundContact);
    void setOnBox(bool boxContact);
    void reset();
    float yPos;
    float yVel;
    
protected:
    float yInitial;
    float yAccel;
    bool onGround;
    bool boxContact;
    
};
#endif /* defined(__Rusko_adventures__RuskoPhysics__) */
