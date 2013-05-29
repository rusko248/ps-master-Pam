#ifndef __TORCH_H
#define __TORCH_H

#include "Framework.h"
#include "Renderable.h"
#include "Model.h"

class Torch : public Model
{
public:
	Torch();
	~Torch();
	
	void render();

private:
	Model *model;
	Texture texture;

};

#endif