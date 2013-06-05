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

class Loadscreen {
public:
	Loadscreen();
	~Loadscreen();
    void render(int level);
    
private:
    void renderLevel(int level);
	void initScreen();
};

#endif /* defined(__Rusko_adventures__loadscreen__) */
