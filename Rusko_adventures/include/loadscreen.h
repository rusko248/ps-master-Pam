//
//  loadscreen.h
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/4/13.
//
//

#ifndef __Rusko_adventures__loadscreen__
#define __Rusko_adventures__loadscreen__

#include <iostream>

#include "Framework.h"
#include "Renderable.h"
extern int windowWidth, windowHeight;
extern int livesLeft;

using namespace std;

class Loadscreen {
public:
	Loadscreen();
	~Loadscreen();
    void render(int level, int numTorches);
    void renderWelcomeScreen();
    void renderGameOver();
    
private:
    void drawIntroScreen();
    void renderLevel(int level);
	void initScreen();
    void drawMessageAt(string message, float xpos, float ypos, STColor4f color, int fontsize);
    STFont* fontLarge;
    STFont* fontSmall;
    STFont* fontMed;
    int numTorches;
    string fontName;
};

#endif /* defined(__Rusko_adventures__loadscreen__) */
