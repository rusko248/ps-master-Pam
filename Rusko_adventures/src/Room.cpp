#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Room.h"
#include <cmath>

using namespace std;

#define PI 3.14159265

#define FREE 0
#define TORCH 1
#define BOX 2
#define SPIKES 3
#define PIT 4

float torchScale = 1.0f;
float boxScale = 1.0f;

Torch torch;
Box box;
Spikes spikes;

// Material
float materialAmbient[]  = { 0.2, 0.2, 0.2, 1.0 };
float materialDiffuse[]  = { 0.2, 0.2, 0.2, 1.0 };
float materialSpecular[] = { 0.4, 0.4, 0.4, 1.0 };
float shininess          = 8.0;

// Room Texture
STImage *floorBrickImage, *wallBrickImage;
STTexture *floorTexture, *wallTexture;

float minHeight = 3.0f, maxHeight = 10.0f;

Room::Room() {
	dim[0] = dim[1] = dim[2] = 10;
	scale = 1.0f;
	
	initRoom();
}

Room::Room(int w, int h, int l, float s) {
	dim[0] = w;
	dim[1] = h;
	dim[2] = l;
	scale = s;

	initRoom();
}

Room::~Room() {
//	delete floorBrickImage, wallBrickImage;
//	delete floorTexture, wallTexture;
}

void Room::initRoom() {
	floor = new Floor;
	floor->width = dim[0];
	floor->length = dim[2];
	floor->objPos.reserve(dim[0]*dim[2]);
	for (int i = 0; i < dim[0]*dim[2]; ++i)
		floor->objPos += '0';

	for (int i = 0; i < 4; ++i) {
		walls[i] = new Wall;
		if (i % 2 == 0) { walls[i]->base = dim[0]; walls[i]->height = dim[1]; }
		else { walls[i]->base = dim[2]; walls[i]->height = dim[1]; }
		walls[i]->objPos.reserve(walls[i]->base*walls[i]->height);
		for (int j = 0; j < walls[i]->base*walls[i]->height; ++j)
			walls[i]->objPos += '0';
	}

	pos = STPoint3(0,0,0);

	level = 1;
	numTorches = 0;

	torch = Torch(torchScale*scale);
	box = Box(boxScale*scale);
	spikes = Spikes();

	floorBrickImage = new STImage("models/Room/BrickFloor.jpg");
	wallBrickImage = new STImage("models/Room/BrickWall.jpg");
	//floorTexture = new STTexture(floorBrickImage);
	//wallTexture = new STTexture(wallBrickImage);
}

void Room::setLevel(int lv) {
	level = lv;
	generateTorches();
	generateObstacles();
}

void Room::render() {
	renderLayout();
	renderObjects();
}

void Room::renderLayout() {
	glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	//floorTexture->Bind();
	glBegin(GL_QUADS);
		// floor
		for (int v = 0; v < floor->length; ++v) {
			for (int u = 0; u < floor->width; ++u) {
				glTexCoord2f(0,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y,pos.z-scale*v);
				glTexCoord2f(0,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y,pos.z-scale*v);
				glTexCoord2f(1,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y,pos.z-scale*(v+1));
				glTexCoord2f(1,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y,pos.z-scale*(v+1));
			}
		}
	glEnd();
	//floorTexture->UnBind();

	//wallTexture->Bind();
	glBegin(GL_QUADS);
		// near wall
		for (int v = 0; v < walls[0]->height; ++v) {
			for (int u = 0; u < walls[0]->base; ++u) {
				glTexCoord2f(0,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y+scale*v,pos.z);
				glTexCoord2f(1,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y+scale*v,pos.z);
				glTexCoord2f(1,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y+scale*(v+1),pos.z);
				glTexCoord2f(0,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y+scale*(v+1),pos.z);
			}
		}

		// left wall
		for (int v = 0; v < walls[1]->height; ++v) {
			for (int u = 0; u < walls[1]->base; ++u) {
				glTexCoord2f(0,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x,pos.y+scale*v,pos.z-scale*u);
				glTexCoord2f(1,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x,pos.y+scale*v,pos.z-scale*(u+1));
				glTexCoord2f(1,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x,pos.y+scale*(v+1),pos.z-scale*(u+1));
				glTexCoord2f(0,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x,pos.y+scale*(v+1),pos.z-scale*u);
			}
		}

		// far wall
		for (int v = 0; v < walls[2]->height; ++v) {
			for (int u = 0; u < walls[2]->base; ++u) {
				glTexCoord2f(0,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y+scale*v,pos.z-scale*floor->length);
				glTexCoord2f(1,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y+scale*v,pos.z-scale*floor->length);
				glTexCoord2f(1,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y+scale*(v+1),pos.z-scale*floor->length);
				glTexCoord2f(0,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y+scale*(v+1),pos.z-scale*floor->length);
			}
		}

		// right wall
		for (int v = 0; v < walls[3]->height; ++v) {
			for (int u = 0; u < walls[3]->base; ++u) {
				glTexCoord2f(0,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*floor->width,pos.y+scale*v,pos.z-scale*u);
				glTexCoord2f(1,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*floor->width,pos.y+scale*v,pos.z-scale*(u+1));
				glTexCoord2f(1,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*floor->width,pos.y+scale*(v+1),pos.z-scale*(u+1));
				glTexCoord2f(0,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*floor->width,pos.y+scale*(v+1),pos.z-scale*u);
			}
		}
	glEnd();
	//wallTexture->UnBind();
}

void Room::renderObjects() {
	// floor
	for (unsigned int i = 0; i < floor->objPos.size(); ++i) {
		if (floor->objPos[i] == FREE) continue;

		glPushMatrix();

		int v = i / floor->width;
		int u = i - v*floor->width;

		glTranslatef(pos.x+scale*((float)u+.5f), pos.y, pos.z-scale*((float)v+.5f));

		switch (floor->objPos[i]) {
		case TORCH:
			glTranslatef(0, -torch.bbox.miny, 0);
			torch.render();
			break;
		case BOX:
			glTranslatef(0, -box.bbox.miny, 0);
			box.render();
			break;
		case SPIKES:
			glTranslatef(0, -spikes.bbox.miny, 0);
			spikes.render();
			break;
		case PIT:
			break;
		}

		glPopMatrix();
	}

	// walls
	for (int j = 0; j < 4; ++j) {
		for (unsigned int i = 0; i < walls[j]->objPos.size(); ++i) {
			if (walls[j]->objPos[i] == FREE) continue;

			glPushMatrix();

			int v = i / walls[j]->base;
			int u = i - v*walls[j]->base;

			if (j == 0) glTranslatef(pos.x+scale*(float)floor->width-scale*((float)u+.5f), pos.y+scale*((float)v+.5f), pos.z);
			else if (j == 1) glTranslatef(pos.x, pos.y+scale*((float)v+.5f), pos.z-scale*((float)u+.5f));
			else if (j == 2) glTranslatef(pos.x+scale*((float)u+.5f), pos.y+scale*((float)v+.5f), pos.z-scale*(float)floor->length);
			else glTranslatef(pos.x+scale*(float)floor->width, pos.y+scale*((float)v+.5f), pos.z-scale*(float)floor->length+scale*((float)u+.5f));

			switch (walls[j]->objPos[i]) {
			case TORCH:
				if (j == 0) { glTranslatef(0, 0, torch.bbox.minz); glRotatef(180.0f, 0, 1, 0); }
				else if (j == 1) { glTranslatef(-torch.bbox.minz, 0, 0); glRotatef(90.0f, 0, 1, 0); }
				else if (j == 2) { glTranslatef(0, 0, -torch.bbox.minz); }
				else if (j == 3) { glTranslatef(torch.bbox.minz, 0, 0); glRotatef(270.0f, 0, 1, 0); }
				torch.render();
				break;
			case BOX:
				box.render();
				break;
			case SPIKES:
				spikes.render();
				break;
			case PIT:
				break;
			}

			glPopMatrix();
		}
	}
}

void Room::generateTorches() {
	if (level == 1) {
		numTorches = 1;
		walls[2]->objPos[walls[2]->getIndex(walls[2]->base/2, walls[2]->height/2)] = TORCH;
		return;
	}

	srand(time(NULL));
	numTorches = rand() % 3 + 2*level - 2;

	std::vector<int> wallPos, basePos, heightPos;
	for (int i = 0; i < numTorches; ++i) {
		// select wall
		int wallpos = rand() % 4;
		wallPos.push_back(wallpos);
		// select base position
		int basepos = rand() % walls[wallpos]->base;
		basePos.push_back(basepos);
		// select height position
		int heightMin = (int)ceilf(minHeight/scale), heightMax = min((int)floorf(maxHeight/scale), walls[wallpos]->height-1);
		int heightpos = rand() % (heightMax-heightMin+1) + heightMin;
		heightPos.push_back(heightpos);
	}

	for (int i = 0; i < numTorches; ++i) {
		walls[wallPos[i]]->objPos[walls[wallPos[i]]->getIndex(basePos[i], heightPos[i])] = TORCH;
	}
}

void Room::generateObstacles() {
	if (level == 1) {
		floor->objPos[floor->getIndex(floor->width/2, floor->length/2)] = BOX;
	}
}