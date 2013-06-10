//
//  Sound.cpp
//  Rusko_adventures
//
//  Created by Aaron Damashek on 5/27/13.
//
//

#include "Sound.h"

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        cout << "FMOD Error" << endl;
    }
}

Sound::Sound(){
    
    /*
     Create a System object and initialize.
     */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);
    
    result = system->getVersion(&version);
    ERRCHECK(result);
    
    if (version < FMOD_VERSION)
    {
        cout << "FMOD version error" << endl;
    }
    
    result = system->init(100, FMOD_INIT_NORMAL | FMOD_INIT_PROFILE_ENABLE, extradriverdata);
    ERRCHECK(result);
    
    /*
     Set the distance units. (meters/feet etc).
     */
    result = system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
    ERRCHECK(result);
    
    /*
     Load some sounds
     */

    result = system->createSound("sounds/Cave4.mp3", FMOD_3D, 0, &sound1);
    ERRCHECK(result);
    result = sound1->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);
    ERRCHECK(result);
    result = sound1->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(result);
    
    result = system->createSound("sounds/constantFire.mp3", FMOD_3D, 0, &sound2);
    ERRCHECK(result);
    result = sound2->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);
    ERRCHECK(result);
    result = sound2->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(result);
    
    result = system->createSound("sounds/Step2.mp3", FMOD_SOFTWARE | FMOD_3D, 0, &sound3);
    ERRCHECK(result);
    result = sound3->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(result);
    
    result = system->createSound("sounds/lightFire.mp3", FMOD_SOFTWARE | FMOD_3D, 0, &sound4);
    ERRCHECK(result);
    result = sound4->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);
    
    result = system->createSound("sounds/jump.mp3", FMOD_SOFTWARE | FMOD_3D, 0, &sound5);
    ERRCHECK(result);
    result = sound5->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);
    
    result = system->createSound("sounds/die.mp3", FMOD_SOFTWARE | FMOD_3D, 0, &sound6);
    ERRCHECK(result);
    result = sound6->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);
    
    result = system->createSound("sounds/loading.mp3", FMOD_SOFTWARE | FMOD_3D, 0, &sound7);
    ERRCHECK(result);
    result = sound7->setMode(FMOD_LOOP_NORMAL);
    ERRCHECK(result);
    

//     Start playing constant sounds

    FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
    FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
    
    //Channel 1 - music
    
    result = system->playSound(sound1, 0, false, &channel1);
    ERRCHECK(result);
    result = channel1->set3DAttributes(&pos, &vel);
    ERRCHECK(result);
    result = channel1->setPaused(true);
    ERRCHECK(result);
    
    //Channel 2 - rusko torch
    
    result = system->playSound(sound2, 0, false, &channel2);
    ERRCHECK(result);
    result = channel2->set3DAttributes(&pos, &vel);
    ERRCHECK(result);
    result = channel2->setPaused(true);
    ERRCHECK(result);
    
    //Channel 3 - walking
    
    result = system->playSound(sound3, 0, true, &channel3);
    ERRCHECK(result);
    result = channel2->set3DAttributes(&pos, &vel);
    ERRCHECK(result);
    result = channel2->setPaused(true);
    ERRCHECK(result);
    
    walking = false;
    
    //Channel 4 - light fire
    
    
    //Channel 5 - jump
    
    jumping = false;
    
    //Channel 6 - die
    
    //Channel 7 - loading music
    
    result = system->playSound(sound7, 0, false, &channel7);
    ERRCHECK(result);
    result = channel7->set3DAttributes(&pos, &vel);
    ERRCHECK(result);
    result = channel7->setPaused(false);
    ERRCHECK(result);
    


}

Sound::~Sound(){
    result = sound1->release();
    ERRCHECK(result);
    result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);
    result = sound4->release();
    ERRCHECK(result);
    result = sound5->release();
    ERRCHECK(result);
    result = sound6->release();
    ERRCHECK(result);
    
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
    
}



void Sound::update(){

    result = system->update();
    ERRCHECK(result);
}

void Sound::startWalking(){
    result = channel3->setPaused(false);
    ERRCHECK(result);
    walking = true;
}

void Sound::stopWalking(){
    result = channel3->setPaused(true);
    ERRCHECK(result);
    walking = false;
}

void Sound::lightTorch(){
    result = system->playSound(sound4, 0, false, &channel4);
    ERRCHECK(result);
}

void Sound::jump(){
    result = system->playSound(sound5, 0, false, &channel5);
    ERRCHECK(result);
    jumping = true;
}

void Sound::die(){
    result = system->playSound(sound6, 0, false, &channel6);
    ERRCHECK(result);
}

void Sound::ruskoTorch(bool off){
    /*
    bool paused;
    channel2->getPaused(&paused);
    channel2->setPaused(!paused);
     */
    channel2->setPaused(off);
}

void Sound::startLevel(){
    cout << "starting level" << endl;
    channel1->setPaused(false);
    channel2->setPaused(false);
    channel3->setPaused(true);
    
    channel7->setPaused(true);
}

void Sound::endLevel(){
    channel1->setPaused(true);
    channel2->setPaused(true);
    channel3->setPaused(true);
    
    channel7->setPaused(false);
}
