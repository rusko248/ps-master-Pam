//
//  CharacterPhysics.h
//  libst
//
//  Created by Aaron Damashek on 6/4/13.
//
//

#ifndef __libst__characterPhysics__
#define __libst__characterPhysics__

#include <iostream>

using namespace std;

class CharacterPhysics
{
public:
    CharacterPhysics(float yPos);
    ~CharacterPhysics();
    void jump();
    void update(float timeStep);
    void setOnGround(bool groundContact);
    void reset(float yPos);
    float yPos;

protected:
    float yVel;
    float yAccel;
    bool onGround;
    
};

#endif /* defined(__libst__characterPhysics__) */
