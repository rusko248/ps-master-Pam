#ifndef _POINTLIGHT_H
#define _POINTLIGHT_H

#include "stglew.h"
//#include <glew.h>
//#include <glut.h>
#include <string>
#include "Shader.h"
#include "DeferredLighting.h"

using namespace std;

class PointLight
{
public:
	PointLight(void);
	~PointLight(void);

	/**
	 * Set the point lighting.
	 */
	void SetPosition(float x, float y, float z);
	void SetColor(float r, float g, float b);
	void SetAttenuation(float constant, float linear, float quadratic);
	void SetRadius(float r);
	void SetGrain(int g);

	/**
	 * Render the light.
	 */
	void RenderPointLight(DeferredLighting *dfe);

private:
	//---------------------------------------------------------------------------
	// UTILITY FUNCTIONS
	//---------------------------------------------------------------------------

	

	//---------------------------------------------------------------------------
	// VARIABLES
	//---------------------------------------------------------------------------

	float radius;				// the radius of the the light
	int grain;					// how fine the sphere of influence is
	float lightColor[3];		// color of the light
	float lightPosition[3];		// position of the light
	float attVals[3];			// Attenuation: 0 = constant, 1 = linear, 3 = quadratic
};

#endif //_POINTLIGHT_H

