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
	
	STPoint3 render(int frame);
    STPoint3 renderWalk(int frame);
    STPoint3 renderBackWalk(int frame);
    STPoint3 renderStepLeft(int frame);
    STPoint3 renderStepRight(int frame);
    STPoint3 renderJump(int frame);

private:
    // List of objects to render
    std::vector<Model *> rusko_run;
    std::vector<Model *> rusko_stand2run;
    std::vector<Model *> rusko_run2stand;
    std::vector<Model *> rusko_stepLeft;
    std::vector<Model *> rusko_jump;


    std::vector<Model *> torch_run;
    std::vector<Model *> torch_stand2run;
    std::vector<Model *> torch_run2stand;
    std::vector<Model *> torch_stepLeft;
    std::vector<Model *> torch_jump;

    //last current frame
    int lastFrame;
};

#endif