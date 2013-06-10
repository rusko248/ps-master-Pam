#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Spikes.h"

Spikes::Spikes() : Model("models/Spikes/spikesLight.obj") {
	
}

Spikes::Spikes(float scale) : Model("models/Spikes/spikesLight.obj", scale) {
	
}

Spikes::~Spikes() {
	
}

void Spikes::render() {
	Model::render();
}