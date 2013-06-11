#ifndef __ROOM_H
#define __ROOM_H

#include "Framework.h"
#include "Renderable.h"
#include "Torch.h"
#include "Box.h"
#include "Spikes.h"
#include "ParticleManager.h"
#include <map>

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

struct TorchPos {
	TorchPos() {
		wallpos = u = v = 0;
	}
	
	int wallpos, u, v;
};

struct TorchPosCompare {
	bool operator() (const TorchPos& a, const TorchPos& b) {
		if (a.wallpos < b.wallpos) return true;
		else if (a.wallpos > b.wallpos) return false;
		else {
			if (a.u < b.u) return true;
			else if (a.u > b.u) return false;
			else return (a.v < b.v);
		}
	}
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
	int getNumTorches();
	void getObList(std::vector<ObsBound> &o);
	STPoint3 getPlayerPosition();
	bool isFree();
	int isTorch();
	bool isPit();
	bool isSpikes();
    bool isWalkToBox();
    
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
	void updateOB();

	Wall *walls[4]; // near, left, far, right
	Floor *floor;
	int numTorches, numHighTorches;
	std::vector<ObsBound> obList;
	std::map<TorchPos, int, TorchPosCompare> torchMap;
	std::vector<int> boxIndices;
	std::vector<int> safeIndices;
	STPoint3 playerStartPos;

};

#endif