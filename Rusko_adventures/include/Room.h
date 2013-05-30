#ifndef __ROOM_H
#define __ROOM_H

#include "Framework.h"
#include "Renderable.h"
#include "Torch.h"
#include "Box.h"
#include "Spikes.h"

// walls and floors are grids
struct Wall {
	int base, height;
	std::string objPos;

	int getIndex(int u, int v) {
		assert(u >= 0 && u < base);
		assert(v >= 0 && v < height);
		return u + base*v;
	}
};

struct Floor {
	int width, length;
	std::string objPos;

	int getIndex(int u, int v) {
		assert(u >= 0 && u < width);
		assert(v >= 0 && v < length);
		return u + length*v;
	}
};

class Room : public Renderable
{
public:
	Room();
	Room(int w, int h, int l, float s);
	
	void setLevel(int lv);
	void render();

	int dim[3];
	float scale;
	STPoint3 pos; // bottom left corner
	int level;

private:
	void renderLayout();
	void renderObstacles();
	void generateObstacles();
	void initRoom();

	Wall *walls[4]; // near, left, far, right
	Floor *floor;

};

#endif