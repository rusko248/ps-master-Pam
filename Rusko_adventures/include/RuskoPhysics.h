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

using namespace std;

class RuskoPhysics
{
public:
    RuskoPhysics(float start);
    ~RuskoPhysics();
    void jump();
    void update(float timeStep);
    void setOnGround(bool groundContact);
    void reset(float start);
    float yPos;
    float yVel;
    
protected:
    float yAccel;
    bool onGround;
    
};
#endif /* defined(__Rusko_adventures__RuskoPhysics__) */
