#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Rusko.h"
#include <stdio.h>
#include <iostream.h>

using namespace std;

Rusko::Rusko() {
    model = new Model("models/rusko/Rusko_full_03.obj");
    //to load animation
    for (int i = 1; i <= lastFrame_run; i++){

        string mod_name = "models/rusko_run/Rusko_ani_02_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        
        cout << mod_name << endl;
        
        Model* mod = new Model(mod_name);
        renderList.push_back(mod);
    }
}

Rusko::~Rusko() {
	delete model;
}

void Rusko::render(int frame) {
    renderList.at(currentFrame)->render();
    currentFrame++;
    
    if (currentFrame == renderList.size()) currentFrame = 0;
}