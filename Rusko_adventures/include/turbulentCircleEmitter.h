//
//  turbulentCircleEmitter.h
//  Particles
//
//  Created by Aaron Damashek on 5/28/13.
//
//

#ifndef __Particles__turbulentCircleEmitter__
#define __Particles__turbulentCircleEmitter__

#include <iostream>
#include "circleEmitter.h"
#include "math.h"

class turbulentCircleEmitter : public circleEmitter
{
public:
    turbulentCircleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    void display();
    
private:
    bool updateParticle(particle *p);
    bool addParticle();
};
#endif /* defined(__Particles__turbulentCircleEmitter__) */
