#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Torch.h"

Torch::Torch() : Model("models/Torch_OBJ/Torch_Low_Poly.obj") {

}

Torch::Torch(float scale) : Model("models/Torch_OBJ/Torch_Low_Poly.obj", scale) {

}

Torch::~Torch() {
	
}

void Torch::render() {
	Model::render();
}