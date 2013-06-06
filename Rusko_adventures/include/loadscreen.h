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

using namespace std;

class Loadscreen {
public:
	Loadscreen();
	~Loadscreen();
    void render(int level, int windowWidth, int windowHeight);
    
private:
    void renderLevel(int level);
	void initScreen();
    void drawIntroScreen();
    void drawMessageAt(string message, float xpos, float ypos, STColor4f color);
    STFont* font;
    
    int windowWidth;
    int windowHeight;
};

#endif /* defined(__Rusko_adventures__loadscreen__) */
