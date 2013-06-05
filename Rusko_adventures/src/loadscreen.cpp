//
//  loadscreen.cpp
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/4/13.
//
//

#include "loadscreen.h"

Loadscreen::Loadscreen(){
    initScreen();
}

Loadscreen::~Loadscreen(){
    
}

void Loadscreen::render(int level){
    renderLevel(level);
}


void Loadscreen::renderLevel(int level){
    printf("level %i", level);
    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(.5, 0);
    glVertex2f(.5, 1);
    glVertex2f(0, 1);
    glEnd();
}


void Loadscreen::initScreen(){
    
}