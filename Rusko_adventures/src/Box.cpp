#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Box.h"

Box::Box() : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj") {
	
}

Box::Box(float scale) : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj", scale) {

}

Box::~Box() {
	
}

void Box::render() {
	Model::render();
}