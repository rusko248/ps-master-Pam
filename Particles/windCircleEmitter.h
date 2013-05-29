//
//  windCircleEmitter.h
//  Particles
//
//  Created by Aaron Damashek on 5/23/13.
//
//

#ifndef __Particles__windCircleEmitter__
#define __Particles__windCircleEmitter__

#include <iostream>
#include "circleEmitter.h"
#include "math.h"

class windCircleEmitter : public circleEmitter
{
public:
    windCircleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    void display();
    
private:
    bool updateParticle(particle *p);
};
#endif /* defined(__Particles__windCircleEmitter__) */
