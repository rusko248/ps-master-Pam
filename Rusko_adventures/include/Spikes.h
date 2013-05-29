#ifndef __SPIKES_H
#define __SPIKES_H

#include "Framework.h"
#include "Renderable.h"
#include "Obstacle.h"
#include "Model.h"

class Spikes : public Obstacle
{
public:
	Spikes();
	~Spikes();
	
	void render();

private:
	Model *model;
	Texture texture;

};

#endif