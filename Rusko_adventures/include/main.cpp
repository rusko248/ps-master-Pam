#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// For this example, we need some function to sleep for some seconds,
// so we include the platform specific sleep functions here. This is
// only need for demo purposes and has nothing to do with sound output.
// include console I/O methods (conio.h for windows, our wrapper in linux)
#if defined(WIN32)
#include <windows.h>
#include <conio.h>
inline void sleepSomeTime() { Sleep(100); }
#else
#include "./common/conio.h"
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

int win_width = 640;
int win_height = 480;
int window_id=0;
const int fps=50;
float xpos = 0.0f;
float zpos = 0.0f;
ISoundEngine* engine;
ISound* music;
ISound* torch;
float posOnCircle = 0;
const float radius = 5;

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/fps,timer,window_id);
}

void display( void )
{
    static int frame = 0;
    frame++;
    //cout << "Frame " << frame << endl;
    glClear( GL_COLOR_BUFFER_BIT );

    
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
    
    glFlush();
	glutSwapBuffers();
}

void reshape( int w, int h )
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1,2,9);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,6,0,0,5,0,1,0);
    glViewport( 0, 0, w, h );
    
    win_width = w;
    win_height = h;
    glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y )
{
	switch(key)
	{
        case 'p':
            xpos += .05;
            break;
        case 'o':
            xpos -= .05;
            break;
            
        case 'i':
            zpos += .1;
            break;
        case 'u':
            zpos -= .1;
            break;
        case 'k': {
            vec3df pos(fmodf((float)rand(),radius*2)-radius, 0, 0);
            engine->play3D("/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/3DSound copy/media/bell.wav", pos);
            break;
        }
        case 'l': {
            vec3df pos2(fmodf((float)rand(),radius*2)-radius, 0, 0);
            engine->play3D("/Users/aarondamashek/Documents/Stanford Work/Spring 2013/CS 248/3DSound copy/media/explosion.wav", pos2);
            break;
        }
        case 27: // Escape key
            exit(0);
            break;
        case 'q':
        case 'Q':
            exit(0);

	}
    glutPostRedisplay();
}


// Now let's start with the irrKlang 3D sound engine example 02,
// demonstrating simple 3D sound. Simply startup the engine using
// using createIrrKlangDevice() with default options/parameters.
int main(int argc, char** argv)
{
    cout << "Starting" << endl;
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( win_width, win_height );
    glutPositionWindow(100, 150);
    window_id=glutCreateWindow("Particle System");
	glutSetWindow(window_id);
    
    //
    // Initialize GLEW.
    //
#ifndef __APPLE__
    glewInit();
    if(!GLEW_VERSION_2_0) {
        printf("Your graphics card or graphics driver does\n"
			   "\tnot support OpenGL 2.0, trying ARB extensions\n");
        
        if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
            printf("ARB extensions don't work either.\n");
            printf("\tYou can try updating your graphics drivers.\n"
				   "\tIf that does not work, you will have to find\n");
            printf("\ta machine with a newer graphics card.\n");
            exit(1);
        }
    }
#endif
    
    
    cout << "Emitter created" << endl;
    
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
    
	glutTimerFunc(1000/fps,timer,window_id);
    
    // start the sound engine with default parameters
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
    
	// Print some help text and start the display loop
    
	printf("\nPlaying streamed sound in 3D.");
	printf("\nPress ESCAPE to quit, any other key to play sound at random position.\n\n");
    


	glutMainLoop();
	// don't forget to release the resources as explained above.

	if (music)
		music->drop(); // release music stream.
    if (torch)
		torch->drop(); // release music stream.

	engine->drop(); // delete engine
	return 0;
}
