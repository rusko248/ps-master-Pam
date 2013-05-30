#ifndef __MODEL_H
#define __MODEL_H
#include "Framework.h"
#include "Renderable.h"

// include OpenMesh
#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include "Mesh_definitions.h"

// The model class

class Model : Renderable
{
public:
	Model();
	Model(const std::string &path);
	virtual ~Model();

	void render();
	void scale(float s);

	BBox bbox;

private:
	void fitSphere();
	BBox findBBox();

	Mesh mesh;

};

#endif