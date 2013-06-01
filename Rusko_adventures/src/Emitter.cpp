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
    emitting = true;
    displaying = true;
    recording = false;
    playFromFile = false;
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

string Emitter::intToString(int num){
    char temp[20];
    sprintf(temp, "%d", num);
    string numStr = string(temp);
    return numStr;
}

string Emitter::floatToString(float num){
    char temp[20];
    sprintf(temp, "%f", num);
    string numStr = string(temp);
    return numStr;
}

float Emitter::readFloat(ifstream *infile){
    char line[20];
    *infile >> line;
    float value = atof(line);
    return value;
}

int Emitter::readInt(ifstream *infile){
    char line[20];
    *infile >> line;
    int value = atoi(line);
    return value;
}

bool Emitter::addParticle(){
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
        if(recording){
            *emitterInfo << floatToString(p->pos.x) << endl;
            *emitterInfo << floatToString(p->pos.y) << endl;
            *emitterInfo << floatToString(p->pos.z) << endl;
        }
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
    if(!displaying) return;
    if(!playFromFile){
        for(int newP = 0; newP < (e->emitsPerFrame + e->emitVar*randDist()); newP++){
            addParticle();
        }
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
    if(recording) emitterInfo->close();
}

void Emitter::update(){
    if(!displaying) return;
    if(playFromFile){
        updateFromFile();
        return;
    }
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

void Emitter::setEmitting(bool emit){
    emitting = emit;
}

void Emitter::setDisplaying(bool display){
    displaying = display;
}

void Emitter::recordEmission(string outputFile){
    emitterInfo = new ofstream (outputFile.c_str());
    if (emitterInfo->is_open())
    {
        *emitterInfo << floatToString(e->pos.x) << endl;
        *emitterInfo << floatToString(e->pos.y) << endl;
        *emitterInfo << floatToString(e->pos.z) << endl;
        
        *emitterInfo << floatToString(e->dir.x) << endl;
        *emitterInfo << floatToString(e->dir.y) << endl;
        *emitterInfo << floatToString(e->dir.z) << endl;

        *emitterInfo << floatToString(e->dirVar.x) << endl;
        *emitterInfo << floatToString(e->dirVar.y) << endl;
        *emitterInfo << floatToString(e->dirVar.z) << endl;

        *emitterInfo << floatToString(e->speed) << endl;
        *emitterInfo << floatToString(e->speedVar) << endl;
        
        *emitterInfo << intToString(e->totalParticles) << endl;

        *emitterInfo << intToString(e->emitsPerFrame) << endl;
        *emitterInfo << intToString(e->emitVar) << endl;
        *emitterInfo << intToString(e->life) << endl;
        *emitterInfo << intToString(e->lifeVar) << endl;
        
        *emitterInfo << floatToString(e->force.x) << endl;
        *emitterInfo << floatToString(e->force.y) << endl;
        *emitterInfo << floatToString(e->force.z) << endl;
 
        recording = true;
    }
    else cout << "Unable to open file";
}

Emitter::Emitter(particle **pool, int emitter_id, string filepath){
    e = new emitter;
    e->emitter_id = emitter_id;
    
    managerParticleList = pool;
    emitting = true;
    displaying = true;
    
    if(filepath != "circle") loadEmission(filepath);
    playFromFile = true;
}

void Emitter::loadEmission(string filepath){
    cout << "loading Emitter" << endl;
    ifstream *infile = new ifstream(filepath.c_str(),ios::in);
    //ifstream infile;
    //infile.open(filepath.c_str());
    
    if(infile){
        //Get attributes
        e->pos.x  = readFloat(infile);
        
        e->pos.y = readFloat(infile);
        e->pos.z = readFloat(infile);
        
        e->dir.x = readFloat(infile);
        
        e->dir.y = readFloat(infile);
        
        e->dir.z = readFloat(infile);
        
        e->dirVar.x = readFloat(infile);
        
        e->dirVar.y = readFloat(infile);
        
        e->dirVar.z = readFloat(infile);
        
        e->speed = readFloat(infile);
        
        e->speedVar = readFloat(infile);
        
        e->totalParticles = readInt(infile);
        
        e->emitsPerFrame = readInt(infile);
        e->emitVar = readInt(infile);
        e->life = readInt(infile);
        e->lifeVar = readInt(infile);
        
        
        e->force.x = readFloat(infile);
        e->force.y = readFloat(infile);
        e->force.z = readFloat(infile);
        

        e->particleList = NULL;
        for(int i = 0; i < e->totalParticles; i++){
            addParticle();
            vector<vector3> vertexPositions;
            storedLocations.push_back(vertexPositions);
        }
        
        //Get vertices
        int particle = 0;
        while(!infile->eof())
        {
            int currParticle = particle % e->totalParticles;
            vector3 pos;
            pos.x = readFloat(infile);
            pos.y = readFloat(infile);
            pos.z = readFloat(infile);
            storedLocations[currParticle].push_back(pos);
            particle++;
        }
        infile->close();
        
    }else{
        cout << "Invalid File" << endl;
    }
}

void Emitter::updateFromFile(){
    static int updateNumber = 0;
    if(storedLocations.size() < 1) return;
    int numFramesStored = storedLocations[0].size();
    int displayFrame = updateNumber % (numFramesStored - 1);
    
    int particleIndex = 0;
    particle *curr = e->particleList;
    while(curr){
        particle *toUpdate = curr;
        curr = curr->next;
        
        vector3 pos = storedLocations[particleIndex][displayFrame];
        toUpdate->pos = pos;
        particleIndex++;
    }
    updateNumber++;
}