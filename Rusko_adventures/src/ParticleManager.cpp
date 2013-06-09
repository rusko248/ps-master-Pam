//
//  ParticleManager.cpp
//  assignment2
//
//  Created by Aaron Damashek on 5/14/13.
//
//

#include "ParticleManager.h"

void ParticleManager::createParticleList(int max){
    pthread_mutex_lock(&mutex);
    particle *head = new particle;
    head->prev = NULL;
    head->next = NULL;
    particlePool = head;
    particle *curr = head;
    for(int i = 0; i < max; i++){
        particle *newParticle = new particle;
        newParticle->prev = curr;
        newParticle->next = NULL;
        curr->next = newParticle;
        curr = curr->next;
    }
    pthread_mutex_unlock(&mutex);
}

ParticleManager::~ParticleManager(){
    pthread_mutex_lock(&mutex);
    particle *curr = particlePool;
    while(curr){
        particle *toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
    for(int e = 0; e < emitters.size(); e++){
        delete emitters[e];
    }
    pthread_mutex_unlock(&mutex);
}

void ParticleManager::reset(){
    pthread_mutex_lock(&mutex);
    
    int particlesLost = 0;
    
    for(int e = 0; e < emitters.size(); e++){
        particlesLost += emitters[e]->e->totalParticles;
        delete (Emitter*)emitters[e];
    }
    emitters.clear();
    
    for(int i = 0; i < particlesLost; i++){
        particle *newParticle = new particle;
        newParticle->prev = NULL;
        newParticle->next = particlePool;
        particlePool = newParticle;
    }
    
    pthread_mutex_unlock(&mutex);
    
}

ParticleManager::ParticleManager(int max){
    createParticleList(max);
}

void ParticleManager::addEmitter(vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force){
    pthread_mutex_lock(&mutex);
    int id = emitters.size();
    Emitter *e = new Emitter(&particlePool, id, pos, dir, dirVar, speed, speedVar, totalParticles, emitsPerFrame, emitVar, life, lifeVar, force);
    emitters.push_back(e);
    pthread_mutex_unlock(&mutex);
}

/*Subclasses use this version*/
void ParticleManager::addEmitter(Emitter *e){
    emitters.push_back(e);
}

/*Update all emitters on the frame*/
void ParticleManager::update(){
    pthread_mutex_lock(&mutex);
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->update();
    }
    pthread_mutex_unlock(&mutex);
}

/*Display all emitters on the frame*/
void ParticleManager::display(){
    pthread_mutex_lock(&mutex);
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->display();
    }
    pthread_mutex_unlock(&mutex);
}

/*Display all emitters on the frame*/
int ParticleManager::nextId(){
    return emitters.size();
}

void ParticleManager::resetPos(int emitter, vector3 newPos){
    pthread_mutex_lock(&mutex);
    if(emitter < emitters.size()){
        emitters[emitter]->resetPos(newPos);
    }
    pthread_mutex_unlock(&mutex);
}

void ParticleManager::resetRelativePos(int emitter, vector3 newPos){
    pthread_mutex_lock(&mutex);
    if(emitter < emitters.size()){
        vector3 updatedPosition = vector3(emitters[emitter]->e->pos.x + newPos.x, emitters[emitter]->e->pos.y + newPos.y, emitters[emitter]->e->pos.z + newPos.z);
        emitters[emitter]->resetPos(updatedPosition);
    }
    pthread_mutex_unlock(&mutex);
}