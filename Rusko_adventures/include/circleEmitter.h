//
//  circleEmitter.h
//  assignment2
//
//  Created by Aaron Damashek on 5/21/13.
//
//

#ifndef __assignment2__circleEmitter__
#define __assignment2__circleEmitter__

#include <iostream>
#include "Emitter.h"
#include "math.h"
#include "Quaternion.h"

class circleEmitter : public Emitter
{
public:
    circleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    virtual void display();
    
protected:
    bool addParticle();
    virtual bool updateParticle(particle *p);
    float randomAngle();
    float radius;
    
};

#endif /* defined(__assignment2__circleEmitter__) */
