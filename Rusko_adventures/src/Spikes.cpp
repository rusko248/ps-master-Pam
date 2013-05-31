#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Spikes.h"

Spikes::Spikes() : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj") {
	
}

Spikes::Spikes(float scale) : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj", scale) {
	
}

Spikes::~Spikes() {
	
}

void Spikes::render() {
	Model::render();
}