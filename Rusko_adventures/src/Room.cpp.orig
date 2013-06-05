#define NOMINMAX
#define _USE_MATH_DEFINES

#include "Room.h"
#include <cmath>




using namespace std;

#define PI 3.14159265

#define FREE '0'
#define TORCH '1'
#define BOX '2'
#define SPIKES '3'
#define PIT '4'
#define SAFE '9'

float torchScale = 0.5f;
float boxScale = 0.7f;
int pitSize = 3;

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

// Torches related
int numTorches;
int numHighTorches; // high torches 3-4 steps
float minHeight = 1.0f, maxHeight = 10.0f, highHeight = 6.0f;

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
	//delete floorBrickImage, wallBrickImage;
	//delete floorTexture, wallTexture;
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
	numTorches = numHighTorches = 0;

	torch = Torch(torchScale*scale);
	box = Box(boxScale*scale);
	spikes = Spikes();
<<<<<<< HEAD

	floorBrickImage = new STImage("models/Room/BrickFloor.jpg");
	wallBrickImage = new STImage("models/Room/BrickWall.jpg");
	//floorTexture = new STTexture(floorBrickImage);
	//wallTexture = new STTexture(wallBrickImage);
=======
>>>>>>> c6b8557adbd0e1ffe1edb52c696f8ae6511d420e
}

void Room::setLevel(int lv) {
	level = lv;
    
	generateTorches();
	generateObstacles();
    
    floorBrickImage = new STImage("models/Room/BrickFloor.jpg");
    wallBrickImage = new STImage("models/Room/BrickWall.jpg");
    floorTexture = new STTexture(floorBrickImage);
    wallTexture = new STTexture(wallBrickImage);
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
				if (floor->objPos[floor->getIndex(u, v)] == PIT) continue;
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
			if (u == 0 || u == floor->width-1 || v == 0 || v == floor->length-1) break;
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
				if (j == 0) { glTranslatef(0, -scale/2.f-box.bbox.miny, box.bbox.minz); glRotatef(180.0f, 0, 1, 0); }
				else if (j == 1) { glTranslatef(-box.bbox.minz, -scale/2.f-box.bbox.miny, 0); glRotatef(90.0f, 0, 1, 0); }
				else if (j == 2) { glTranslatef(0, -scale/2.f-box.bbox.miny, -box.bbox.minz); }
				else if (j == 3) { glTranslatef(box.bbox.minz, -scale/2.f-box.bbox.miny, 0); glRotatef(270.0f, 0, 1, 0); }
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
		walls[2]->objPos[walls[2]->getIndex(walls[2]->base/2, (int)(2/scale))] = TORCH;
		return;
	}

	srand(time(NULL));
	numTorches = rand() % 3 + level;
	numHighTorches = numTorches / 5;

	std::vector<int> wallPos, basePos, heightPos;
	int countHighTorches = 0;
	for (int i = 0; i < numTorches; ++i) {
		// select wall
		int wallpos = rand() % 4;
		wallPos.push_back(wallpos);
		// select base position
		int basepos = rand() % walls[wallpos]->base;
		// select height position
		int heightMin=0, heightMax=0, heightpos=0;
		if (countHighTorches < numHighTorches) {
			heightMin = (int)ceilf(highHeight/scale), heightMax = min((int)floorf(maxHeight/scale), walls[wallpos]->height-1);
			heightpos = rand() % (heightMax-heightMin+1) + heightMin;
			countHighTorches++;
		} else {
			heightMin = (int)ceilf(minHeight/scale), heightMax = min((int)floorf(highHeight/scale), walls[wallpos]->height-1);
			heightpos = rand() % (heightMax-heightMin+1) + heightMin;
		}
		// prevent two torches vertically and closely aligned
		while ((heightpos < walls[wallpos]->height-1 && walls[wallpos]->objPos[walls[wallpos]->getIndex(basepos, heightpos+1)] == TORCH) || 
			(heightpos < walls[wallpos]->height-2 && walls[wallpos]->objPos[walls[wallpos]->getIndex(basepos, heightpos+2)] == TORCH) || 
			(heightpos > 0 && walls[wallpos]->objPos[walls[wallpos]->getIndex(basepos, heightpos-1)] == TORCH) ||
			(heightpos > 1 && walls[wallpos]->objPos[walls[wallpos]->getIndex(basepos, heightpos-2)] == TORCH)) {
			basepos = rand() % walls[wallpos]->base;
			heightpos = rand() % (heightMax-heightMin+1) + heightMin;
		}
		basePos.push_back(basepos);
		heightPos.push_back(heightpos);
	}

	for (int i = 0; i < numTorches; ++i) {
		walls[wallPos[i]]->objPos[walls[wallPos[i]]->getIndex(basePos[i], heightPos[i])] = TORCH;
	}
}

void Room::generateObstacles() {
	if (level == 1) {
		floor->objPos[floor->getIndex(floor->width/2, floor->length-1)] = BOX;
		walls[2]->objPos[walls[2]->getIndex(walls[2]->base/2, 0)] = BOX;
		return;
	}

	srand(time(NULL));
	for (int wallpos = 0; wallpos < 4; ++wallpos) {
		std::string objpos = walls[wallpos]->objPos;
		for (unsigned int i = 0; i < objpos.length(); ++i) {
			if (objpos[i] != TORCH) continue;
			int v = i / walls[wallpos]->base;
			int u = i - v*walls[wallpos]->base;

			if (v > 1) walls[wallpos]->objPos[walls[wallpos]->getIndex(u, v-2)] = BOX;
			if (v <= 2) continue;

			bool prevTorch = false, nextTorch = false;
			bool prevBox = false, nextBox = false;
			int prevwallpos = (wallpos == 0) ? 3 : wallpos-1;
			int nextwallpos = (wallpos == 3) ? 0 : wallpos+1;
			int prevu = walls[prevwallpos]->base-1;
			int nextu = 0;
			if (u > 0) { prevwallpos = wallpos; prevu = u-1; }
			if (u < walls[wallpos]->base-1) { nextwallpos = wallpos; nextu = u+1; }
			for (int j = 0; j < walls[prevwallpos]->height; ++j) {
				if (walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, j)] == TORCH)
					prevTorch = true;
				if (walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, j)] == BOX)
					prevBox = true;
				if (prevTorch && prevBox) break;
			}
			for (int j = 0; j < walls[nextwallpos]->height; ++j) {
				if (walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, j)] == TORCH)
					nextTorch = true;
				if (walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, j)] == BOX)
					nextBox = true;
				if (nextTorch && nextBox) break;
			}

			if (prevTorch && nextTorch) {
				if (wallpos == 0) floor->objPos[floor->getIndex(floor->width-1-u, 0)] = BOX;
				else if (wallpos == 1) floor->objPos[floor->getIndex(0, u)] = BOX;
				else if (wallpos == 2) floor->objPos[floor->getIndex(u, floor->length-1)] = BOX;
				else if (wallpos == 3) floor->objPos[floor->getIndex(floor->width-1, floor->length-1-u)] = BOX;
				continue;
			}
			if (prevTorch && !nextTorch) {
				int newheight = rand() % 5 + v - 3;
				walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, newheight)] = BOX;
				if (nextwallpos == 0) floor->objPos[floor->getIndex(floor->width-1-nextu, 0)] = BOX;
				else if (nextwallpos == 1) floor->objPos[floor->getIndex(0, nextu)] = BOX;
				else if (nextwallpos == 2) floor->objPos[floor->getIndex(nextu, floor->length-1)] = BOX;
				else if (nextwallpos == 3) floor->objPos[floor->getIndex(floor->width-1, floor->length-1-nextu)] = BOX;
				continue;
			}
			if (!prevTorch && nextTorch) {
				int newheight = rand() % 5 + v - 3;
				walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, newheight)] = BOX;
				if (prevwallpos == 0) floor->objPos[floor->getIndex(floor->width-1-prevu, 0)] = BOX;
				else if (prevwallpos == 1) floor->objPos[floor->getIndex(0, prevu)] = BOX;
				else if (prevwallpos == 2) floor->objPos[floor->getIndex(prevu, floor->length-1)] = BOX;
				else if (prevwallpos == 3) floor->objPos[floor->getIndex(floor->width-1, floor->length-1-prevu)] = BOX;
				continue;
			}
			if (!prevTorch && !nextTorch) {
				int pickside = rand() % 2;
				int newwallpos = 0;
				int newu = 0;
				if (pickside == 0) { newwallpos = prevwallpos; newu = prevu; }
				else { newwallpos = nextwallpos; newu = nextu; }
				int newheight = rand() % 5 + v - 3;
				walls[newwallpos]->objPos[walls[newwallpos]->getIndex(newu, newheight)] = BOX;
				if (newwallpos == 0) floor->objPos[floor->getIndex(floor->width-1-newu, 0)] = BOX;
				else if (newwallpos == 1) floor->objPos[floor->getIndex(0, newu)] = BOX;
				else if (newwallpos == 2) floor->objPos[floor->getIndex(newu, floor->length-1)] = BOX;
				else if (newwallpos == 3) floor->objPos[floor->getIndex(floor->width-1, floor->length-1-newu)] = BOX;
				continue;
			}
		}
	}

	// Create pits
	srand(time(NULL));
	int numPits = min(numTorches / 3, 4);
	int countPits = 0;
	while (countPits < numPits) {
		int u = rand() % (floor->width-2) + 1;
		int v = rand() % (floor->length-2) + 1;
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (floor->objPos[floor->getIndex(u+i, v+j)] == FREE)
					floor->objPos[floor->getIndex(u+i, v+j)] = PIT;
			}
		}
		countPits++;
	}
}