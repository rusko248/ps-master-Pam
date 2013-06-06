//
//  RuskoCollisions.h
//  Rusko_adventures
//
//  Created by Aaron Damashek on 6/5/13.
//
//

#ifndef __Rusko_adventures__RuskoCollisions__
#define __Rusko_adventures__RuskoCollisions__

#include <iostream>

#include "Framework.h"
#include "Room.h"

using namespace std;

class RuskoCollisions
{
public:
    RuskoCollisions(Room* room);
    ~RuskoCollisions();
    void checkForCollisions();
    void reset();
    
protected:
    bool collisionOccuring;
    bool colliding(ObsBound *one, ObsBound *two);
    void reactToCollision(ObsBound* offendingObject);
    Room* room;
    ObsBound *ruskoBound;
    vector<ObsBound> obsList;
    
};

#endif /* defined(__Rusko_adventures__RuskoCollisions__) */
