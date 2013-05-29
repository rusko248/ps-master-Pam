//
//  Emitter.h
//  assignment2
//
//  Created by Aaron Damashek on 5/8/13.
//
//

#ifndef __assignment2__Emitter__
#define __assignment2__Emitter__

#include <iostream>
#include <cmath>
#include "stglew.h"
#ifdef __APPLE__
#define GLEW_VERSION_2_0 1
#else
#define GLEW_STATIC 1
#include "GL/glew.h"
#endif

#include "ParticleStructs.h"

class Emitter
{
public:
	Emitter(particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    ~Emitter();
    void update();
    virtual void display();
    void resetPos(vector3 newPos);
protected:
    particle **managerParticleList;
    emitter *e;
    void rotationToDirection(float pitch, float yaw, vector3 *direction);
    virtual bool addParticle();
    virtual bool updateParticle(particle *p);
    inline float randDist();
};


#endif /* defined(__assignment2__Emitter__) */
