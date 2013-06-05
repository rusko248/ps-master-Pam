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
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Clear the window.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw background
//    glEnable(GL_TEXTURE_2D);
//
//    glDisable(GL_DEPTH_TEST);
//    glDepthMask(GL_FALSE);
//    
//   
//    static STFont* gFont = new STFont("resources/arial.ttf", 24);
//    gFont->DrawString("hello", STColor4f(0, 0, 0, 1));  //Draws the string

    
    //printf("level %i", level);
    glBegin(GL_QUADS);
    glColor3f(1.0, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(0, .5);
    glVertex2f(.5, .5);
    glVertex2f(.5, 0);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
}


void Loadscreen::initScreen(){
    
}