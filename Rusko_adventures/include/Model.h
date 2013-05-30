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

	void addMesh(const std::string &path);
	virtual void render();
	void renderModel();

private:
	void fitSphereAll();
	void fitSphere(unsigned int i);
	std::vector<Mesh> meshes;

};


#endif