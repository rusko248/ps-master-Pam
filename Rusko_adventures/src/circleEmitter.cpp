//
//  circleEmitter.cpp
//  assignment2
//
//  Created by Aaron Damashek on 5/21/13.
//
//

#include "circleEmitter.h"


circleEmitter::circleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force) : Emitter(pool, emitter_id, pos, dir, dirVar, speed, speedVar, totalParticles, emitsPerFrame, emitVar, life, lifeVar, force){
    radius = r;
}

void circleEmitter::display(){
    if(!displaying) return;
    for(int newP = 0; newP < (e->emitsPerFrame + e->emitVar*randDist()); newP++){
        addParticle();
    }
    glPointSize(2);
    glBegin(GL_POINTS);
    particle *curr = e->particleList;
    while(curr){
        if(displaying == false) std::cout << "Here" << std::endl;
        glVertex3f(curr->pos.x, curr->pos.y, curr->pos.z);
        curr = curr->next;
    }
    glEnd();
}

float circleEmitter::randomAngle(){
    float angle = 2.0f * 3.14159265 * ((float)rand() / (float)RAND_MAX);
    return angle;
}

bool circleEmitter::addParticle(){
    particle *newParticle;
    float speed;
    //Particle pool exists and max num particles not exceeded
    if(e != NULL && *managerParticleList != NULL && e->particleCount < e->totalParticles && emitting){
        newParticle = *managerParticleList;
        *managerParticleList = (*managerParticleList)->next;
        if(e->particleList != NULL){
            e->particleList->prev = newParticle;
        }
        newParticle->next = e->particleList;
        newParticle->prev = NULL;
        e->particleList = newParticle;
        
        float angle = randomAngle();
        float radScalar = randDist();
        newParticle->rand = radScalar;
        newParticle->radius = radius * radScalar;
        STVector3 point = STVector3(e->pos.x + radius*radScalar*cosf(angle), e->pos.y, e->pos.z + radius*radScalar*sinf(angle));
        STVector3 straightUp = STVector3(0,1,0);
        STVector3 circleDir = STVector3(e->dir.x, e->dir.y, e->dir.z);
        

        STVector3 a  = STVector3::Cross(straightUp, circleDir);
        float w = sqrt(powf(straightUp.Length(), 2) * powf(circleDir.Length(), 2)) + STVector3::Dot(straightUp, circleDir);
        Quaternion rotateCircle = Quaternion(w, a.x, a.y, a.z);
        rotateCircle.Normalize();

        STVector3 rotatedPoint = rotateCircle.rotate(point, rotateCircle);
        newParticle->pos.x = rotatedPoint.x;
        newParticle->pos.y = rotatedPoint.y;
        newParticle->pos.z = rotatedPoint.z;

/*
        newParticle->pos.x = e->pos.x + radius*sinf(angle);
        newParticle->pos.y = e->pos.y;
        newParticle->pos.z = e->pos.z + radius*cosf(angle);
*/
        
        newParticle->prevPos.x = 0;
        newParticle->prevPos.y = 0;
        newParticle->prevPos.z = 0;
        
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

bool circleEmitter::updateParticle(particle *p){
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

bool circleEmitter::simpleDetectCollision(vector3 pos, float epsilon){
    if(fabsf(pos.x - e->pos.x) - this->radius > epsilon) return false;
    if(fabsf(pos.y - e->pos.y) - this->radius > epsilon) return false;
    if(fabsf(pos.z - e->pos.z) - this->radius > epsilon) return false;
    return true;
}

bool circleEmitter::particleDetectCollision(vector3 pos, float epsilon){
    if(fabsf(pos.x - e->pos.x) - this->radius > epsilon) return false;
    if(fabsf(pos.y - e->pos.y) - this->radius > epsilon) return false;
    if(fabsf(pos.z - e->pos.z) - this->radius > epsilon) return false;
    particle *curr = e->particleList;
    while(curr){
        if(sqrt(pow(pos.x - curr->pos.x, 2) + pow(pos.y - curr->pos.y, 2) + pow(pos.z - curr->pos.z, 2)) < epsilon) return true;
        curr = curr->next;
    }
    return false;
}
