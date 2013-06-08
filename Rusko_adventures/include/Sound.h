//
//  Sound.h
//  Rusko_adventures
//
//  Created by Aaron Damashek on 5/27/13.
//
//

#ifndef __Rusko_adventures__Sound__
#define __Rusko_adventures__Sound__


#include <iostream>
#include "fmod.hpp"
//#include "common.h"

using namespace std;

class Sound
{
public:
	Sound();
    void update();
    void startWalking();
    void stopWalking();

    void ruskoTorch(bool off);
    
    void lightTorch();
    void jump();
    void die();
    
    void startLevel();
    void endLevel();
    
    ~Sound();
    bool walking;
    bool jumping;

protected:
    const int   INTERFACE_UPDATETIME = 50;      // 50ms update for interface
    const float DISTANCEFACTOR = 1.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.
    FMOD::System    *system;
    FMOD::Sound     *sound1, *sound2, *sound3, *sound4, *sound5, *sound6, *sound7;
    FMOD::Channel   *channel1 = 0, *channel2 = 0, *channel3 = 0, *channel4 = 0, *channel5 = 0, *channel6 = 0, *channel7 = 0;
    FMOD_RESULT      result;
    bool             listenerflag = true;
    FMOD_VECTOR      listenerpos  = { 0.0f, 0.0f, 0.0f};
    unsigned int     version;
    void            *extradriverdata = 0;
};

#endif /* defined(__Rusko_adventures__Sound__) */
