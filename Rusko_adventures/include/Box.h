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
	Box(float scale);
	~Box();
	
    void setMove(float height);//makes a box to move up a certain height
	void render();
    void render(int frame); //renders at a certain frame for moving boxes

private:
    CatmullRom* cr;
    bool wasSetMove;

};

#endif