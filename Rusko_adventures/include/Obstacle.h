#ifndef __OBSTACLE_H
#define __OBSTACLE_H
#include "Framework.h"
#include "Renderable.h"

class Obstacle : public Renderable
{
public:
	Obstacle();
	/*virtual bool detectCollision(float playerZ, float playerRotation) = 0;
	virtual void setPosition(float,float) = 0;
	virtual void setPhase(float,float) = 0;
	virtual void collide() = 0;*/
	virtual void render() {};
	BBox bbox;

private:

};

#endif