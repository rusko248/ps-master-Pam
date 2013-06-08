#ifndef __GRAPHICS_H
#define __GRAPHICS_H

// Graphics module
/*
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
*/

#include <cmath>
#include <vector>
#include "Framework.h"
#include "Renderable.h"
#include "Room.h"
#include "CatmullRom.h"
#include "Rusko.h"
#include "ParticleManager.h"
#include "Sound.h"
#include "loadscreen.h"
#include "RuskoPhysics.h"
#include "RuskoBounds.h"
#include "RuskoCollisions.h"


//Particles that must rotate as part of the world

extern ParticleManager *particles;

//Torch Fire
extern ParticleManager *torchParticles;

extern float xpos;
extern float zpos;
extern float ypos;

void GraphicsInit(int argc, char** argv);
void GraphicsMainLoop();

#endif