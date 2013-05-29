//
//  Emitter.cpp
//  assignment2
//
//  Created by Aaron Damashek on 5/8/13.
//
//

#include "Emitter.h"

Emitter::Emitter(particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force){
    
    e = new emitter;
    e->emitter_id = emitter_id;
    e->pos = pos;
    //e->yaw = yaw;
    //e->yawVar = yawVar;
    //e->pitch = pitch;
    //e->pitchVar = pitchVar;
    e->dir = dir;
    e->dirVar = dirVar;
    e->speed = speed;
    e->speedVar = speedVar;
    e->totalParticles = totalParticles;
    e->particleList = NULL;
    e->particleCount = 0;
    e->emitsPerFrame = emitsPerFrame;
    e->emitVar = emitVar;
    e->life = life;
    e->lifeVar = lifeVar;
    e->force = force;
    
    managerParticleList = pool;
}

inline float Emitter::randDist(){
    float r = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
    return r;
}

void Emitter::rotationToDirection(float pitch, float yaw, vector3 *direction){
    direction->x = -sin(yaw) * cos(pitch);
    direction->y = sin(pitch);
    direction->z = cos(pitch) * cos(yaw);
}

bool Emitter::addParticle(){
    particle *newParticle;
    float speed;
    //Particle pool exists and max num particles not exceeded
    if(e != NULL && *managerParticleList != NULL && e->particleCount < e->totalParticles){
        newParticle = *managerParticleList;
        *managerParticleList = (*managerParticleList)->next;
        if(e->particleList != NULL){
            e->particleList->prev = newParticle;
        }
        newParticle->next = e->particleList;
        newParticle->prev = NULL;
        e->particleList = newParticle;
        
        newParticle->pos.x = e->pos.x;
        newParticle->pos.y = e->pos.y;
        newParticle->pos.z = e->pos.z;
        
        newParticle->prevPos.x = 0;
        newParticle->prevPos.y = 0;
        newParticle->prevPos.z = 0;
        
        //Calculate direction vector
        //yaw = e->yaw + (e->yawVar*randDist());
        //pitch = e->pitch + (e->pitchVar*randDist());
        //rotationToDirection(pitch, yaw, &newParticle->dir);
        newParticle->dir = e->dir + (e->dirVar*randDist());
        
        speed = e->speed + (e->speed * randDist());
        newParticle->dir.x *= speed;
        newParticle->dir.y *= speed;
        newParticle->dir.z *= speed;
        
        
        newParticle->life = e->life + (int)((float)e->lifeVar * randDist());
        
        newParticle->side = randDist();
        e->particleCount++;
        return true;
    }
    return false;
}

bool Emitter::updateParticle(particle *p){
    if(p != NULL && p->life > 0){
        p->prevPos.x = p->pos.x;
        p->prevPos.y = p->pos.y;
        p->prevPos.z = p->pos.z;
        
        p->dir = p->dir*(fmax((p->life),e->life/1.1)/(float)e->life);
        
        p->pos.x += p->dir.x;
        p->pos.y += p->dir.y;
        p->pos.z += p->dir.z;
        
        p->dir.x += e->force.x*cosf(p->pos.y)*p->side;
        p->dir.y += e->force.y*cosf(p->pos.y)*p->side;
        p->dir.z += e->force.z*cosf(p->pos.y)*p->side;
        
        p->life--;
        return true;
    }else if(p != NULL && p->life == 0){
        if(p->prev != NULL){
            p->prev->next = p->next;
        }else{
            e->particleList = p->next;
        }
        if(p->next != NULL){
            p->next->prev = p->prev;
        }
        p->next = *managerParticleList;
        p->prev = NULL;
        *managerParticleList = p;
        e->particleCount--;
    }
    
    return false;
}

void Emitter::display(){
    for(int newP = 0; newP < (e->emitsPerFrame + e->emitVar*randDist()); newP++){
        addParticle();
    }
    glPointSize(2);
    glBegin(GL_POINTS);
    particle *curr = e->particleList;
    while(curr){
        glVertex3f(curr->pos.x, curr->pos.y, curr->pos.z);
        curr = curr->next;
    }
    glEnd();
}

Emitter::~Emitter(){
    particle *curr = e->particleList;
    while(curr){
        particle *toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    delete e;
}

void Emitter::update(){
    particle *curr = e->particleList;
    while(curr){
        particle *toUpdate = curr;
        curr = curr->next;
        updateParticle(toUpdate);
    }
}

void Emitter::resetPos(vector3 newPos){
    e->pos = newPos;
}