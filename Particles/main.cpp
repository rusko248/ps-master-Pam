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
#include "ParticleManager.h"
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

using namespace std;

int win_width = 640;
int win_height = 480;
int window_id=0;
const int fps=50;
ParticleManager *particles;
float xpos = 0.0f;
float zpos = 0.0f;

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
/*
    glBegin(GL_QUADS);
    glVertex3d(-1, -1, -1);
    glVertex3d(1, -1, -1);
    glVertex3d(1, 1, -1);
    glVertex3d(-1, 1, -1);
    glEnd();
*/
    particles->resetPos(0, vector3(xpos, 0, zpos));
    particles->display();
    particles->update();
    
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
        case 27: // Escape key
            delete particles;
            exit(0);
            break;
        case 'q':
        case 'Q':
            delete particles;
            exit(0);
	}
    glutPostRedisplay();
}

int main (int argc, char *argv[])
{
    cout << "Starting" << endl;
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( win_width, win_height );
    glutPositionWindow(100, 150);
    window_id=glutCreateWindow("Particle System");
	glutSetWindow(window_id);
    
    vector3 pos = vector3(0,0,0);
    //vector3 fire = vector3(0,-.0001,0);
    vector3 fire = vector3(.0005,.0001,.0005);
    vector3 wind = vector3(0,.0001,.0005);
    vector3 dir = vector3(0,1,0);
    vector3 dirVar = vector3(.25,0,.25);
    particles = new ParticleManager(7000);
    cout << "Pool created" << endl;
    //particles->addEmitter(pos, 0, 30, 0, 30, .01, .001, 200, 5, 2, 40, 0, pos);
    
    //particles->addEmitter(pos, 1, 5, -30, 0, .005, 1, 2000, 50, 20, 40, 0, pos);
    //particles->addEmitter(pos, 1, 5, -30, 0, .02, 0, 2000, 50, 20, 15, 5,fire);
    //particles->addEmitter(pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    //pointEmitter *p = new pointEmitter(particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    //circleEmitter *p = new circleEmitter(.05, particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    //fireCircleEmitter *p = new fireCircleEmitter(.05, particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    dirVar = vector3(0,0,0);
    dir = vector3(-1,0,0);
    //windCircleEmitter *p = new windCircleEmitter(.05, particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    windCircleEmitter *p = new windCircleEmitter(.05, &particles->particlePool, particles->nextId(), pos, dir, dirVar, .1, .02, 6000, 100, 20, 70, 10, wind);
    particles->addEmitter(p);

    cout << "Emitter created" << endl;

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );

	glutTimerFunc(1000/fps,timer,window_id);
    
	glutMainLoop();
}
