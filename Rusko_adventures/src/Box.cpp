#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Box.h"


Box::Box() : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj") {
    movable = false;
    lastYPos = 0;
}


Box::Box(float scale) : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj", scale) {
    movable = false;
    lastYPos = 0;
}

Box::~Box() {
}

void Box::render() {
    float materialAmbient[]  = { 0.2, 0.2, 0.2, 1.0 };
    float materialDiffuse[]  = { 0.3, 0.2, 0.15, 1.0 };
    float materialSpecular[] = { 0.4, 0.4, 0.4, 1.0 };
    float shininess          = 8.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
	Model::render();
}

float Box::render(int frame) {
    if (!movable) {
        render();
        return 0;
    }
    else {
        glPushMatrix ();
        frame = frame % cr->totalPoints;
        STPoint3 fu = cr->pointAt(frame);
        glTranslatef(0, fu.y, 0);  //moves up/down new position
        float materialAmbient[]  = { 0.2, 0.2, 0.2, 1.0 };
        float materialDiffuse[]  = { 0.4, 0.2, 0.15, 1.0 };
        float materialSpecular[] = { 0.4, 0.4, 0.4, 1.0 };
        float shininess          = 8.0;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
        render();
        glPopMatrix ();
        
        //variables that need to be returned
        float deltay = fu.y - lastYPos;
        lastYPos = fu.y; //saves this position as lastYpos
        return deltay;
    }
}

void Box::setMove(float height){
    cr = new CatmullRom();
    cr->addControlPoint(0, 0, 0);
    cr->addControlPoint(0, height/2, 0);
    cr->addControlPoint(0, height, 0);
    cr->addControlPoint(0, 0, 0);
    cr->done();
    movable = true;
}