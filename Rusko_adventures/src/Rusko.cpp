#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Rusko.h"

using namespace std;

Rusko::Rusko() {
    lastFrame = 0;
    
    //loads running animation
    for (int i = 5; i <= 23; i++){
        string mod_name = "models/rusko/rusko_run/Rusko_ani_04_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        rusko_run.push_back(mod);
        
        float scaleLength = mod->getMaxLength();
        STPoint3 centerMass = mod->getCenterMass();
        
        string torch_name = "models/rusko/torch_run/Rusko_ani_06_0000";
        torch_name += (i/10 + '0');
        torch_name += ((i % 10) +'0');
        torch_name += ".obj";
        Model* torch_mod = new Model(torch_name, centerMass, scaleLength);
        torch_run.push_back(torch_mod);
    }
    
    //loads stand to run animation
    for (int i = 1; i <= 31; i = i+6){
        string mod_name = "models/rusko/rusko_stand2run/walk2run_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        rusko_stand2run.push_back(mod);
        
        float scaleLength = mod->getMaxLength();
        STPoint3 centerMass = mod->getCenterMass();
        
        string torch_name = "models/rusko/torch_stand2run/Rusko_ani_09_walkToRun_0000";
        torch_name += (i/10 + '0');
        torch_name += ((i % 10) +'0');
        torch_name += ".obj";
        Model* torch_mod = new Model(torch_name, centerMass, scaleLength);
        torch_stand2run.push_back(torch_mod);
    }
    
    
    //loads run to stand animation
    for (int i = 1; i <= 61; i = i+2){
        string mod_name = "models/rusko/rusko_run2stand/runToStand_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        rusko_run2stand.push_back(mod);
        
        float scaleLength = mod->getMaxLength();
        STPoint3 centerMass = mod->getCenterMass();
        
        string torch_name = "models/rusko/torch_run2stand/torch runToStand_0000";
        torch_name += (i/10 + '0');
        torch_name += ((i % 10) +'0');
        torch_name += ".obj";
        Model* torch_mod = new Model(torch_name, centerMass, scaleLength);
        torch_run2stand.push_back(torch_mod);
    }

    //loads stepLeft animation
    for (int i = 1; i <= 44; i = i+2){
        string mod_name = "models/rusko/rusko_stepLeft/stepLeft_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        rusko_stepLeft.push_back(mod);
        
        float scaleLength = mod->getMaxLength();
        STPoint3 centerMass = mod->getCenterMass();
        
        string torch_name = "models/rusko/torch_stepLeft/stepLeft_0000";
        torch_name += (i/10 + '0');
        torch_name += ((i % 10) +'0');
        torch_name += ".obj";
        Model* torch_mod = new Model(torch_name, centerMass, scaleLength);
        torch_stepLeft.push_back(torch_mod);
    }

    //loads jump animation
    for (int i = 1; i <= 47; i = i+2){
        string mod_name = "models/rusko/rusko_jump/jump_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        rusko_jump.push_back(mod);
        
        float scaleLength = mod->getMaxLength();
        STPoint3 centerMass = mod->getCenterMass();
        
        string torch_name = "models/rusko/torch_jump/jump_0000";
        torch_name += (i/10 + '0');
        torch_name += ((i % 10) +'0');
        torch_name += ".obj";
        Model* torch_mod = new Model(torch_name, centerMass, scaleLength);
        torch_jump.push_back(torch_mod);
    }
}

Rusko::~Rusko() {
}


STPoint3 Rusko::render(int frame) {
    STPoint3 torchPos;
    rusko_stand2run.at(0)->render();
    torchPos = torch_stand2run.at(0)->getCenterPoint();
    return torchPos;
}

STPoint3 Rusko::renderWalk(int frame){
    STPoint3 torchPos;
    if (frame < rusko_stand2run.size()){
        rusko_stand2run.at(frame)->render();
        torchPos = torch_stand2run.at(frame)->getCenterPoint();

    }
    else {
        frame -= rusko_stand2run.size();
        frame = frame % rusko_run.size();
        rusko_run.at(frame)->render();
        torchPos = torch_run.at(frame)->getCenterPoint();

    }
    lastFrame = frame;
    return torchPos;
}


STPoint3 Rusko::renderBackWalk(int frame){
    STPoint3 torchPos;
    if (frame < rusko_run2stand.size()){
        int endFrame = rusko_run2stand.size()-1;
        
        rusko_run2stand.at(endFrame - frame)->render();
        torchPos = torch_run2stand.at(endFrame- frame)->getCenterPoint();
    }
    else {
        frame -= rusko_run2stand.size();
        frame = frame % rusko_run.size();
        
        int endFrame = rusko_run.size()-1;
        rusko_run.at(endFrame - frame)->render();
        torchPos = torch_run.at(endFrame - frame)->getCenterPoint();
    }
    lastFrame = frame;
    return torchPos;
}

STPoint3 Rusko::renderStepLeft(int frame){
    STPoint3 torchPos;

    frame = frame % rusko_stepLeft.size();
    rusko_stepLeft.at(frame)->render();
    torchPos = torch_stepLeft.at(frame)->getCenterPoint();

    lastFrame = frame;
    return torchPos;
}

STPoint3 Rusko::renderStepRight(int frame){
    STPoint3 torchPos;
    
    frame = frame % rusko_stepLeft.size();
    int endFrame = rusko_stepLeft.size()-1;

    rusko_stepLeft.at(endFrame - frame)->render();
    torchPos = torch_stepLeft.at(endFrame - frame)->getCenterPoint();
    
    lastFrame = frame;
    return torchPos;
}

STPoint3 Rusko::renderJump(int frame){
    STPoint3 torchPos;
    
    frame = frame % rusko_jump.size();
    rusko_jump.at(frame)->render();
    torchPos = torch_jump.at(frame)->getCenterPoint();
    lastFrame = frame;
    return torchPos;
}
