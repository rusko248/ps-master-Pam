#include "PointLight.h"


PointLight::PointLight(void)
{
	lightPosition[0] = 0.0f;
	lightPosition[1] = 0.0f;
	lightPosition[2] = 0.0f;
	lightColor[0] = 0.0f;
	lightColor[1] = 0.0f;
	lightColor[2] = 0.0f;
	attVals[0] = 1.0f;
	attVals[1] = 0.0f;
	attVals[2] = 0.0f;
	radius = 0.0f;
	grain = 20;
}


PointLight::~PointLight(void)
{
}

void
PointLight::SetPosition(float x, float y, float z)
{
	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;
}

void
PointLight::SetColor(float r, float g, float b)
{
	lightColor[0] = r;
	lightColor[1] = g;
	lightColor[2] = b;
}

void
PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	attVals[0] = constant;
	attVals[1] = linear;
	attVals[2] = quadratic;
}

void
PointLight::SetRadius(float r)
{
	radius = r;
}

void
PointLight::SetGrain(int g)
{
	grain = g;
}

void
PointLight::RenderPointLight(DeferredLighting *dfe)
{
	dfe->SetPointLightPosition(lightPosition[0], lightPosition[1], lightPosition[2]);
	dfe->SetPointLightColor(lightColor[0], lightColor[1], lightColor[2]);
	dfe->SetPointAttenuation(attVals[0], attVals[1], attVals[2]);
	glPushMatrix();
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	glutSolidSphere(radius, grain, grain);
	glPopMatrix();
}


