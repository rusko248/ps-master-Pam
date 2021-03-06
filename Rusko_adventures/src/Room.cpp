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
#define SMOKE '5'
#define MOVABLEBOX '6'
#define SAFE '9'

float torchScale = 0.5f;
float boxScale = 0.8f;
float spikesScale = 0.5f;
int pitSize = 3;

Torch torch;
Box box;
std::vector<Box> mbox; // movable boxes
Spikes spikes;

struct MovableBoxPos {
	MovableBoxPos() {
		wallpos = u = v;
	}

	int wallpos, u, v;
};

struct MovableBoxPosCompare {
	bool operator() (const MovableBoxPos& a, const MovableBoxPos& b) {
		if (a.wallpos < b.wallpos) return true;
		else if (a.wallpos > b.wallpos) return false;
		else {
			if (a.u < b.u) return true;
			else if (a.u > b.u) return false;
			else return (a.v < b.v);
		}
	}
};

std::map<MovableBoxPos, int, MovableBoxPosCompare> mboxMap;
std::map<MovableBoxPos, int, MovableBoxPosCompare> mboxBoundMap;
extern int boxFrame1, boxFrame2, boxFrame3;
std::vector<int> boxFrames;

// World position. Rusko position rel to the room is negative this amount
extern STVector3 worldPos;
// Future position for detecting collision
extern STVector3 futurePos;

// Particles System
extern ParticleManager *particles;
extern fireCircleEmitter *torchFire;

// Smoke
turbulentCircleEmitter *t1, *t3;
extern int groundPos;

// Material
float materialAmbient[]  = { 0.2, 0.2, 0.2, 1.0 };
float materialDiffuse[]  = { 0.2, 0.2, 0.2, 1.0 };
float materialSpecular[] = { 0.4, 0.4, 0.4, 1.0 };
float shininess          = 8.0;

// Room Texture
STImage *floorBrickImage, *wallBrickImage;
STTexture *floorTexture, *wallTexture;

std::vector<std::vector<float> > floorHeight;

// Torches related
float minHeight = 1.0f, maxHeight = 10.0f, highHeight = 6.0f;

Room::Room() {
	dim[0] = 10;
	dim[1] = 10;
	dim[2] = 20;
	scale = 2.0f;
	
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
	delete floorBrickImage, wallBrickImage;
	delete floorTexture, wallTexture;
}

void Room::initRoom() {
	floor = new Floor;
	floor->width = dim[0];
	floor->length = dim[2];
	floor->fwidth = scale * dim[0];
	floor->flength = scale * dim[2];
	floor->objPos.reserve(dim[0]*dim[2]);
	for (int i = 0; i < dim[0]*dim[2]; ++i)
		floor->objPos += '0';

	for (int i = 0; i < 4; ++i) {
		walls[i] = new Wall;
		if (i % 2 == 0) { walls[i]->base = dim[0]; walls[i]->height = dim[1]; }
		else { walls[i]->base = dim[2]; walls[i]->height = dim[1]; }
		walls[i]->fbase = scale * walls[i]->base;
		walls[i]->fheight = scale * walls[i]->height;
		walls[i]->objPos.reserve(walls[i]->base*walls[i]->height);
		for (int j = 0; j < walls[i]->base*walls[i]->height; ++j)
			walls[i]->objPos += '0';
	}

	pos = STPoint3(0,0,0);

	level = 1;
	numTorches = numHighTorches = 0;

	torch = Torch(torchScale*scale);
	box = Box(boxScale*scale);
	spikes = Spikes(spikesScale*scale);

	floorHeight.clear();
	for (int v = 0; v <= floor->length; ++v) {
		std::vector<float> h;
		for (int u = 0; u <= floor->width; ++u) {
			h.push_back(noisef(pos.x+scale*u,pos.y,pos.z-scale*v));
		}
		floorHeight.push_back(h);
	}
}

void Room::setLevel(int lv) {
	level = lv;
    
    particles->reset();
    
    torchFire = new fireCircleEmitter(&particles->particlePool, particles->nextId(), "../Particles/fireRecording-250.txt");
    
    particles->addEmitter(torchFire);
    
	t1 = new turbulentCircleEmitter(&particles->particlePool, particles->nextId(), "../Particles/windRecording-100.txt");
	t3 = new turbulentCircleEmitter(&particles->particlePool, particles->nextId() + 1, "../Particles/windRecording100.txt");

	generateTorches();
	generateObstacles();
	updateOB();

	floorBrickImage = new STImage("models/Room/BrickFloor.jpg");
	wallBrickImage = new STImage("models/Room/BrickWall.jpg");
	floorTexture = new STTexture(floorBrickImage);
	wallTexture = new STTexture(wallBrickImage);
}

void Room::updateOB() {
	// floor
	for (unsigned int i = 0; i < floor->objPos.size(); ++i) {
		if (floor->objPos[i] == FREE) continue;

		int v = i / floor->width;
		int u = i - v*floor->width;

		ObsBound ob = ObsBound();
		ob.type = floor->objPos[i];
		switch (floor->objPos[i]) {
		case TORCH:
			ob.bcir.x = scale*((float)u+.5f);
			ob.bcir.y = -torch.bbox.miny;
			ob.bcir.z = -scale*((float)v+.5f);
			ob.bcir.radius = torch.bcir.radius;
			obList.push_back(ob);
			break;
		case BOX:
		case MOVABLEBOX:
			if (u == 0 || u == floor->width-1 || v == 0 || v == floor->length-1) break;
			ob.bcir.x = scale*((float)u+.5f);
			ob.bcir.y = -box.bbox.miny;
			ob.bcir.z = -scale*((float)v+.5f);
			ob.bcir.radius = box.bcir.radius;
			obList.push_back(ob);
			break;
		case SPIKES:
			break;
		case PIT:
			break;
		}
	}

	// walls
	for (int j = 0; j < 4; ++j) {
		for (unsigned int i = 0; i < walls[j]->objPos.size(); ++i) {
			if (walls[j]->objPos[i] == FREE) continue;

			int v = i / walls[j]->base;
			int u = i - v*walls[j]->base;

			ObsBound ob = ObsBound();
			ob.type = walls[j]->objPos[i];
			switch (walls[j]->objPos[i]) {
			case TORCH:
				{
				if (j == 0) {
					ob.bcir.x = scale*(float)floor->width-scale*((float)u+.5f);
					ob.bcir.y = scale*((float)v+.5f);
					ob.bcir.z = torch.bbox.minz;
				} else if (j == 1) {
					ob.bcir.x = -torch.bbox.minz;
					ob.bcir.y = scale*((float)v+.5f);
					ob.bcir.z = -scale*((float)u+.5f);
				} else if (j == 2) {
					ob.bcir.x = scale*((float)u+.5f);
					ob.bcir.y = scale*((float)v+.5f);
					ob.bcir.z = -scale*(float)floor->length-torch.bbox.minz;
				} else if (j == 3) {
					ob.bcir.x = scale*(float)floor->width+torch.bbox.minz;
					ob.bcir.y = scale*((float)v+.5f);
					ob.bcir.z = -scale*(float)floor->length+scale*((float)u+.5f);
				}
				ob.bcir.radius = torch.bcir.radius;
				obList.push_back(ob);
				TorchPos tp = TorchPos();
				tp.wallpos = j; tp.u = u; tp.v = v;
				torchMap.insert(std::pair<TorchPos, int>(tp, obList.size()-1));
				}
				break;
			case BOX:
				if (j == 0) {
					ob.bcir.x = scale*(float)floor->width-scale*((float)u+.5f);
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = box.bbox.minz;
				} else if (j == 1) {
					ob.bcir.x = -box.bbox.minz;
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = -scale*((float)u+.5f);
				} else if (j == 2) {
					ob.bcir.x = scale*((float)u+.5f);
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = -scale*(float)floor->length-box.bbox.minz;
				} else if (j == 3) {
					ob.bcir.x = scale*(float)floor->width+box.bbox.minz;
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = -scale*(float)floor->length+scale*((float)u+.5f);
				}
				ob.bcir.radius = box.bcir.radius;
				obList.push_back(ob);
				break;
			case MOVABLEBOX:
				{
				if (j == 0) {
					ob.bcir.x = scale*(float)floor->width-scale*((float)u+.5f);
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = box.bbox.minz;
				} else if (j == 1) {
					ob.bcir.x = -box.bbox.minz;
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = -scale*((float)u+.5f);
				} else if (j == 2) {
					ob.bcir.x = scale*((float)u+.5f);
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = -scale*(float)floor->length-box.bbox.minz;
				} else if (j == 3) {
					ob.bcir.x = scale*(float)floor->width+box.bbox.minz;
					ob.bcir.y = scale*((float)v+.5f)-scale/2.f-box.bbox.miny;
					ob.bcir.z = -scale*(float)floor->length+scale*((float)u+.5f);
				}
				ob.bcir.radius = box.bcir.radius;
				obList.push_back(ob);
				MovableBoxPos mbpos = MovableBoxPos();
				mbpos.wallpos = j; mbpos.u = u; mbpos.v = v;
				mboxBoundMap.insert(std::pair<MovableBoxPos, int>(mbpos, obList.size()-1));
				}
				break;
			case SPIKES:
				break;
			case PIT:
				break;
			}
		}
	}
}

Floor *Room::getFloor() {
	return this->floor;
}

Wall **Room::getWalls() {
	return this->walls;
}

int Room::getNumTorches() {
	return numTorches;
}

void Room::getObList(std::vector<ObsBound> &o) {
	o.clear();
	for (unsigned int i = 0; i < obList.size(); ++i) {
		ObsBound ob = obList[i];
		o.push_back(ob);
	}
}

STPoint3 Room::getPlayerPosition() {
	return playerStartPos;
}

bool Room::isFree() {
	int uRusko = (int)floorf(-worldPos.x/scale);
	int vRusko = (int)floorf(worldPos.z/scale);

	return (floor->objPos[floor->getIndex(uRusko, vRusko)] == FREE);
}

int Room::isTorch() {
	int xRusko = (int)floorf(-worldPos.x/scale);
	int yRusko = (int)floorf(-worldPos.y/scale);
	int zRusko = (int)floorf(worldPos.z/scale);

	TorchPos tp = TorchPos();
	if (zRusko == 0) {
		if (walls[0]->objPos[walls[0]->getIndex(floor->width-1-xRusko, yRusko)] == TORCH) {
			tp.wallpos = 0; tp.u = floor->width-1-xRusko; tp.v = yRusko;
			return torchMap[tp];
		}
	}
	if (xRusko == 0) {
		if (walls[1]->objPos[walls[1]->getIndex(zRusko, yRusko)] == TORCH) {
			tp.wallpos = 1; tp.u = zRusko; tp.v = yRusko;
			return torchMap[tp];
		}
	}
	if (zRusko == floor->length-1) {
		if (walls[2]->objPos[walls[2]->getIndex(xRusko, yRusko)] == TORCH) {
			tp.wallpos = 2; tp.u = xRusko; tp.v = yRusko;
			return torchMap[tp];
		}
	}
	if (xRusko == floor->width-1) {
		if (walls[3]->objPos[walls[3]->getIndex(floor->length-1-zRusko, yRusko)] == TORCH) {
			tp.wallpos = 3; tp.u = floor->length-1-zRusko; tp.v = yRusko;
			return torchMap[tp];
		}
	}

	return -1;
}

bool Room::isWalkToBox() {
	int xRusko = (int)floorf(-futurePos.x/scale);
	int yRusko = (int)floorf(-futurePos.y/scale);
	int zRusko = (int)floorf(futurePos.z/scale);
	int curxRusko = (int)floorf(-worldPos.x/scale);
	int curyRusko = (int)floorf(-worldPos.y/scale);
	int curzRusko = (int)floorf(worldPos.z/scale);

	if (curzRusko == 1) {
		if (walls[0]->objPos[walls[0]->getIndex(floor->width-1-xRusko, yRusko)] == BOX) {
			return true;
		}
	}
	if (curxRusko == 1) {
		if (walls[1]->objPos[walls[1]->getIndex(zRusko, yRusko)] == BOX) {
			return true;
		}
	}
	if (curzRusko == floor->length-2) {
		if (walls[2]->objPos[walls[2]->getIndex(xRusko, yRusko)] == BOX) {
			return true;
		}
	}
	if (curxRusko == floor->width-2) {
		if (walls[3]->objPos[walls[3]->getIndex(floor->length-1-zRusko, yRusko)] == BOX) {
			return true;
		}
	}

	return false;
}

bool Room::isJumpOnBox() {

}

bool Room::isPit() {
	int uRusko = (int)floorf(-worldPos.x/scale);
	int vRusko = (int)floorf(worldPos.z/scale);

	return (floor->objPos[floor->getIndex(uRusko, vRusko)] == PIT);
}

bool Room::isSpikes() {
	int uRusko = (int)floorf(-worldPos.x/scale);
	int vRusko = (int)floorf(worldPos.z/scale);

	return (floor->objPos[floor->getIndex(uRusko, vRusko)] == SPIKES && worldPos.y >= -1.f);
}

void Room::render() {
	renderLayout();
	renderObjects();
}

void Room::renderLayout() {
	renderPits();

	glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	floorTexture->Bind();
	glBegin(GL_QUADS);
		// floor
		for (int v = 0; v < floor->length; ++v) {
			for (int u = 0; u < floor->width; ++u) {
				if (floor->objPos[floor->getIndex(u, v)] == PIT) continue;
				glTexCoord2f(0,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y+floorHeight[v][u],pos.z-scale*v);
				glTexCoord2f(0,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y+floorHeight[v][u+1],pos.z-scale*v);
				glTexCoord2f(1,1);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*(u+1),pos.y+floorHeight[v+1][u+1],pos.z-scale*(v+1));
				glTexCoord2f(1,0);
				glNormal3f(0,1,0);
				glVertex3f(pos.x+scale*u,pos.y+floorHeight[v+1][u],pos.z-scale*(v+1));
			}
		}
	glEnd();
	floorTexture->UnBind();

	wallTexture->Bind();
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
	wallTexture->UnBind();
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
			case MOVABLEBOX:
				{
				if (j == 0) { glTranslatef(0, -scale/2.f-box.bbox.miny, box.bbox.minz); glRotatef(180.0f, 0, 1, 0); }
				else if (j == 1) { glTranslatef(-box.bbox.minz, -scale/2.f-box.bbox.miny, 0); glRotatef(90.0f, 0, 1, 0); }
				else if (j == 2) { glTranslatef(0, -scale/2.f-box.bbox.miny, -box.bbox.minz); }
				else if (j == 3) { glTranslatef(box.bbox.minz, -scale/2.f-box.bbox.miny, 0); glRotatef(270.0f, 0, 1, 0); }
				MovableBoxPos mbpos = MovableBoxPos();
				mbpos.wallpos = j; mbpos.u = u; mbpos.v = v;
				int ind = mboxMap[mbpos];
				int idx = mboxBoundMap[mbpos];
				if (boxFrames[ind] == 0) obList[idx].bcir.y += mbox[ind].render(boxFrame1);
				else if (boxFrames[ind] == 1) obList[idx].bcir.y += mbox[ind].render(boxFrame2);
				else if (boxFrames[ind] == 2) obList[idx].bcir.y += mbox[ind].render(boxFrame3);
				}
				break;
			case SPIKES:
				spikes.render();
				break;
			case PIT:
				break;
			case SMOKE:
				{
				vector3 pos = vector3(pos.x+scale*floor->width-scale*((float)u+.5f), pos.y+scale*((float)v+.5f), pos.z);
				if (j == 1) { pos = vector3(pos.x, pos.y+scale*((float)v+.5f), pos.z-scale*((float)u+.5f));}
				else if (j == 2) { pos = vector3(pos.x+scale*((float)u+.5f), pos.y+scale*((float)v+.5f), pos.z-scale*floor->length);}
				else if (j == 3) { pos = vector3(pos.x+scale*floor->width, pos.y+scale*((float)v+.5f), pos.z-scale*floor->length+scale*((float)u+.5f));}
				}
			}

			glPopMatrix();
		}
	}
}

void Room::renderPits() {
	// draw pit
	floorTexture->Bind();
	for (int v = 1; v < floor->length-1; ++v) {
		for (int u = 1; u < floor->width-1; ++u) {
			if (floor->objPos[floor->getIndex(u, v)] == PIT) {
				bool pitcenter = true;
				for (int vt = -1; vt <= 1; ++vt) {
					for (int ut = -1; ut <= 1; ++ut) {
						if (floor->objPos[floor->getIndex(u+ut, v+vt)] != PIT) {
							pitcenter = false;
							break;
						}
					}
				}
				if (pitcenter) {
					glBegin(GL_QUADS);
					for (int q = 0; q < 20; ++q) {
						for (int p = 0; p < 3; ++p) {
							glTexCoord2f(0,0);
							glNormal3f(0,0,-1);
							glVertex3f(pos.x+scale*(u-1+p),-q,pos.z-scale*(v-1));
							glTexCoord2f(0,1);
							glNormal3f(0,0,-1);
							glVertex3f(pos.x+scale*(u+p),-q,pos.z-scale*(v-1));
							glTexCoord2f(1,1);
							glNormal3f(0,0,-1);
							glVertex3f(pos.x+scale*(u+p),-q-1,pos.z-scale*(v-1));
							glTexCoord2f(1,0);
							glNormal3f(0,0,-1);
							glVertex3f(pos.x+scale*(u-1+p),-q-1,pos.z-scale*(v-1));
							glTexCoord2f(0,0);
							glNormal3f(-1,0,0);
							glVertex3f(pos.x+scale*(u+2),-q,pos.z-scale*(v-1+p));
							glTexCoord2f(0,1);
							glNormal3f(-1,0,0);
							glVertex3f(pos.x+scale*(u+2),-q,pos.z-scale*(v+p));
							glTexCoord2f(1,1);
							glNormal3f(-1,0,0);
							glVertex3f(pos.x+scale*(u+2),-q-1,pos.z-scale*(v+p));
							glTexCoord2f(1,0);
							glNormal3f(-1,0,0);
							glVertex3f(pos.x+scale*(u+2),-q-1,pos.z-scale*(v-1+p));
							glTexCoord2f(0,0);
							glNormal3f(0,0,1);
							glVertex3f(pos.x+scale*(u+2-p),-q,pos.z-scale*(v+2));
							glTexCoord2f(0,1);
							glNormal3f(0,0,1);
							glVertex3f(pos.x+scale*(u+1-p),-q,pos.z-scale*(v+2));
							glTexCoord2f(1,1);
							glNormal3f(0,0,1);
							glVertex3f(pos.x+scale*(u+1-p),-q-1,pos.z-scale*(v+2));
							glTexCoord2f(1,0);
							glNormal3f(0,0,1);
							glVertex3f(pos.x+scale*(u+2-p),-q-1,pos.z-scale*(v+2));
							glTexCoord2f(0,0);
							glNormal3f(1,0,0);
							glVertex3f(pos.x+scale*(u-1),-q,pos.z-scale*(v+2-p));
							glTexCoord2f(0,1);
							glNormal3f(1,0,0);
							glVertex3f(pos.x+scale*(u-1),-q,pos.z-scale*(v+1-p));
							glTexCoord2f(1,1);
							glNormal3f(1,0,0);
							glVertex3f(pos.x+scale*(u-1),-q-1,pos.z-scale*(v+1-p));
							glTexCoord2f(1,0);
							glNormal3f(1,0,0);
							glVertex3f(pos.x+scale*(u-1),-q-1,pos.z-scale*(v+2-p));
						}
					}
					glEnd();
				}
			}
		}
	}
	floorTexture->UnBind();
}

void Room::generateTorches() {
	if (level == 1) {
		numTorches = 1;
		walls[2]->objPos[walls[2]->getIndex(walls[2]->base/2, 2)] = TORCH;
		return;
	}

	srand(time(NULL));
	numTorches = rand() % 3 + level;
	numHighTorches = numTorches / 5;

	//std::vector<int> wallPos, basePos, heightPos;
	int countHighTorches = 0;
	for (int i = 0; i < numTorches; ++i) {
		// select wall
		int wallpos = rand() % 4;
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
		walls[wallpos]->objPos[walls[wallpos]->getIndex(basepos, heightpos)] = TORCH;
	}
}

void Room::generateObstacles() {
	if (level == 1) {
		floor->objPos[floor->getIndex(floor->width/2, floor->length-1)] = BOX;
		walls[2]->objPos[walls[2]->getIndex(walls[2]->base/2, 0)] = BOX;
		playerStartPos = STPoint3(pos.x+scale*((float)floor->width/2.f+.5f), pos.y, pos.z-scale*((float)floor->length/2.f+.5f));
		return;
	}

	// create boxes
	srand(time(NULL));
	for (int wallpos = 0; wallpos < 4; ++wallpos) {
		std::string objpos = walls[wallpos]->objPos;
		for (unsigned int i = 0; i < objpos.length(); ++i) {
			if (objpos[i] != TORCH) continue;
			int v = i / walls[wallpos]->base;
			int u = i - v*walls[wallpos]->base;

			int boxInd = -1;
			if (v > 1) walls[wallpos]->objPos[walls[wallpos]->getIndex(u, v-2)] = BOX;
			if (v <= 2) {
				if (wallpos == 0) boxInd = floor->getIndex(floor->width-1-u, 0);
				else if (wallpos == 1) boxInd = floor->getIndex(0, u);
				else if (wallpos == 2) boxInd = floor->getIndex(u, floor->length-1);
				else if (wallpos == 3) boxInd = floor->getIndex(floor->width-1, floor->length-1-u);
				floor->objPos[boxInd] = BOX;
				boxIndices.push_back(boxInd);
				continue;
			}

			bool prevTorch = false, nextTorch = false;
			bool prevBox = false, nextBox = false;
			int prevwallpos = (wallpos == 0) ? 3 : wallpos-1;
			int nextwallpos = (wallpos == 3) ? 0 : wallpos+1;
			int prevu = walls[prevwallpos]->base-2;
			int nextu = 1;
			if (u > 0) { prevwallpos = wallpos; prevu = u-1; }
			if (u < walls[wallpos]->base-1) { nextwallpos = wallpos; nextu = u+1; }
			for (int j = 0; j < walls[prevwallpos]->height; ++j) {
				if (walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, j)] == TORCH)
					prevTorch = true;
				if (walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, j)] == BOX || walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, j)] == MOVABLEBOX)
					prevBox = true;
				if (prevTorch && prevBox) break;
			}
			for (int j = 0; j < walls[nextwallpos]->height; ++j) {
				if (walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, j)] == TORCH)
					nextTorch = true;
				if (walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, j)] == BOX || walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, j)] == MOVABLEBOX)
					nextBox = true;
				if (nextTorch && nextBox) break;
			}

			if (prevTorch && nextTorch) {
				walls[wallpos]->objPos[walls[wallpos]->getIndex(u, v-2)] = FREE;
				walls[wallpos]->objPos[walls[wallpos]->getIndex(u, 0)] = MOVABLEBOX;
				Box mb = Box(boxScale*scale);
				mb.setMove(scale*(float)(v-2));
				mbox.push_back(mb);
				boxFrames.push_back(rand() % 3);
				MovableBoxPos mbpos = MovableBoxPos();
				mbpos.wallpos = wallpos; mbpos.u = u; mbpos.v = 0;
				mboxMap.insert(std::pair<MovableBoxPos, int>(mbpos, mbox.size()-1));
				if (wallpos == 0) boxInd = floor->getIndex(floor->width-1-u, 0);
				else if (wallpos == 1) boxInd = floor->getIndex(0, u);
				else if (wallpos == 2) boxInd = floor->getIndex(u, floor->length-1);
				else if (wallpos == 3) boxInd = floor->getIndex(floor->width-1, floor->length-1-u);
				floor->objPos[boxInd] = BOX;
				boxIndices.push_back(boxInd);
				continue;
			}
			if (prevTorch && !nextTorch) {
				int newheight = min(rand() % 5 + v - 3, walls[nextwallpos]->height-1);
				walls[nextwallpos]->objPos[walls[nextwallpos]->getIndex(nextu, 0)] = MOVABLEBOX;
				Box mb = Box(boxScale*scale);
				mb.setMove(scale*(float)newheight);
				mbox.push_back(mb);
				boxFrames.push_back(rand() % 3);
				MovableBoxPos mbpos = MovableBoxPos();
				mbpos.wallpos = wallpos; mbpos.u = nextu; mbpos.v = 0;
				mboxMap.insert(std::pair<MovableBoxPos, int>(mbpos, mbox.size()-1));
				if (nextwallpos == 0) boxInd = floor->getIndex(floor->width-1-nextu, 0);
				else if (nextwallpos == 1) boxInd = floor->getIndex(0, nextu);
				else if (nextwallpos == 2) boxInd = floor->getIndex(nextu, floor->length-1);
				else if (nextwallpos == 3) boxInd = floor->getIndex(floor->width-1, floor->length-1-nextu);
				floor->objPos[boxInd] = BOX;
				boxIndices.push_back(boxInd);
				continue;
			}
			if (!prevTorch && nextTorch) {
				int newheight = min(rand() % 5 + v - 3, walls[prevwallpos]->height-1);
				walls[prevwallpos]->objPos[walls[prevwallpos]->getIndex(prevu, 0)] = MOVABLEBOX;
				Box mb = Box(boxScale*scale);
				mb.setMove(scale*(float)newheight);
				mbox.push_back(mb);
				boxFrames.push_back(rand() % 3);
				MovableBoxPos mbpos = MovableBoxPos();
				mbpos.wallpos = wallpos; mbpos.u = prevu; mbpos.v = 0;
				mboxMap.insert(std::pair<MovableBoxPos, int>(mbpos, mbox.size()-1));
				if (prevwallpos == 0) boxInd = floor->getIndex(floor->width-1-prevu, 0);
				else if (prevwallpos == 1) boxInd = floor->getIndex(0, prevu);
				else if (prevwallpos == 2) boxInd = floor->getIndex(prevu, floor->length-1);
				else if (prevwallpos == 3) boxInd = floor->getIndex(floor->width-1, floor->length-1-prevu);
				floor->objPos[boxInd] = BOX;
				boxIndices.push_back(boxInd);
				continue;
			}
			if (!prevTorch && !nextTorch) {
				int pickside = rand() % 2;
				int newwallpos = 0;
				int newu = 0;
				if (pickside == 0) { newwallpos = prevwallpos; newu = prevu; }
				else { newwallpos = nextwallpos; newu = nextu; }
				int newheight = min(rand() % 5 + v - 3, walls[prevwallpos]->height-1);
				walls[newwallpos]->objPos[walls[newwallpos]->getIndex(newu, 0)] = MOVABLEBOX;
				Box mb = Box(boxScale*scale);
				mb.setMove(scale*(float)newheight);
				mbox.push_back(mb);
				boxFrames.push_back(rand() % 3);
				MovableBoxPos mbpos = MovableBoxPos();
				mbpos.wallpos = wallpos; mbpos.u = newu; mbpos.v = 0;
				mboxMap.insert(std::pair<MovableBoxPos, int>(mbpos, mbox.size()-1));
				if (newwallpos == 0) boxInd = floor->getIndex(floor->width-1-newu, 0);
				else if (newwallpos == 1) boxInd = floor->getIndex(0, newu);
				else if (newwallpos == 2) boxInd = floor->getIndex(newu, floor->length-1);
				else if (newwallpos == 3) boxInd = floor->getIndex(floor->width-1, floor->length-1-newu);
				floor->objPos[boxInd] = BOX;
				boxIndices.push_back(boxInd);
				continue;
			}
		}
	}

	// create spikes along the rims (2/3)
	int numSpikes = 0;
	for (int i = 0; i < floor->width; ++i) {
		if (floor->objPos[floor->getIndex(i, 0)] == FREE)
			if (rand() % 3 != 0) { floor->objPos[floor->getIndex(i, 0)] = SPIKES; numSpikes++; }
		if (floor->objPos[floor->getIndex(i, floor->length-1)] == FREE)
			if (rand() % 3 != 0) { floor->objPos[floor->getIndex(i, floor->length-1)] = SPIKES; numSpikes++; }
	}
	for (int j = 0; j < floor->length; ++j) {
		if (floor->objPos[floor->getIndex(0, j)] == FREE)
			if (rand() % 3 != 0) { floor->objPos[floor->getIndex(0, j)] = SPIKES; numSpikes++; }
		if (floor->objPos[floor->getIndex(floor->width-1, j)] == FREE)
			if (rand() % 3 != 0) { floor->objPos[floor->getIndex(floor->width-1, j)] = SPIKES; numSpikes++; }
	}

	// find safe paths to ensure to game can be beaten
	int uPlayerStart = rand() % 4 + (floor->width/2) - 2;
	int vPlayerStart = rand() % 4 + (floor->length/2) - 2;
	int playerStartInd = floor->getIndex(uPlayerStart, vPlayerStart);
	playerStartPos = STPoint3(pos.x+scale*((float)uPlayerStart+.5f), pos.y, pos.z-scale*((float)vPlayerStart+.5f));
	floor->objPos[playerStartInd] = SAFE;
	safeIndices.push_back(playerStartInd);
	for (unsigned int i = 0; i < boxIndices.size(); ++i) {
		int startInd = (i == 0) ? playerStartInd : safeIndices[rand() % safeIndices.size()];
		int endInd = boxIndices[i];

		int vStart = startInd/floor->width, uStart = startInd-vStart*floor->width;
		int vEnd = endInd/floor->width, uEnd = endInd-vEnd*floor->width;
		int uCur = uStart, vCur = vStart;

		int stepX = uEnd - uStart, stepZ = vEnd - vStart;
		int incX = (stepX >= 0) ? 1 : -1, incZ = (stepZ >= 0) ? 1 : -1;

		int safeInd = -1;
		while (abs(stepX) > 0 || abs(stepZ) > 0) {
			if ((uCur+incX == uEnd && vCur == vEnd) || (uCur == uEnd && vCur+incZ == vEnd))
				break;
			if (stepX == 0 || uCur+incX <= 0 || uCur+incX >= floor->width-1) {
				vCur += incZ;
				stepZ -= incZ;
			} else if (stepZ == 0 || vCur+incZ <= 0 || vCur+incZ >= floor->length-1) {
				uCur += incX;
				stepX -= incX;
			} else {
				if (rand() % 2 == 0) {
					uCur += incX;
					stepX -= incX;
				} else {
					vCur += incZ;
					stepZ -= incZ;
				}
			}
			safeInd = floor->getIndex(uCur, vCur);
			if (floor->objPos[safeInd] == FREE) {
				floor->objPos[safeInd] = SAFE;
				safeIndices.push_back(safeInd);
			}
		}
	}

	// Create pits
	srand(time(NULL));
	int numPits = min(numTorches / 3, 7);
	int countPits = 0;
	int numTry = 0;
	while (countPits < numPits && numTry < 15) {
		int u = rand() % (floor->width-2) + 1;
		int v = rand() % (floor->length-2) + 1;
		bool pitOkay = true;
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (floor->objPos[floor->getIndex(u+i, v+j)] != FREE)
					pitOkay = false;
			}
		}
		if (pitOkay) {
			for (int i = -1; i <= 1; ++i) {
				for (int j = -1; j <= 1; ++j) {
					floor->objPos[floor->getIndex(u+i, v+j)] = PIT;
				}
			}
			countPits++;
		} else {
			numTry++;
		}
	}

	int obsThreshold = (int)floorf((.2f + .03f*(float)level) * (floor->width*floor->length));
	int numSafe = boxIndices.size() + safeIndices.size();
	int numDanger = 9*countPits + numSpikes;
	int numAdd = (int)floorf(.03f*floor->width*floor->length);
	std::vector<int> freeIndices;
	for (unsigned int i = 0; i < floor->objPos.length(); ++i) {
		if (floor->objPos[i] == FREE) freeIndices.push_back(i);
	}
	while (freeIndices.size() > 0 && numDanger < obsThreshold) {
		for (int i = 0; i < numAdd; ++i) {
			int ind = rand() % freeIndices.size();
			floor->objPos[freeIndices[ind]] = SPIKES;
			numSpikes++;
			numDanger++;
			freeIndices.erase(freeIndices.begin()+ind);
			if (freeIndices.size() == 0) break;
		}
	}

	// create smoke
	srand(time(NULL));
	for (int j = 0; j < 4; ++j) {
		int basepos = rand() % walls[j]->base;
		while (walls[j]->objPos[walls[j]->getIndex(basepos, 1)] != FREE)
			basepos = rand() % walls[j]->base;
		walls[j]->objPos[walls[j]->getIndex(basepos, 1)] = SMOKE;
		if (j == 0) { vector3 pos = vector3(playerStartPos.x+scale*floor->width-scale*((float)basepos+.5f), groundPos-.5f, playerStartPos.z); }
		else if (j == 1) { vector3 pos = vector3(playerStartPos.x, groundPos-.5f, playerStartPos.z-scale*((float)basepos+.5f)); t1->resetPos(pos); }
		else if (j == 2) { vector3 pos = vector3(playerStartPos.x+scale*((float)basepos+.5f), groundPos-.5f, playerStartPos.z-scale*floor->length); }
		else if (j == 3) { vector3 pos = vector3(playerStartPos.x+scale*floor->width, groundPos-.5f, playerStartPos.z-scale*floor->length+scale*((float)basepos+.5f)); t3->resetPos(pos); }
		if (j == 0) {}
		else if (j == 1) { particles->addEmitter(t1); }
		else if (j == 2) {}
		else if (j == 3) { particles->addEmitter(t3); }
	}
}