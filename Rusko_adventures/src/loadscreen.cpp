//
//  loadscreen.cpp
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/4/13.
//
//

#include "loadscreen.h"
#define FONT_SMALL 0
#define FONT_MEDIUM 1
#define FONT_LARGE 2

Loadscreen::Loadscreen(){
    initScreen();
}

Loadscreen::~Loadscreen(){
    
}

void Loadscreen::renderWelcomeScreen(){
    this->numTorches = numTorches;
    
    // Clear the window.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawIntroScreen();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Loadscreen::render(int level, int numTorches){
    this->numTorches = numTorches;
    
    // Clear the window.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    renderLevel(level);
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void Loadscreen::renderLevel(int level){
    
    string message = "Level ";
    message += (level + '0');

    drawMessageAt(message, 0, 80, STColor4f(1, 1, 1, 1), FONT_LARGE);
    message = "Find ";
    message += (numTorches+ '0');
    if (numTorches == 1) message += (" total torch");
    else message += (" total torches");
    
    drawMessageAt(message, 0, 30, STColor4f(0.7, .7, .7, 1), FONT_SMALL);
    
    message = livesLeft + '0';
    if (livesLeft == 1) {
        message += " life left";
        drawMessageAt(message, 0, (float)-windowHeight/3, STColor4f(1., .4, .4, 1), FONT_SMALL);
    }
    else {
        message += " lives left";
        drawMessageAt(message, 0, (float)-windowHeight/3, STColor4f(1., 1., .6, 1), FONT_SMALL);
    }
}


void Loadscreen::drawIntroScreen(){

    string welcome = "Welcome to Rusko's Aventures!";
    string instructions = "Press enter to start";
    
    drawMessageAt(welcome, 0, 70, STColor4f(1, 1, 1, 1), FONT_MEDIUM);
    drawMessageAt(instructions, 0, 30, STColor4f(.7, .7, .7, 1), FONT_SMALL);
    
    instructions = "Use SPACEBAR to jump";
    drawMessageAt(instructions, 0, (float)-windowHeight/3, STColor4f(1., 1., .6, 1), FONT_SMALL);

    instructions = "UP/DOWN/RIGHT/LEFT keys to move";
    drawMessageAt(instructions, 0, (float)-windowHeight/3 - 30, STColor4f(1., 1., .6, 1), FONT_SMALL);
    
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 1);
    glVertex2d(0, 0);
    glColor3f(1, 0, 1);
    glVertex2d(0, 1);
    glColor3f(1, 0, 1);
    glVertex2d(1, 1);
    glEnd();
}

void Loadscreen::renderGameOver(){
    
    string welcome = "GAME OVER";
    string instructions = "Press enter to play again";
    
    drawMessageAt(welcome, 0, 70, STColor4f(1., .4, .4, 1), FONT_LARGE);
    
    drawMessageAt(instructions, 0, 30, STColor4f(.7, .7, .7, 1), FONT_SMALL);
    
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
    
    #ifdef __APPLE__
    fontName = "fonts/NanumScript.ttc"; 
    #else
    fontName = "fonts/Gabriola.ttf.ttc";
    #endif

    fontLarge = new STFont(fontName, 64);
    fontMed = new STFont(fontName, 40);
    fontSmall = new STFont(fontName, 32);
    
    numTorches = 0;
}



void Loadscreen::drawMessageAt(string message, float xpos, float ypos, STColor4f color, int fontsize){
    
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2, -1., 1.);

    
    STFont* font;
    if (fontsize == FONT_SMALL) font = fontSmall;
    else if (fontsize == FONT_MEDIUM) font = fontMed;
    else if (fontsize == FONT_LARGE) font = fontLarge;

    float temp = font->ComputeWidth(message);
    
    xpos = xpos - (float)temp/2;
    glTranslatef(xpos, ypos, 0);
    font->DrawString(message, color);  //Draws the string

    glPopMatrix ();
}

