#define NOMINMAX
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include "Framework.h"
#include "Graphics.h"
#include "Renderable.h"
#include "Room.h"
#include "CatmullRom.h"
#include "Rusko.h"
#include "ParticleManager.h"
#include "Sound.h"
#include "loadscreen.h"
#include "RuskoPhysics.h"
#include "RuskoBounds.h"
#include "RuskoCollisions.h"
#include <pthread.h>

// PI def
const float PI = 3.14159265;
const int FLOOR_POS = -1;

// OpenGL display
int windowWidth  = 640;
int windowHeight = 640;

// Interaction bools
bool upKeyPressed, downKeyPressed, rightKeyPressed, leftKeyPressed;

//System sound
Sound *systemSound;

//Loadscreen
Loadscreen* loadscreen;


// Camera/world positions, initialized at setup
STVector3 camPos, worldPos, lastJump;
float worldAngle;
int groundPos = FLOOR_POS;

// CatmullRom Jump
bool jumpOn;
int rusko_frameJump;
CatmullRom* cr;

//Walk/Jump frame counters
int rusko_frameWalk = 0;

// Lights
float light0Position[4];

// Game states
#define GAME_LOADING 0
#define GAME_RUNNING 1
#define GAME_LSCREEN 2
int gameState = GAME_LOADING;
bool firstLoad = true;

//Current Game Level
int gameLevel = 1;

// List of objects to render
std::vector<Renderable *> renderList;

// Models
Room room;

//Rusko
Rusko* rusko;
RuskoPhysics *ruskoPhys;
RuskoBounds *ruskoBounds;
RuskoCollisions *collisions;

//Particles that must rotate as part of the world
ParticleManager *particles;
fireCircleEmitter *torchFire;
//windCircleEmitter;

//Torch Fire
ParticleManager *torchParticles;

float xpos = 0.0f;
float zpos = 0.0f;
float ypos = 0.0f;

const int fps=50;
int window_id=0;


/**
 * Makes sure every time new level starts
 * these variables are reset
 **/
void resetGameVariables(){
    //Initial world position
    //how is the room positioned... DEPENDS ON ROOM
    worldPos.x = -5;
    worldPos.y = groundPos;
    worldPos.z = 2;
    worldAngle = 180;
    
    //Camera
    camPos.x = 0;
    camPos.y = 2;
    camPos.z = -2;
    
    //Jump stuff
    jumpOn = false;
    rusko_frameJump = 0;
    lastJump.x = lastJump.y = lastJump.z = 0;

    //Interaction/keyboard
    upKeyPressed = downKeyPressed = rightKeyPressed = leftKeyPressed = false;
}


/**
 * Initializes variables, and does initial setup
 **/
void setup(){
    // Initialize OpenGL defaults
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
    
    resetGameVariables();
    
    particles = new ParticleManager(20000);
    torchParticles = new ParticleManager(3000);
    
    //Rusko model
    rusko = new Rusko();
    ruskoPhys = new RuskoPhysics(-groundPos);
    //Rusko bounds
    ruskoBounds = new RuskoBounds();
    
    //Sound
    systemSound = new Sound();
    
    //Loadscreen
    loadscreen = new Loadscreen();
    
    vector3 pos = vector3(xpos,ypos,zpos);
    //vector3 fire = vector3(0,-.0001,0);
    vector3 fire = vector3(.0005,.0001,.0005);
    vector3 wind = vector3(0,.0001,.0005);
    vector3 dir = vector3(0,1,0);
    vector3 dirVar = vector3(.25,0,.25);


    fireCircleEmitter *f = new fireCircleEmitter(.12, &particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    torchParticles->addEmitter(f);
    
    torchFire = new fireCircleEmitter(&particles->particlePool, particles->nextId(), "../Particles/fireRecording.txt");
    particles->addEmitter(torchFire);
    
    //Jump stuff-CatmullRom file uploaded
    cr = new CatmullRom("models/rusko/jump_controlPoints.txt");
    
    // Enable global lights
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float light0Position[4] = {camPos.x, camPos.y, camPos.z, 1.f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    
    //Enable fire light
    glEnable(GL_LIGHT1);
    GLfloat spotAmbientColor[] = {0.0, 0.0 , 0.0, 1.0};
    GLfloat spotDiffuseColor[] = {1.0, 0.2, 0.0, 1.0};
    GLfloat spotSpecularColor[] = {1.0, 0.2 , 0.0, 1.0};
    GLfloat spotPosition[] = {xpos, ypos, zpos, 1};
    glLightfv(GL_LIGHT1, GL_AMBIENT, spotAmbientColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuseColor);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecularColor);
    glLightfv(GL_LIGHT1, GL_POSITION, spotPosition);
    
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,2);
    
	// Enable texture
	glEnable(GL_TEXTURE_2D);
}


// Initializes the graphics system (i.e. Open GL)
void GraphicsInit(int argc, char** argv)
{
	// Initialize GLUT
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA); 
	glutInitWindowSize(windowWidth, windowHeight); 
	glutCreateWindow("Rusko's Adventures");

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
    
    setup();

}


void gameLogic() {
	if (gameState == GAME_LOADING)
    {
		room = Room();
		room.setLevel(gameLevel);
        ruskoBounds->setRoom(&room);
        collisions = new RuskoCollisions(&room);
        if (firstLoad){
            loadscreen->render(-1, windowWidth, windowHeight);
        } else gameState = GAME_LSCREEN;
    }
    else if (gameState == GAME_RUNNING)
    {
		renderList.push_back((Renderable *)&room);
    }
    else if (gameState == GAME_LSCREEN)
    {
        resetGameVariables();
        loadscreen->render(gameLevel, windowWidth, windowHeight);
    }
}

/** Renders the world with applied transforms **/
void renderWorld(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix ();
    glLoadIdentity();
    
    glRotated(worldAngle, 0, 1, 0);  //rotates world with given angle
    
    worldPos.y = -ruskoPhys->yPos;
    glTranslatef(worldPos.x, worldPos.y, worldPos.z);  //translates to new position
    

 	// Draw
	for(unsigned i = 0; i<renderList.size(); i++)
		renderList[i]->render();
	renderList.clear();
    
    //Draw rotated particles
    particles->display();
    
    glPopMatrix ();
}


/**
 * Jump function
 * Uses catmull rom to simulate jump
 */
void jump()
{
    rusko_frameJump += 3;
    int totPoints = cr->totalPoints;

    if (rusko_frameJump >= totPoints) {
        jumpOn = false;
        lastJump.x = lastJump.y = lastJump.z = 0;
        worldPos.y = groundPos;
    }
    else {
        STPoint3 fu = cr->pointAt(rusko_frameJump);
        
        //calculates where the world needs to be after a jump
        worldPos.y -= (fu.y - lastJump.y);
        worldPos.z -= (fu.z - lastJump.z)*cos(PI/180*worldAngle);
        worldPos.x += (fu.z - lastJump.z)*sin(PI/180*worldAngle);
        
        lastJump.y = fu.y;
        lastJump.z = fu.z; //makes sure to record lastJump.z position
    }
}


/** Rends the main character, who should remain at origin**/
void drawRusko(){

    STPoint3 torchPos;

    /**deals with animation**/
    
    //walk forward
    if (upKeyPressed && !jumpOn) {
        torchPos = rusko->renderWalk(rusko_frameWalk);
        rusko_frameWalk++;
    }
    
    //walk backward
    else if (downKeyPressed && !jumpOn) {
        torchPos = rusko->renderBackWalk(rusko_frameWalk);
        rusko_frameWalk++;
    }
    
    //turning left
    else if (leftKeyPressed){
        torchPos = rusko->renderStepLeft(rusko_frameWalk);
        rusko_frameWalk++;
    }
    //turning right
    else if (rightKeyPressed){
        torchPos = rusko->renderStepRight(rusko_frameWalk);
        rusko_frameWalk++;
    }
    
    //jump
    else if (jumpOn) {
        rusko_frameWalk++;
        torchPos = rusko->renderJump(rusko_frameWalk);
    }
    
    //still
    else {
        torchPos = rusko->render(0);
    }
    
    xpos = torchPos.x;
    ypos = torchPos.y;
    zpos = torchPos.z;
    
}


/**
 * Window resize callback function
 */
void ReshapeCallback(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, windowWidth, windowHeight);
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    float aspectRatio = (float) windowWidth / (float) windowHeight;
    
    gluPerspective(75, aspectRatio, 1, 1000.0f);

    //since object is at the origin, looks x steps steps ahead
    float x_steps = 2;
    gluLookAt(camPos.x, camPos.y, camPos.z, 0, 0, x_steps, 0, 1, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawParticles(){
    torchParticles->resetPos(0, vector3(xpos, ypos, zpos));
    torchParticles->display();
    torchParticles->update();
    static int frame = 0;
    frame++;
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,2 + sinf(frame));
}


/**
 * Display callback function
 */
void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    gameLogic();

    if (gameState == GAME_RUNNING){
        renderWorld(); //transforms and draws the world as Rusko moves around
        drawRusko();  //transforms and draws Rusko
        drawParticles();
        particles->update();
    }
    
    ReshapeCallback(windowWidth, windowHeight);
    
    glFlush();
    
    glutSwapBuffers();
}




/**
 * Timer function for moving forward/back, and turning
 */
static void Timer(int value)
{
    if (gameState == GAME_RUNNING) {
        
        STVector3 futurePos = STVector3(worldPos.x, worldPos.y, worldPos.z);
        
        if (upKeyPressed) {
            futurePos.x = worldPos.x + 1*sin(PI/180*worldAngle);
            futurePos.z = worldPos.z - 1*cos(PI/180*worldAngle);
            
            if (ruskoBounds->inBounds(futurePos) && collisions->lateralMovement){
                worldPos.x = futurePos.x;
                worldPos.z = futurePos.z;
                
                if(systemSound->walking == false && systemSound->jumping != true){
                    systemSound->startWalking();
                }
                if(systemSound->jumping == true) systemSound->stopWalking();
                }else{
                
            }
            
        }
        
        else if (downKeyPressed) {
            futurePos.x -= 1*sin(PI/180*worldAngle);
            futurePos.z += 1*cos(PI/180*worldAngle);
            
            if (ruskoBounds->inBounds(futurePos)){
                worldPos.x = futurePos.x;
                worldPos.z = futurePos.z;
            }
        }
        
        if (rightKeyPressed){
            if (worldAngle == 360) worldAngle = 0;
            worldAngle += 5;
        }
        if (leftKeyPressed){
            if (worldAngle == 360) worldAngle = 0;
            worldAngle -= 5;
        }
        if (upKeyPressed || downKeyPressed || rightKeyPressed || leftKeyPressed ){
            glutPostRedisplay();
        }
        systemSound->update();
        
    }
    
    glutTimerFunc(2000/fps, Timer, 0); // 10 milliseconds
}


/**
 * Timer function for jumping, it moves faster than normal timer
 */
static void TimerJump(int value){
    if (gameState == GAME_RUNNING){
        

        ruskoPhys->update((float)5/fps);
        collisions->checkForCollisions();
        
        if (jumpOn) {
            jump();
            if(systemSound->jumping == false) systemSound->jump();
            glutPostRedisplay();
        }else{
            systemSound->jumping = false;
        }
    }
    glutTimerFunc(100/fps, TimerJump, 0); // 10 milliseconds
}


/**
 * Keyboard callback function
 */
void KeyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:// exit program on escape press
            exit(0);
            break;
        case ' ':  //activates jumping
            if (!jumpOn) {
                jumpOn = true;
                rusko_frameJump = 0;
            }
            glutPostRedisplay();
            break;
        case 'j':  //activates jumping
            ruskoPhys->jump();
            glutPostRedisplay();
            break;
        case 'r': //resets same level
            if (gameState == GAME_RUNNING) {
                gameState = GAME_LSCREEN;
                printf("\n same level again: %i \n", gameLevel);
            }
            glutPostRedisplay();
            break;
        case 13: //toggles from one level to the next
            if (gameState == GAME_LSCREEN) gameState = GAME_RUNNING;
            else if (firstLoad && gameState == GAME_LOADING) {
                gameState = GAME_LSCREEN;
                firstLoad = false;
            }
            else {
                gameState = GAME_LOADING;
                gameLevel++;
                printf("\n oooo new level: %i \n", gameLevel);
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}


/**
 * special cases for up/down/left/right arrows
 **/
void KeySpecial(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) { //turns to the right
        rightKeyPressed = true;
        glutPostRedisplay();
    } else if (key == GLUT_KEY_LEFT) {  //turns to the left
        leftKeyPressed = true;
        glutPostRedisplay();
    } else if (key == GLUT_KEY_UP){  //moves a step forward
        upKeyPressed = true;
        glutPostRedisplay();
    } else if (key == GLUT_KEY_DOWN){ //moves a step back
        downKeyPressed = true;
        glutPostRedisplay();
    }
}

/**
 * special cases for releasing up/down/left/right arrows
 **/
void KeySpecialUp(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT){
        rightKeyPressed = false;
        rusko_frameWalk = 0;
    } else if (key == GLUT_KEY_LEFT){
        leftKeyPressed = false;
        rusko_frameWalk = 0;
    }if (key == GLUT_KEY_UP){
        upKeyPressed = false;
        systemSound->stopWalking();
        rusko_frameWalk = 0;
        rusko_frameJump = 0;
    } else if (key == GLUT_KEY_DOWN){
        downKeyPressed = false;
        rusko_frameWalk = 0;
        rusko_frameJump = 0;
    }
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/fps,timer,window_id);
}

// To be called to render every scene
void GraphicsMainLoop()
{
    glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
    
    glutTimerFunc(2000/fps, Timer, 0); //timer for moving up/down/turning
    glutTimerFunc(100/fps, TimerJump, 0); //timer for jumping
    glutTimerFunc(1000/fps,timer,window_id);
    
    glutKeyboardFunc(KeyboardCallback);
    glutSpecialFunc(KeySpecial);
    glutSpecialUpFunc(KeySpecialUp);
    
	glutMainLoop();
}