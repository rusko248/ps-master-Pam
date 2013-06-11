#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Graphics.h"

//fire emitter
fireCircleEmitter *torchFire;

// PI def
const float PI = 3.14159265;

// OpenGL display
int windowWidth  = 640;
int windowHeight = 640;

// Interaction bools
bool upKeyPressed, downKeyPressed, rightKeyPressed, leftKeyPressed;

//Loadscreen
Loadscreen* loadscreen;

// Camera/world positions, initialized at setup
STVector3 camPos, worldPos, futurePos;
float worldAngle;
const int FLOOR_POS = -1;
int groundPos = FLOOR_POS;


//Box frame -- to keep track of moving boxes
int boxFrame1, boxFrame2, boxFrame3;

// Jump
bool jumpOn;
int rusko_frameJump;

//frame counters
int rusko_frameWalk = 0;
static int frame = 0;
const int fps=30;
int window_id=0;

// Lights
float light0Position[4];

// Game states
#define GAME_LOADING 0
#define GAME_RUNNING 1
#define GAME_LSCREEN 2
int gameState = 0;
bool firstLoad = true;
const int TOTAL_LIVES = 3;
int livesLeft;

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
bool dead = false;
bool torchOn = true;

//Deferred Lighting
DeferredLighting * dfe;
std::string shaderPath = "../shaders"; //path to the shaders
float zNear = .1f; //TODO: these need to be caluclated
float zFar = 100.f; //TODO: these need to be caluclated
enum RENDER_MODE{FIXED_FUNCTION, FULL_DEFERRED, POINTLIGHTS, NORMALS, DEPTH, COLORS, NUM_MODES};

//Point Lights
vector<PointLight> plights; //holds the info for the lights in room
float fireLightColor [3] = {0.9, 0.6, 0.0}; //the color of fire light
float ruskoTorchRadius = 1.0;

bool useDeferred = false; //if true = deferred, false = gl lighting


/**function declarations**/
void respawn();


/**
 * Ambient and directional lighting
 */

void Lights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //point light pos
    GLfloat lightPos[] = {camPos.x, camPos.y, camPos.z, 0.0};
    GLfloat ambientComp[] = {0.0, 0.0, 0.0, 1.0};
    
    //diffuse comp
    GLfloat diffuseComp[] = {0.1, 0.1, 0.1, 1.0};
    
    //specular comp
    GLfloat specularComp[] = {0.1, 0.1, 0.0, 1.0};
    
    //Point light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientComp);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseComp);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularComp);
    
    dfe->SetAmbLightColor(0.2, 0.2, 0.2);
    dfe->SetDirLightColor(0.1, 0.1, 0.1);
    dfe->SetDirLightDirection(camPos.x, camPos.y, camPos.z);
    
}

/**
 * Set the characteristics of Rusko's torch light. 
 * This will always be plight[0]
 */

void setTorchLight(float x, float y, float z, float radius) {
	//PLight
	PointLight p;
	p.SetColor(fireLightColor[0], fireLightColor[1], fireLightColor[2]);
	p.SetPosition(x, y, z);
	p.SetAttenuation(0.01, 0.1, 0.1);
	//p.SetAttenuation(1.0, 0.05, 0.0);
	p.SetRadius(radius);
	p.SetGrain(10);

	plights.push_back(p);  
}

/**
 * Draws the particles that are effected by the 
 * world transformations.
 */

void drawRotatedParticles()
{
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix ();
    glLoadIdentity();
    
    glRotated(worldAngle, 0, 1, 0);  //rotates world with given angle
    
    worldPos.y = -ruskoPhys->yPos;
    glTranslatef(worldPos.x, worldPos.y, worldPos.z);  //translates to new position

	//Draw rotated particles
    particles->display();
    
    glPopMatrix ();
}

/**
 * Adds point lights to the plight vector based on the positions
 * in torchFire. plight[0] is saved for Rusko's torch and should
 * not be altered here. torchfire[0] has a dummy light and thus
 * is ignored.
 */
void addPointLights()
{
	int numFire = torchFire->positions.size();
	int numLights = plights.size();

	for(int i = numLights; i < numFire; i++) {
		setTorchLight(torchFire->positions[i].x, torchFire->positions[i].y, torchFire->positions[i].z, 1.0);
	}
}

/**
 * Sets up the point light color and position.
 * ADT
 */
void DrawPointLights() {
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	plights[0].RenderPointLight(dfe);

	glRotated(worldAngle, 0, 1, 0);  //rotates world with given angle
    
    worldPos.y = -ruskoPhys->yPos;

	glTranslatef(worldPos.x, worldPos.y, worldPos.z);  //translates to new position

	for(int i = 1; i < plights.size(); i++) {
		plights[i].RenderPointLight(dfe);
	}
 
	 glPopMatrix ();
}




/**
 * Makes sure every time new level starts
 * these variables are reset
 **/
void resetGameVariables(){
    //Initial world position
    //how is the room positioned... DEPENDS ON ROOM
    STPoint3 startPos = room.getPlayerPosition();
    
    worldPos.x = -startPos.x;
    worldPos.y = groundPos;
    worldPos.z = -startPos.z;
    worldAngle = 180;
    
    //dying variables
    dead = false;
    if (firstLoad) livesLeft = TOTAL_LIVES;
    
    //Camera
    camPos.x = 0;
    camPos.y = 2;
    camPos.z = -2;
    
    //Jump stuff
    jumpOn = false;
    rusko_frameJump = 0;

    //Interaction/keyboard
    upKeyPressed = downKeyPressed = rightKeyPressed = leftKeyPressed = false;

	//reset plights
	plights.clear();
	setTorchLight(xpos, ypos, zpos, ruskoTorchRadius);
    
    srand(time(NULL));
    boxFrame1 = rand() % 10;
    boxFrame2 = rand() % 10;
    boxFrame3 = rand() % 10;
}


/**
 * Initializes variables, and does initial setup
 **/
void setup(){
    cout << "Setting up" << endl;
    // Initialize OpenGL defaults
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);


	if(useDeferred) {
		//------------------------//
		//DEFERRED LIGHTING SET-UP//
		//------------------------//
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_NORMALIZE);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//------------------------//
		//  END DEFERRED SET-UP   //
		//------------------------//
	}
    
    resetGameVariables();
    
    //Rusko model
    rusko = new Rusko();
    ruskoPhys = new RuskoPhysics(-groundPos);
    //Rusko bounds
    ruskoBounds = new RuskoBounds();
    
    //Loadscreen
    loadscreen = new Loadscreen();
    
    vector3 pos = vector3(xpos,ypos,zpos);
    vector3 fire = vector3(.0005,.0001,.0005);
    vector3 dir = vector3(0,1,0);
    vector3 dirVar = vector3(.25,0,.25);

    fireCircleEmitter *f = new fireCircleEmitter(.12, &particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    torchParticles->addEmitter(f);
    
    //sets the point light for the torch
	setTorchLight(xpos, ypos, zpos, ruskoTorchRadius);
    
    
    if(!useDeferred) {
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
	}

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
        systemSound->endLevel();
        cout << "loading" << endl;
        room = Room();
        room.setLevel(gameLevel);
        ruskoBounds->setRoom(&room);
        collisions = new RuskoCollisions(&room);
		plights.clear();
		setTorchLight(xpos, ypos, zpos, ruskoTorchRadius);
        gameState = GAME_LSCREEN;
    }
    else if (gameState == GAME_RUNNING)
    {
        if(dead) {
            livesLeft--;
            respawn();
        }
        collisions->checkForCollisions();
        
		renderList.push_back((Renderable *)&room);
        if (collisions->torchesAllLit) {
            gameLevel++;
            gameState = GAME_LOADING;
        }

    }
    else if (gameState == GAME_LSCREEN)
    {
        if (firstLoad){
            loadscreen->renderWelcomeScreen();
        }
        else if (livesLeft == 0) {
            loadscreen->renderGameOver();
        }
        else {
            resetGameVariables();
            loadscreen->render(gameLevel, room.getNumTorches());
        }

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
    
	//------------------------//
	//    MATERIAL SET-UP     //
	//------------------------//
	
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	dfe->SetMaterialTexture(0, true);

	//------------------------//
	//  END MATERIAL SET-UP   //
	//------------------------//

 	// Draw
	for(unsigned i = 0; i<renderList.size(); i++)
		renderList[i]->render();
	renderList.clear();

	//------------------------//
	//    RELEASE TEXTURE     //
	//------------------------//

	glDisable(GL_TEXTURE_2D);
	dfe->SetMaterialTexture(0, false);

	//------------------------//
	//      TEXTURE FREED     //
	//------------------------//

    //Draw rotated particles
    //particles->display(); //not in right spot for deferred rendering
    
    glPopMatrix ();
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
    else if (leftKeyPressed && !jumpOn){
        torchPos = rusko->renderStepLeft(rusko_frameWalk);
        rusko_frameWalk++;
    }
    //turning right
    else if (rightKeyPressed && !jumpOn){
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

	plights[0].SetPosition(xpos, ypos, zpos); //update the torch light
    
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

/**
 * Display callback function
 */
void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    gameLogic();

    if (gameState == GAME_RUNNING){
		if(useDeferred) {
			//UPDATE PLIGHTS NEEDED
			if(plights.size() < torchFire->positions.size()) {
				addPointLights();
			}
			//BUILD G-BUFFER
			dfe->PreDrawScene(); //lighting ADT
            Lights();
            
			//DRAW OBJECTS AND EVIRONMENT
			//GETS STORED IN G-BUFFER FOR RENDERING
			renderWorld(); //transforms and draws the world as Rusko moves around
			drawRusko();  //transforms and draws Rusko
		
			//PREPARE FOR RENDING
			dfe->PostDrawScene(); //lighting ADT

			//-------------------------------//
			// Render the scene with shaders //
			//-------------------------------//
			dfe->DrawColors(windowWidth, windowHeight);
			dfe->PreDrawPointLights(windowWidth, windowHeight, zNear, zFar);
			DrawPointLights();
			dfe->PostDrawPointLights();
			//-----------------------------//
			//    End render the scene     //
			//-----------------------------//

		} else {
			renderWorld(); //transforms and draws the world as Rusko moves around
			drawRusko();  //transforms and draws Rusko
		}
		//FIRE RENDERED AFTER EVERYTHING ELSE
		drawRotatedParticles();
        torchParticles->display();
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
    frame++;
    boxFrame1++; boxFrame2++; boxFrame3++;
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,2 + sinf(frame));
    if (gameState == GAME_RUNNING) {
        futurePos = STVector3(worldPos.x, worldPos.y, worldPos.z);
        
        if (upKeyPressed) {
            futurePos.x = worldPos.x + 1*sin(PI/180*worldAngle);
            futurePos.z = worldPos.z - 1*cos(PI/180*worldAngle);
            
            if(jumpOn && ruskoPhys->movingDuringJump == false){
                futurePos.x = worldPos.x;
                futurePos.z = worldPos.z;
            }
            
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
            
            if(jumpOn && ruskoPhys->movingDuringJump == false){
                futurePos.x = worldPos.x;
                futurePos.z = worldPos.z;
            }
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
        
    }
    
    glutTimerFunc(2000/fps, Timer, 0); // 10 milliseconds
}


void resetLevel(){
    //    if (gameState == GAME_RUNNING) {
    //        gameState = GAME_LSCREEN;
    //        printf("\n same level again: %i \n", gameLevel);
    //    }
    ruskoPhys->reset();
    collisions->reset();
    resetGameVariables();
    glutPostRedisplay();
}

void respawn(){
    dead = false;
    
    if (gameState == GAME_RUNNING) {
        gameState = GAME_LSCREEN;
    }
    glutPostRedisplay();
    
    resetLevel();
}

void nextLevel(){
    ruskoPhys->reset();
    if (firstLoad && gameState == GAME_LSCREEN){
        gameState = GAME_LSCREEN;
        firstLoad = false;
    }
    else if (livesLeft == 0) {
             firstLoad = true;
             gameLevel = 1;
             livesLeft = TOTAL_LIVES;
             gameState = GAME_LOADING;
    }
    else if (gameState == GAME_LSCREEN){
        gameState = GAME_RUNNING;
        systemSound->startLevel();
        
    }
    else if (gameState == GAME_RUNNING) {
        gameLevel++;
        gameState = GAME_LOADING;
    }
    
    glutPostRedisplay();
}

/**
 * Timer function for jumping, it moves faster than normal timer
 */
static void TimerJump(int value){
    if (gameState == GAME_RUNNING){
        ruskoPhys->update((float)5/fps);
        if (jumpOn) {
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
			delete dfe; //delete Deferred engine
            exit(0);
            break;
        case ' ':  //activates jumping
            if (!jumpOn) {
                jumpOn = true;
                ruskoPhys->jump(upKeyPressed);
                rusko_frameJump = 0;
            }
            glutPostRedisplay();
            break;
        case 'r': //resets same level
            respawn();
            break;
        case 13: //toggles from one level to the next
            nextLevel();
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

	//------------------------//
	//DEFERRED LIGHTING ENGINE//
	//------------------------//
	dfe = new DeferredLighting(windowWidth, windowHeight);
	dfe->Init(shaderPath);
	//------------------------//
	//  END DEFERRED ENGINE   //
	//------------------------//
  
	glutMainLoop();
}