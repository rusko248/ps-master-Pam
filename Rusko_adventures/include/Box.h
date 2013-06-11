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
    float render(int frame); //renders at a certain frame for moving boxes, returns y_position

    bool movable;

private:
    CatmullRom* cr;

};

#endif