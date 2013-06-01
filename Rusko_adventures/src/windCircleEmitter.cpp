//
//  windCircleEmitter.cpp
//  Particles
//
//  Created by Aaron Damashek on 5/23/13.
//
//

#include "windCircleEmitter.h"

windCircleEmitter::windCircleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force) : circleEmitter(r, pool, emitter_id, pos, dir, dirVar, speed, speedVar, totalParticles, emitsPerFrame, emitVar, life, lifeVar, force){
    
}

windCircleEmitter::windCircleEmitter(particle **pool, int emitter_id, string filepath) : circleEmitter (pool, emitter_id, filepath){
    
}

void windCircleEmitter::display(){
    if(!displaying) return;
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
    //sf::Image::Bind(); //or glBindTexture(id);
    
    glEnable(GL_POINT_SPRITE);
    glDepthMask(GL_FALSE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    // File locations
    std::string vertexShader = "/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/ParticleSystem3/Particles/kernels/default.vert";
    std::string fragmentShader = "/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/ParticleSystem3/Particles/kernels/wind.frag";
    //std::string fragmentShader = "/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/ParticleSystem3/ProgrammableShading/kernels/wind.frag";
    std::string windPic = "/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/ParticleSystem3/Particles/wind.png";
    
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
    shader->SetTexture("windTex", 0);
    
    // Invoke the shader.  Now OpenGL will call our
    // shader programs on anything we draw.
    shader->Bind();
    shader->SetUniform("pointRadius", 7.0f);
    shader->SetUniform("point_size", 7.0f);
    
    glPointSize(5);
    glBegin(GL_POINTS);
    particle *curr = e->particleList;
    while(curr){
        glVertex3f(curr->pos.x, curr->pos.y, curr->pos.z);
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
}

bool windCircleEmitter::updateParticle(particle *p){
    if(p != NULL && p->life > 0){
        p->prevPos.x = p->pos.x;
        p->prevPos.y = p->pos.y;
        p->prevPos.z = p->pos.z;
        
        p->dir = p->dir*(fmax((p->life),e->life/1.1)/(float)e->life);
        
        p->pos.x += p->dir.x;
        p->pos.y += p->dir.y;
        p->pos.z += p->dir.z;
        
        //p->dir.x += e->force.x*cosf(p->pos.y)*p->side;
        //p->dir.y += e->force.y*cosf(p->pos.y)*p->side;
        //p->dir.z += e->force.z*cosf(p->pos.y)*p->side;
        
        //p->dir.y += p->pos.z * p->pos.x / 20 * randDist();
        //p->dir.z += p->pos.y * p->pos.x / 20 * randDist();
        
        p->dir.y += p->pos.z * p->pos.x / 20 * randDist();
        p->dir.z += p->pos.y * p->pos.x / 20 * randDist();
        
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