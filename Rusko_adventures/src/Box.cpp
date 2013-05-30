#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Box.h"

Box::Box() {
	model = new Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj");
	/*texture.diffuseMap = new STImage("models/WoodCrate_OBJ/D.jpg");
	texture.specularMap = new STImage("models/WoodCrate_OBJ/S.jpg");
	texture.normalMap = new STImage("models/WoodCrate_OBJ/NM.jpg");*/
	this->bbox = model->bbox;
}

Box::Box(float scale) {
	model = new Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj");
	model->scale(scale);
	this->bbox = model->bbox;
	this->bbox *= scale;
}

Box::~Box() {
	delete model;
}

void Box::render() {
	model->render();
}