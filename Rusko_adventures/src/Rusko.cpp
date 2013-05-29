#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Rusko.h"

Rusko::Rusko() {
	//model = new Model("models/obj/sphere.obj");
    model = new Model("models/rusko/Rusko_v5_try2.obj");
}

Rusko::~Rusko() {
	delete model;
}

void Rusko::render() {
	model->render();
}