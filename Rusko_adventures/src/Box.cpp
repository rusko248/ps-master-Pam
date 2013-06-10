#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Box.h"


Box::Box() : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj") {
    movable = false;
}


//Box::Box(float scale) : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj", scale) {
//    wasSetMove = false;
//}

Box::Box(float scale) : Model("models/WoodCrate_OBJ/WoodCrate_OBJ.obj", scale) {
    movable = false;
}

Box::~Box() {
}

void Box::render() {
	Model::render();
}

void Box::render(int frame) {
    if (!movable) render();
    else {
        glPushMatrix ();
        frame = frame % cr->totalPoints;
        STPoint3 fu = cr->pointAt(frame);
        glTranslatef(0, fu.y, 0);  //moves up/down new position
        render();
        glPopMatrix ();
    }
}

void Box::setMove(float height){
    cr = new CatmullRom();
    cr->addControlPoint(0, 0, 0);
    cr->addControlPoint(0, height, 0);
    cr->addControlPoint(0, 0, 0);
    cr->done();
    movable = true;
}