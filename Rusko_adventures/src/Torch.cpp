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
    
    float materialAmbient[]  = { 0.0, 0.0, 0.0, 1.0 };
    float materialDiffuse[]  = { 0.400000, 0.400000, 0.400000, 1.0 };
    float materialSpecular[] = { 0.098461, 0.095218, 0.091337, 1.0 };
    float shininess          = 8.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
    
	Model::render();
}