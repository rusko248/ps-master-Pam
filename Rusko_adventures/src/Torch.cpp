#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Torch.h"

Torch::Torch() {
	model = new Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj");
	/*texture.diffuseMap = new STImage("models/WoodCrate_OBJ/D.jpg");
	texture.specularMap = new STImage("models/WoodCrate_OBJ/S.jpg");
	texture.normalMap = new STImage("models/WoodCrate_OBJ/NM.jpg");*/
}

Torch::~Torch() {
	delete model;
}

void Torch::render() {
	model->render();
}