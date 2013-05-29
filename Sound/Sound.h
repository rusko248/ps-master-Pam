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
// For this example, we need some function to sleep for some seconds,
// so we include the platform specific sleep functions here. This is
// only need for demo purposes and has nothing to do with sound output.
// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <windows.h>
#include <conio.h>
inline void sleepSomeTime() { Sleep(100); }
#else
#include "./Sound/common/conio.h"
#endif

// Lets start: include the irrKlang headers and other input/output stuff
// needed to print and get user input from the console. And as exlained
// in the first tutorial, we use the namespace irr and audio and
// link to the irrKlang.dll file.
#include <stdio.h>
#include "./include/irrKlang.h"
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


using namespace std;

class Sound
{
public:
	Sound();
    void update();
    void step();
    void lightTorch();
    ~Sound();

protected:
    ISoundEngine* engine;
    ISound* music;
    ISound* torch;
    float posOnCircle = 0;
    const float radius = 5;
};

#endif /* defined(__Rusko_adventures__Sound__) */
