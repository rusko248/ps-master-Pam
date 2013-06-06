#ifndef __ROOM_H
#define __ROOM_H

#include "Framework.h"
#include "Renderable.h"
#include "Torch.h"
#include "Box.h"
#include "Spikes.h"

#define FREE '0'
#define TORCH '1'
#define BOX '2'
#define SPIKES '3'
#define PIT '4'
#define SMOKE '5'
#define SAFE '9'

// walls and floors are grids
struct Wall {
	int base, height;
	float fbase, fheight;
	std::string objPos;

	int getIndex(int u, int v) {
		assert(u >= 0 && u < base);
		assert(v >= 0 && v < height);
		return u + base*v;
	}
};

struct Floor {
	int width, length;
	float fwidth, flength;
	std::string objPos;

	int getIndex(int u, int v) {
		assert(u >= 0 && u < width);
		assert(v >= 0 && v < length);
		return u + width*v;
	}
};

struct ObsBound {
	ObsBound() {
		type = '0';
		bcir = BCir();
	}

	ObsBound& operator=(const ObsBound& o) {
		this->type = o.type;
		this->bcir = o.bcir;
        return *this;
	};

	char type;
	BCir bcir;
};

class Room : public Renderable
{
public:
	Room();
	Room(int w, int h, int l, float s);
	~Room();
	
	void setLevel(int lv);
	Floor *getFloor();
	Wall **getWalls();
	void getObList(std::vector<ObsBound> &o);
	void render();

	int dim[3];
	float scale;
	STPoint3 pos; // bottom left corner
	int level;

private:
	void renderLayout();
	void renderObjects();
	void renderPits();
	void generateTorches();
	void generateObstacles();
	void initRoom();
	void updateBCir();

	Wall *walls[4]; // near, left, far, right
	Floor *floor;
	std::vector<ObsBound> obList;

};

#endif