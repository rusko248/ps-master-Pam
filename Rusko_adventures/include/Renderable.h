#ifndef __RENDERABLE_H
#define __RENDERABLE_H 

#include "Framework.h"

// All classes that will be passed to the graphics module should be renderable
class Renderable
{
public:
	virtual void render() = 0;
};

struct Texture {
	STImage* diffuseMap;
	STImage* specularMap;
	STImage* normalMap;
};

struct Camera {
	STVector3 pos, up, pan;
};

#endif