//
//  pointEmitter.h
//  assignment2
//
//  Created by Aaron Damashek on 5/21/13.
//
//

#ifndef __assignment2__pointEmitter__
#define __assignment2__pointEmitter__

#include <iostream>
#include "Emitter.h"

class pointEmitter : public Emitter
{
public:
    pointEmitter(particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    virtual void display();
    
protected:
    bool addParticle();
    
};
#endif /* defined(__assignment2__pointEmitter__) */
