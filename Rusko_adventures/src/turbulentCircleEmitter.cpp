//
//  turbulentCircleEmitter.cpp
//  Particles
//
//  Created by Aaron Damashek on 5/28/13.
//
//

#include "turbulentCircleEmitter.h"

turbulentCircleEmitter::turbulentCircleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force) : circleEmitter(r, pool, emitter_id, pos, dir, dirVar, speed, speedVar, totalParticles, emitsPerFrame, emitVar, life, lifeVar, force){
    
}

turbulentCircleEmitter::turbulentCircleEmitter(particle **pool, int emitter_id, string filepath) : circleEmitter (pool, emitter_id, filepath){
    
}

void turbulentCircleEmitter::display(){
    if(!displaying) return;
    pthread_mutex_lock(&mutex);
    if(!playFromFile){
        for(int newP = 0; newP < (e->emitsPerFrame + e->emitVar*randDist()); newP++){
            addParticle();
        }
    }
    glEnable(GL_POINT_SMOOTH);
    glEnable( GL_TEXTURE_2D );
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexEnvf( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glEnable(GL_POINT_SPRITE);
    glDepthMask(GL_FALSE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    // File locations
    std::string vertexShader = "../Particles/kernels/default.vert";
    std::string fragmentShader = "../Particles/kernels/fire.frag";
    std::string windPic = "../Particles/wind.png";
    
    STImage   *windImg;
    STTexture *windTex;
    
    STShaderProgram *shader;
    
    windImg = new STImage(windPic);
    windTex = new STTexture(windImg);
    
    shader = new STShaderProgram();
    shader->LoadVertexShader(vertexShader);
    shader->LoadFragmentShader(fragmentShader);
    
    // Texture 1: fire
    glActiveTexture(GL_TEXTURE0);
    windTex->Bind();
    
    // Bind the textures we've loaded into openGl to
    // the variable names we specify in the fragment
    // shader.
    shader->SetTexture("texture", 0);
    
    // Invoke the shader.  Now OpenGL will call our
    // shader programs on anything we draw.
    shader->Bind();
    shader->SetUniform("pointRadius", 25.0f);
    shader->SetUniform("point_size", 25.0f);
    
    glPointSize(5);
    glBegin(GL_POINTS);
    particle *curr = e->particleList;
    while(curr){
        if(playFromFile){
            glVertex3f(curr->pos.x + e->pos.x, curr->pos.y + e->pos.y, curr->pos.z + e->pos.z);
        }else{
            glVertex3f(curr->pos.x, curr->pos.y, curr->pos.z);
        }
        curr = curr->next;
    }
    glEnd();
    
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    glDisable(GL_POINT_SMOOTH);
    
    shader->UnBind();
    
    glActiveTexture(GL_TEXTURE0);
    windTex->UnBind();
    
    delete windImg;
    delete windTex;
    delete shader;
    pthread_mutex_unlock(&mutex);
}

bool turbulentCircleEmitter::addParticle(){
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
        STVector3 point = STVector3(radius*radScalar*cosf(angle), 0, radius*radScalar*sinf(angle));
        STVector3 straightUp = STVector3(0,1,0);
        STVector3 circleDir = STVector3(e->dir.x, e->dir.y, e->dir.z);
        
        
        STVector3 a  = STVector3::Cross(straightUp, circleDir);
        float w = sqrt(powf(straightUp.Length(), 2) * powf(circleDir.Length(), 2)) + STVector3::Dot(straightUp, circleDir);
        Quaternion rotateCircle = Quaternion(w, a.x, a.y, a.z);
        rotateCircle.Normalize();
        
        STVector3 rotatedPoint = rotateCircle.rotate(point, rotateCircle);
        newParticle->pos.x = rotatedPoint.x + e->pos.x;
        newParticle->pos.y = rotatedPoint.y + e->pos.y;
        newParticle->pos.z = rotatedPoint.z + e->pos.z;
        
        
        /*
         newParticle->pos.x = e->pos.x + radius*sinf(angle);
         newParticle->pos.y = e->pos.y;
         newParticle->pos.z = e->pos.z + radius*cosf(angle);
         */
        
        newParticle->prevPos.x = 0;
        newParticle->prevPos.y = 0;
        newParticle->prevPos.z = 0;
        
        newParticle->dir = e->dir;
        speed = 2*e->speed + e->speed * randDist()/2;
        //speed = e->speed;
        newParticle->dir.x *= speed;
        newParticle->dir.y *= speed;
        newParticle->dir.z *= speed;
        
        //newParticle->life = e->life + (int)((float)e->lifeVar * randDist());
        newParticle->life = e->life;
        newParticle->side = randDist();
        e->particleCount++;
        return true;
    }
    return false;
}

bool turbulentCircleEmitter::updateParticle(particle *p){
    if(p != NULL && p->life > 0){
        p->prevPos.x = p->pos.x;
        p->prevPos.y = p->pos.y;
        p->prevPos.z = p->pos.z;
        
        if(p->side < 0){
            p->pos.y = e->pos.y + cosf((p->pos.x)*e->life/e->lifeVar)*p->radius;
            if(abs(e->dir.x) == 1){
                p->pos.z = e->pos.z + p->radius * sinf((p->pos.x)*e->life/e->lifeVar)*p->radius;
            }else{
                p->pos.x = e->pos.x + p->radius * sinf((p->pos.z)*e->life/e->lifeVar)*p->radius;
            }
        }else{
            p->pos.y = e->pos.y + sinf((p->pos.x)*e->life/e->lifeVar)*p->radius;
            if(abs(e->dir.x) == 1){
                p->pos.z = e->pos.z + p->radius * cosf((p->pos.x)*e->life/e->lifeVar)*p->radius;
            }else{
                p->pos.x = e->pos.x + p->radius * cosf((p->pos.z)*e->life/e->lifeVar)*p->radius;
            }
        }
        
        p->pos.z += p->dir.z * abs(e->dir.z);
        p->pos.x += p->dir.x * abs(e->dir.x);
        
        p->dir.y += p->pos.z * p->pos.x * randDist();
        p->dir.z += p->pos.y * p->pos.x * randDist();
        
        p->pos.y += e->dirVar.y * randDist();
        p->pos.z += e->dirVar.z * randDist();
        p->pos.x += e->dirVar.x * (float)rand()/RAND_MAX;
        
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