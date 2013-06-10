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

void Loadscreen::render(int level, int numTorches){
    this->numTorches = numTorches;
    
    // Clear the window.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (level == -1) drawIntroScreen();
    else renderLevel(level);
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void Loadscreen::renderLevel(int level){
    
    string message = "Level ";
    message += (level + '0');

    font = new STFont("fonts/NanumScript.ttc", 32);
    drawMessageAt(message, 0, 80, STColor4f(1, 1, 1, 1));
    message = "Find ";
    message += (numTorches+ '0');
    if (numTorches == 1) message += (" torch");
    else message += (" torches");
    
    font = new STFont("fonts/NanumScript.ttc", 28);
    drawMessageAt(message, 0, 50, STColor4f(0.7, .7, .7, 1));
}


void Loadscreen::drawIntroScreen(){

    string welcome = "Welcome to Rusko's Aventures!";
    string instructions = "Press enter to start";
    
    font = new STFont("fonts/NanumScript.ttc", 32);
    drawMessageAt(welcome, 0, 70, STColor4f(1, 1, 1, 1));
    
    font = new STFont("fonts/NanumScript.ttc", 28);
    drawMessageAt(instructions, 0, 30, STColor4f(.7, .7, .7, 1));
    
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 1);
    glVertex2d(0, 0);
    glColor3f(1, 0, 1);
    glVertex2d(0, 1);
    glColor3f(1, 0, 1);
    glVertex2d(1, 1);
    glEnd();
}

void Loadscreen::initScreen(){
    font = new STFont("fonts/NanumScript.ttc", 32);
    numTorches = 0;
}



void Loadscreen::drawMessageAt(string message, float xpos, float ypos, STColor4f color){
    
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2, -1., 1.);

    float temp = font->ComputeWidth(message);
    
    xpos = xpos - (float)temp/2;
    glTranslatef(xpos, ypos, 0);
    font->DrawString(message, color);  //Draws the string

    
    
    glPopMatrix ();
}

