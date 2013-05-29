//
//  Sound.cpp
//  Rusko_adventures
//
//  Created by Aaron Damashek on 5/27/13.
//
//

#include "Sound.h"

Sound::Sound(){
    engine = createIrrKlangDevice();
    
    if (!engine)
		return 0; // error starting up the engine
    
	// Now play some sound stream as music in 3d space, looped.
	// We are setting the last parameter named 'track' to 'true' to
	// make irrKlang return a pointer to the played sound. (This is also returned
	// if the parameter 'startPaused' is set to true, by the way). Note that you
	// MUST call ->drop to the returned pointer if you don't need it any longer and
	// don't want to waste any memory. This is done in the end of the program.
    
	music = engine->play3D("/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/3DSound copy/media/Cave4.mp3", vec3df(0,0,0), true, false, true);
    
    torch = engine->play3D("/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/3DSound copy/media/constantFire.mp3",vec3df(0,0,0), true, false, true);
    
	// the following step isn't necessary, but to adjust the distance where
	// the 3D sound can be heard, we set some nicer minimum distance
	// (the default min distance is 1, for a small object). The minimum
	// distance simply is the distance in which the sound gets played
	// at maximum volume.
    
	if (music){
        music->setVolume(3.0f);
		music->setMinDistance(5.0f);
    }
    if (torch){
        torch->setVolume(1.0f);
		torch->setMinDistance(5.0f);
    }

}

Sound::~Sound(){
    if (music)
		music->drop(); // release music stream.
    if (torch)
		torch->drop(); // release music stream.
    
	engine->drop(); // delete engine
}



void Sound::update(){
    posOnCircle += 0.04f;
    vec3df pos3d(radius * cosf(posOnCircle), 0,
                 radius * sinf(posOnCircle * 0.5f));
    
    // After we know the positions, we need to let irrKlang know about the
    // listener position (always position (0,0,0), facing forward in this example)
    // and let irrKlang know about our calculated 3D music position
    
    engine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
    
    if (music)
        music->setPosition(pos3d);
	
    sleepSomeTime();
}

void Sound::step(){
    vec3df pos(fmodf((float)rand(),radius*2)-radius, 0, 0);
    engine->play3D("/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/3DSound copy/media/bell.wav", pos);
    break;
}

void Sound::lightTorch(){
    vec3df pos(fmodf((float)rand(),radius*2)-radius, 0, 0);
    engine->play3D("/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/3DSound copy/media/bell.wav", pos);
    break;
}