#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Rusko.h"

Rusko::Rusko() {
    model = new Model("models/rusko/Rusko_full_03.obj");
}

Rusko::~Rusko() {
	delete model;
}

void Rusko::render() {
	model->render();
}