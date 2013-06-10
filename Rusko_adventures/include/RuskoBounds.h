//
//  RuskoBounds.h
//  Rusko_adventures
//
//  Created by Pamela Martinez on 6/5/13.
//
//

#ifndef __Rusko_adventures__RuskoBounds__
#define __Rusko_adventures__RuskoBounds__

#include <iostream>
#include "Framework.h"
#include "Room.h"

using namespace std;

class RuskoBounds
{
public:
    RuskoBounds();
    ~RuskoBounds();
    void setRoom(Room* room);
    bool inBounds(STVector3 futurePos);
    
protected:
    Room* room;
    Floor* floorBounds;
};


#endif /* defined(__Rusko_adventures__RuskoBounds__) */
