//
//  ParticleManager.h
//  assignment2
//
//  Created by Aaron Damashek on 5/14/13.
//
//

#ifndef __assignment2__ParticleManager__
#define __assignment2__ParticleManager__

#include <iostream>
#include <vector>
#include "ParticleStructs.h"
#include "Emitter.h"
#include "pointEmitter.h"
#include "circleEmitter.h"
#include "fireCircleEmitter.h"
#include "windCircleEmitter.h"

class ParticleManager
{
public:
	ParticleManager(int max);
    ~ParticleManager();
    void addEmitter(vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    void addEmitter(Emitter *e);
    void update();
    void display();
    int nextId();
    particle *particlePool;
    void resetPos(int emitter, vector3 newPos);
private:
    int maxParticles;
    void createParticleList(int max);
    std::vector<Emitter*> emitters;
};

#endif /* defined(__assignment2__ParticleManager__) */
