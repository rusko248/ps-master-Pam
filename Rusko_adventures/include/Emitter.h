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
#include "math.h"
#include "stglew.h"
#ifdef __APPLE__
#define GLEW_VERSION_2_0 1
#else
#define GLEW_STATIC 1
#include "GL/glew.h"
#endif

#include "ParticleStructs.h"
#include <vector.h>
#include <iostream>
#include <fstream>

using namespace std;

class Emitter
{
public:
	Emitter(particle **pool, int emitter_id, vector3 pos, vector3 dir, vector3 dirVar, float speed, float speedVar, int totalParticles, int emitsPerFrame, int emitVar, int life, int lifeVar, vector3 force);
    Emitter(particle **pool, int emitter_id, string filepath);
    ~Emitter();
    void update();
    virtual void display();
    void resetPos(vector3 newPos);
    void addDisplayPos(vector3 newPos);
    void setEmitting(bool emit);
    void setDisplaying(bool display);
    
    virtual void recordEmission(string outputFile);
    virtual void loadEmission(string filepath);
    void updateFromFile();
    emitter *e;
    
protected:
    particle **managerParticleList;
    void rotationToDirection(float pitch, float yaw, vector3 *direction);
    virtual bool addParticle();
    virtual bool updateParticle(particle *p);
    inline float randDist();
    bool emitting;
    bool displaying;
    ofstream *emitterInfo;
    bool recording;
    bool playFromFile;
    vector< vector <vector3> > storedLocations; // Particles / Frames for particle / vector for frame
    string intToString(int num);
    string floatToString(float num);
    float readFloat(ifstream *infile);
    int readInt(ifstream *infile);
    vector<vector3> positions;
    
};


#endif /* defined(__assignment2__Emitter__) */
