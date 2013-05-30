#define NOMINMAX
#define _USE_MATH_DEFINES

#include <cmath>
#include "Framework.h"
#include "Graphics.h"
#include "Renderable.h"
#include "Room.h"
#include <vector>

// Windows
int windowWidth = 640, windowHeight = 480;

// Mouse
bool leftDown = false, rightDown = false, middleDown = false;

// Camera
STVector2 lastPos;
Camera cam;

// Lights
float light0Position[4];

// Game states
#define GAME_START 0
#define GAME_LOADING 1
#define GAME_RUNNING 2

int gameState = GAME_LOADING;

// List of objects to render
std::vector<Renderable *> renderList;

// Room
Room room;

// Initializes the graphics system (i.e. Open GL)
void GraphicsInit(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(windowWidth, windowHeight); 
	glutCreateWindow("Rusko");

	// Initialize GLEW
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

    // Initialize OpenGL defaults
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// Initialize camera
	cam.pos = STVector3(0.f, 0.f, 4.f);
	cam.up = STVector3(0.f, 1.f, 0.f);
	cam.pan = STVector3(0.f, 0.f, 0.f);

	// Enable global lights
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float light0Position[4] = {cam.pos.x, cam.pos.y, cam.pos.z, 1.f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

	// Enable texture
	glEnable(GL_TEXTURE_2D);
}

void gameLogic() {
	if (gameState == GAME_LOADING) {
		room = Room();
		room.setLevel(1);
		gameState = GAME_RUNNING;
	} else if (gameState == GAME_RUNNING) {
		renderList.push_back((Renderable *)&room);
	}
}

void display() {
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.pos.x+cam.pan.x, cam.pos.y+cam.pan.y, cam.pos.z+cam.pan.z, cam.pan.x, cam.pan.y, cam.pan.z, cam.up.x, cam.up.y, cam.up.z);

	gameLogic();

	// Draw
	for (unsigned int i = 0; i<renderList.size(); ++i) {
		renderList[i]->render();
	}

	renderList.clear();

<<<<<<< HEAD
/**
 * Display callback function
 */
void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    gameLogic();

    renderWorld(); //transforms and draws the world as Rusko moves around
    drawRusko();  //transforms and draws Rusko
    
    
    particles->resetPos(0, vector3(xpos, ypos, zpos));
    particles->display();
    particles->update();
    static int frame = 0;
    frame++;
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,2 + sinf(frame));
    
    ReshapeCallback(windowWidth, windowHeight);

    
    glFlush();
    glutSwapBuffers();
=======
	glutSwapBuffers();
>>>>>>> 52a040ef7155012af3c931b4b40e2a03d7a27999
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);
	else if (button == GLUT_MIDDLE_BUTTON) middleDown = (state == GLUT_DOWN);
	
	lastPos.x = x;
	lastPos.y = y;
}

<<<<<<< HEAD
/**
 * Timer function for moving forward/back, and turning
 */
static void TimerMove(int value)
{
    if (upKeyPressed) {
        worldPos.x += 1*sin(PI/180*worldAngle);
        worldPos.z -= 1*cos(PI/180*worldAngle);
    }
    if (downKeyPressed) {
        worldPos.x -= 1*sin(PI/180*worldAngle);
        worldPos.z += 1*cos(PI/180*worldAngle);
    }
    if (rightKeyPressed){
       worldAngle += 5; 
    }
    if (leftKeyPressed){
       worldAngle -= 5; 
    }
    if (upKeyPressed || downKeyPressed || rightKeyPressed || leftKeyPressed ){
      glutPostRedisplay();  
    }

    glutTimerFunc(100, TimerMove, 0); // 10 milliseconds
}


/**
 * Timer function for jumping, it moves faster than normal timer
 */
static void TimerJump(int value){
    if (jumpOn) {
        jump();
        glutPostRedisplay();
    }
    
    glutTimerFunc(1000/fps, TimerJump, 0); // 10 milliseconds
=======
void mouseMoved(int x, int y) {
	int dx = x - lastPos.x;
	int dy = y - lastPos.y;
	STVector3 curCamera(cam.pos);
	float len = curCamera.Length();
	STVector3 curCameraNormalized = curCamera / len;
	STVector3 right = STVector3::Cross(cam.up, curCameraNormalized);

	if (leftDown) {
		// Assume here that up vector is (0,1,0)
		STVector3 newPos = curCamera - 2*(float)((float)dx/(float)windowWidth) * right + 2*(float)((float)dy/(float)windowHeight) * cam.up;
		newPos.Normalize();
		newPos *= len;
		
		cam.up = cam.up - STVector3::Dot(cam.up, newPos) * newPos / newPos.LengthSq();
		cam.up.Normalize();
		
		cam.pos = newPos;
	}
	else if (rightDown) cam.pos *= pow(1.1,dy*.1);
	else if (middleDown) {
		cam.pan += -2*(float)((float)dx/(float)windowWidth) * right + 2*(float)((float)dy/(float)windowHeight) * cam.up;
	}
	
	lastPos.x = x;
	lastPos.y = y;
	
	glutPostRedisplay();
>>>>>>> 52a040ef7155012af3c931b4b40e2a03d7a27999
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') exit(0);

	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);
	
	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000); // 50 degree vertical viewing angle, zNear = 1, zFar = 1000

	glutPostRedisplay();
}

// To be called to render every scene
void GraphicsMainLoop()
{
<<<<<<< HEAD
    glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
    
    glutTimerFunc(100, TimerMove, 0); //timer for moving up/down/turning
    glutTimerFunc(1000/fps, TimerJump, 0); //timer for jumping
    glutTimerFunc(1000/fps,timer,window_id);
    
    glutKeyboardFunc(KeyboardCallback);
    glutSpecialFunc(KeySpecial);
    glutSpecialUpFunc(KeySpecialUp);
    
=======
	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

>>>>>>> 52a040ef7155012af3c931b4b40e2a03d7a27999
	glutMainLoop();
}