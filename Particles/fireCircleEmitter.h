//
//  fireCircleEmitter.h
//  assignment2
//
//  Created by Aaron Damashek on 5/21/13.
//
//

#ifndef __assignment2__fireCircleEmitter__
#define __assignment2__fireCircleEmitter__

#include <iostream>
#include "circleEmitter.h"
#include "math.h"

class fireCircleEmitter : public circleEmitter
{
public:
    fireCircleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    void display();
    
private:
    
};
#endif /* defined(__assignment2__fireCircleEmitter__) */
