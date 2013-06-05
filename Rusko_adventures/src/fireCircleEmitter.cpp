//
//  fireCircleEmitter.cpp
//  assignment2
//
//  Created by Aaron Damashek on 5/21/13.
//
//

#include "fireCircleEmitter.h"

fireCircleEmitter::fireCircleEmitter(float r, particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force) : circleEmitter(r, pool, emitter_id, pos, dir, dirVar, speed, speedVar, totalParticles, emitsPerFrame, emitVar, life, lifeVar, force){

}

fireCircleEmitter::fireCircleEmitter(particle **pool, int emitter_id, string filepath) : circleEmitter (pool, emitter_id, filepath){
    
}

void fireCircleEmitter::display(){
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glTexEnvf( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE );
    
    glBindTexture(GL_TEXTURE_2D, 0);
    //sf::Image::Bind(); //or glBindTexture(id);
    
    glEnable(GL_POINT_SPRITE);
    glDepthMask(GL_FALSE);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    // File locations
    std::string vertexShader = "../Particles/kernels/default.vert";
    std::string fragmentShader = "../Particles/kernels/fire.frag";
    //std::string fragmentShader = "/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/ParticleSystem3/ProgrammableShading/kernels/wind.frag";
    std::string firePic = "../Particles/Lava1.jpg";
    
    STImage   *fireImg;
    STTexture *fireTex;
    
    STShaderProgram *shader;
    
    fireImg = new STImage(firePic);
    fireTex = new STTexture(fireImg);
    
    shader = new STShaderProgram();
    shader->LoadVertexShader(vertexShader);
    shader->LoadFragmentShader(fragmentShader);
    
    // Texture 1: fire
    glActiveTexture(GL_TEXTURE0);
    fireTex->Bind();
    
    // Bind the textures we've loaded into openGl to
    // the variable names we specify in the fragment
    // shader.
    shader->SetTexture("texture", 0);
    
    // Invoke the shader.  Now OpenGL will call our
    // shader programs on anything we draw.
    shader->Bind();
    shader->SetUniform("pointRadius", 3.0f);
    shader->SetUniform("point_size", 3.0f);
    

    
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
    fireTex->UnBind();
    delete fireImg;
    delete fireTex;
    delete shader;
}