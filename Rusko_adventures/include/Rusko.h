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
	
	void render(int frame);
    STPoint3 getTorchPos(int frame);
    
private:
	Model *model;
	Texture texture;
    
    //number of frames for animation
    int lastFrame_run = 40;
    int currentFrame = 0;
    
    // List of objects to render
    std::vector<Model *> runAnimation;
    std::vector<Model *> torchPosition;

    
};

#endif