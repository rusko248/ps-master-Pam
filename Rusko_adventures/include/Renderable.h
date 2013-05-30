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

struct BBox {
	BBox() {
		minx = miny = minz = 0.f;
		maxx = maxy = maxz = 0.f;
	}

	BBox& operator=(const BBox& b) {
		this->minx = b.minx; this->miny = b.miny; this->minz = b.minz;
		this->maxx = b.maxx; this->maxy = b.maxy; this->maxz = b.maxz;
		return *this;
	}

	BBox& operator*=(float s) {
		this->minx *= s; this->miny *= s; this->minz *= s;
		this->maxx *= s; this->maxy *= s; this->maxz *= s;
		return *this;
	}

	float minx, miny, minz;
	float maxx, maxy, maxz;
};

#endif