#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Rusko.h"

using namespace std;

Rusko::Rusko() {
    model = new Model("models/rusko/Rusko_full_03.obj");
    //to load animation
    for (int i = 2; i <= lastFrame_run; i++){
        string mod_name = "models/rusko_run/Rusko_ani_03_0000";
        mod_name += (i/10 + '0');
        mod_name += ((i % 10) +'0');
        mod_name += ".obj";
        Model* mod = new Model(mod_name);
        renderList.push_back(mod);
    }
}

Rusko::~Rusko() {
	delete model;
}

void Rusko::render(int frame) {
    frame = frame % renderList.size();
    renderList.at(frame)->render();
}