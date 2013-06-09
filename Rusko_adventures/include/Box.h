#ifndef __BOX_H
#define __BOX_H

#include "Framework.h"
#include "Renderable.h"
#include "Obstacle.h"
#include "Model.h"
#include "CatmullRom.h"


class Box : public Obstacle, public Model
{
public:
	Box();
    Box(float scale, float max); //moving box that moves a max height up
	Box(float scale);
	~Box();
	
	void render();
    void render(int frame); //renders at a certain frame for moving boxes

private:
    CatmullRom* cr;

};

#endif