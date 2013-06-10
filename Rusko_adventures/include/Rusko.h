#ifndef __RUSKO_H
#define __RUSKO_H

#include "Framework.h"
#include "Renderable.h"
#include "Obstacle.h"
#include "ruskoModel.h"

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
    std::vector<ruskoModel *> rusko_run;
    std::vector<ruskoModel *> rusko_stand2run;
    std::vector<ruskoModel *> rusko_run2stand;
    std::vector<ruskoModel *> rusko_stepLeft;
    std::vector<ruskoModel *> rusko_jump;


    std::vector<ruskoModel *> torch_run;
    std::vector<ruskoModel *> torch_stand2run;
    std::vector<ruskoModel *> torch_run2stand;
    std::vector<ruskoModel *> torch_stepLeft;
    std::vector<ruskoModel *> torch_jump;

    //last current frame
    int lastFrame;
};

#endif