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
    float materialAmbient[]  = {0.2, 0.2, 0.2, 1.0 };
    float materialDiffuse[]  = { 0.319, 0.177, 0.005167, 1.0 };
    float materialSpecular[] = { 0.500000, 0.500000, 0.500000, 1.0 };
    float shininess          = 8.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
    
	Model::render();
}