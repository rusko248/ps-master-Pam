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
	Model(const std::string &path, float scale);
	virtual ~Model();

	void render();

	BBox bbox;

private:
	void fitSphere(float scale);
	BBox findBBox();

	Mesh mesh;

};

#endif