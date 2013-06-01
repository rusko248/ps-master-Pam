#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Rusko.h"

using namespace std;

Rusko::Rusko() {
    model = new Model("models/rusko/Rusko_full_03.obj");
    
    //to load animation
    for (int i = 2; i <= lastFrame_run; i++){
        string mod_name = "models/rusko_run/Rusko_ani_04_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        runAnimation.push_back(mod);
        
        float scaleLength = mod->getMaxLength();
        STPoint3 centerMass = mod->getCenterMass();
        
        string torch_name = "models/torch_pos/Rusko_torchPos_0000";
        torch_name += (i/10 + '0');
        torch_name += ((i % 10) +'0');
        torch_name += ".obj";
        Model* torch_mod = new Model(torch_name, centerMass, scaleLength);
        torchPosition.push_back(torch_mod);
    }
}

Rusko::~Rusko() {
	delete model;
}

void Rusko::render(int frame) {
    frame = frame % runAnimation.size();
    runAnimation.at(frame)->render();
}

STPoint3 Rusko::getTorchPos(int frame){
    STPoint3 torchPos;
    
    frame = frame % torchPosition.size();
    torchPos = torchPosition.at(frame)->getCenterPoint();
    
    return torchPos;
}
