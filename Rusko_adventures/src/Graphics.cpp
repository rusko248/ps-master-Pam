#define NOMINMAX
#define _USE_MATH_DEFINES

#include <cmath>
#include "Framework.h"
#include "Graphics.h"
#include "Renderable.h"
//#include "DeferredLighting.h" //for deferred lighting
#include "Room.h"
#include <vector>

// Windows
int windowWidth = 640, windowHeight = 480;

// Mouse
bool leftDown = false, rightDown = false, middleDown = false;

// Camera
STVector2 lastPos;
Camera cam;
float zNear = .1f;
float zFar = 100.f;

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

Rusko* rusko;

//Fire
ParticleManager *particles;
fireCircleEmitter *f;
turbulentCircleEmitter *w;
float xpos = 0.0f;
float zpos = 0.0f;
float ypos = 0.0f;

const int fps=50;
int window_id=0;

/**
 * Initializes variables, and does initial setup
 **/
void setup(){
    // Initialize OpenGL defaults
    glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
    
    //Initial world position
    worldPos.x = 0;
    worldPos.y = initialYPos; //how is the room positioned?
    worldPos.z = 0;
    worldAngle = -90;
    
    //Sound
    systemSound = new Sound();
    
    //Rusko position
    camPos.x = 0;
    camPos.y = 2;
    camPos.z = -2.5;
    //Rusko model
    rusko = new Rusko();
    
    //Fire model
    xpos = -.6;
    ypos = .6;
    zpos=.25;

    vector3 pos = vector3(xpos,ypos,zpos);
    //vector3 fire = vector3(0,-.0001,0);
    vector3 fire = vector3(.0005,.0001,.0005);
    vector3 wind = vector3(0,.0001,.0005);
    vector3 dir = vector3(0,1,0);
    vector3 dirVar = vector3(.25,0,.25);
    particles = new ParticleManager(7000);

    f = new fireCircleEmitter(.12, &particles->particlePool, particles->nextId(), pos, dir, dirVar, .02, 0, 2000, 50, 20, 15, 5, fire);
    particles->addEmitter(f);
    
    dirVar = vector3(.005,.02,.02);
    dir = vector3(-1,0,0);
    vector3 windPos = vector3(0,.6,0);
    new turbulentCircleEmitter(.4, &particles->particlePool, particles->nextId(), windPos, dir, dirVar, .005, .001, 2500, 15, 1, 150, 10, wind);
    particles->addEmitter(f);
    
    //Jump stuff-CatmullRom file uploaded
    jumpOn = false;
    rusko_frameJump = 0;
    lastJump.x = lastJump.y = lastJump.z = 0;

    cr = new CatmullRom("models/rusko/jump_controlPoints.txt");
    
    //Interaction/keyboard
    upKeyPressed = downKeyPressed = false;
    
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

//Lighting
//DeferredLighting* dfe;
//std::string shaderPath = "../../shaders";	// Path for DeferredLighting shaders

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

/*---------------------------
Is used for point lights in 
deferred lighting
----------------------------*/
void DrawPointLights()
{
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//View();

	dfe->SetPointLightColor(1.0, 1.0, 1.0);
	dfe->SetRadius(5.0f);
	glPushMatrix();
	glTranslatef(2.0f, 2.0f, 6.0f);
//	glTranslatef(-2.0f, -5.0f, -6.0f);
	glutSolidSphere(5.0f, 10, 10);
	glPopMatrix();

	dfe->SetPointLightColor(1.0, 1.0, 1.0);
	dfe->SetRadius(5.0f);
	glPushMatrix();
	glTranslatef(-2.0f, 2.0f, -6.0f);
//	glTranslatef(-2.0f, -5.0f, -6.0f);
	glutSolidSphere(5.0f, 10, 10);
	glPopMatrix();
}

void display() {
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.pos.x+cam.pan.x, cam.pos.y+cam.pan.y, cam.pos.z+cam.pan.z, cam.pan.x, cam.pan.y, cam.pan.z, cam.up.x, cam.up.y, cam.up.z);

	gameLogic();

	//sets up G-Buffer for lighting
	//dfe->PreDrawScene();
	

	// Draw
	for (unsigned int i = 0; i<renderList.size(); ++i) {
		renderList[i]->render();
	}

	renderList.clear();
	
	//preps for lighting
	//dfe->PostDrawScene();
	
	/*-------------------------
	Performs deferred lighting
	-------------------------*/
	//dfe->DrawDirectionalAndAmbient(windowWidth, windowHeight);
	//dfe->PreDrawPointLights(windowWidth, windowHeight, zNear, zFar);
	//DrawPointLights();
	//dfe->PostDrawPointLights();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);
	else if (button == GLUT_MIDDLE_BUTTON) middleDown = (state == GLUT_DOWN);
	
	lastPos.x = x;
	lastPos.y = y;
}

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
	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}