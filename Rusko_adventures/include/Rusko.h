#ifndef __RUSKO_H
#define __RUSKO_H

#include "Framework.h"
#include "Renderable.h"
#include "Obstacle.h"
#include "Model.h"

//Want the similar attributes to Obstacles for Rusko
//such as colliding with objects/etc

class Rusko : public Obstacle
{
public:
	Rusko();
	~Rusko();
	
	void render();
    
private:
	Model *model;
	Texture texture;
    
};

#endif