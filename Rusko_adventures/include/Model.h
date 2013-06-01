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
	Model(const std::string &path, STPoint3 centerMass, float maxLength); //flag to use fitSphere with offset

	virtual ~Model();

	void render();
    STPoint3 getCenterPoint();
    
    STPoint3 getCenterMass();
    float getMaxLength();

	BBox bbox;

private:
	void fitSphere(float scale);
    void fitSphere_withOffset(float scale, STPoint3 centerMass, float maxLength);

	BBox findBBox();

    STPoint3 centerPoint;
    
    STPoint3 centerMass;
    float scaleLength;
    
	Mesh mesh;

};

#endif