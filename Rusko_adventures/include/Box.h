#ifndef __BOX_H
#define __BOX_H

#include "Framework.h"
#include "Renderable.h"
#include "Obstacle.h"
#include "Model.h"

class Box : public Obstacle
{
public:
	Box();
	~Box();
	
	void render();

private:
	Model *model;
	Texture texture;

};

#endif