#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <windows.h>
#include "st.h"
#include <vector>

using namespace std;

// --------------------------------------------------------------------------
// Structure to contain the values for materials in a mesh.  The values are
// are those from the Wavefront .MTL specifications, as follows:
//    name       = the name specified for the material to be used for lookup
//    Ka         = ambient color rgb values
//    Kd         = diffuse color rgb values
//    Ks         = specular color rgb values
//    Ke         = emmissive color rgb values
//    illum      = illumination model (e.g. 2 = highlight on)
//    Ns         = specular exponent (0 - 1000)
//    Ni         = index of refraction (0.001 - 10)
//                 1.0 = no bending of light passing through
//                 1.5 = typical glass value
//                 increase value for more refraction (less than 1 not
//                 recommended)
//    d          = dissolve value (0.0 (transparent) - 1.0 (opaque)).  Used
//                 as the alpha component for OpenGL color values.
//    Tf         = transmission filter rgb values ( amount of each component
//                 allowed to pass through the material)
//    Tr         = not found in the MTL specification
//    hasTexture = true is a texture has been specified; false, otherwise
//    texture    = the OpenGL texture map index containing the texture map
// --------------------------------------------------------------------------

struct Material
{
	string name;
    STColor3f Ka;
    STColor3f Kd;
    STColor3f Ks;
    STColor3f Ke;
	int illum;
	float Ns;
	float Ni;
	float d;
	float Tr;
    STColor3f Tf;
	bool hasTexture;
//	unsigned int texture;
	STTexture* texture;

    Material(string p_name) {
		name = p_name;
		Ka = STColor3f(0.0f, 0.0f, 0.0f);
		Kd = STColor3f(0.0f, 0.0f, 0.0f);
		Ks = STColor3f(0.0f, 0.0f, 0.0f);
		Ke = STColor3f(0.0f, 0.0f, 0.0f);
		illum = 0;
		Ns = 0.0f;
		Ni = 0.0f;
		d = 0.0f;
		Tr = 0.0f;
		Tf = STColor3f(0.0f, 0.0f, 0.0f);
		hasTexture = false;
//		texture = 0;
		texture = NULL;
	}

	void SetKa(const STColor3f p_Ka) { Ka = p_Ka; }
	void SetKd(const STColor3f p_Kd) { Kd = p_Kd; }
	void SetKs(const STColor3f p_Ks) { Ks = p_Ks; }
	void SetKe(const STColor3f p_Ke) { Ke = p_Ke; }
	void SetTf(const STColor3f p_Tf) { Tf = p_Tf; }
};

#endif //_MATERIAL_H
