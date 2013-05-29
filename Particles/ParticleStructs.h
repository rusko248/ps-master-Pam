//
//  ParticleStructs.h
//  assignment2
//
//  Created by Aaron Damashek on 5/8/13.
//
//

#include "Basic.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef assignment2_ParticleStructs_h
#define assignment2_ParticleStructs_h

//Add textures, transparency, size, and shape, acceleration
struct particle {
    particle *prev, *next;
    vector3 pos;
    vector3 prevPos;
    vector3 dir;
    int life;
    float side;
};

//generation shapes
struct emitter {
    int emitter_id;
    vector3 pos;
    vector3 dir;
    vector3 dirVar;
    float yaw, yawVar;
    float pitch, pitchVar;
    float speed, speedVar;
    particle *particleList;
    int totalParticles;
    int particleCount;
    int emitsPerFrame, emitVar;
    int life, lifeVar;
    vector3 force;
    
};

#endif
