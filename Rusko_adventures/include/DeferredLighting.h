#ifndef _DEFERREDLIGHTING_H
#define _DEFERREDLIGHTING_H

#include "stglew.h"
//#include <glew.h>
//#include <glut.h>
#include <string>
#include "Shader.h"

using namespace std;

class DeferredLighting
{
public:
	DeferredLighting(int p_width, int p_height);
	~DeferredLighting(void);

	/**
	 * Initialization function that must be called after all GL, GLUT, and GLEW
	 * setup, but before use of other library functions.
	 */
	void Init(const string shaderPath);

	/**
	 * Call to bind FBO, attach the gather shader, and perform other setup before draw calls.
	 */
	void PreDrawScene();

	/**
	 * Call to unbind FBO, detach the gather shader, and perform other breakdown after draw calls.
	 */
	void PostDrawScene();

	void SetMaterialTexture(int texture, bool useTexture);

	/**
	 * Draw the directional and ambient lighting.
	 */
	void DrawDirectionalAndAmbient(int screenWidth, int screenHeight);
	void SetAmbLightColor(float r, float g, float b);
	void SetDirLightColor(float r, float g, float b);
	void SetDirLightDirection(float x, float y, float z);

	/**
	 * Draw the point lighting.
	 */
	void PreDrawPointLights(int screenWidth, int screenHeight, int zNear, int zFar);
	void SetPointLightColor(float r, float g, float b);
	void SetPointLightPosition(float x, float y, float z);
	void SetPointAttenuation(float constant, float linear, float quadratic);
	void SetRadius(float r);
	void PostDrawPointLights();

	/**
	 * Draws the normal buffer.
	 */
	void DrawNormals(int screenWidth, int screenHeight);

	/**
	 * Draws the color buffer.
	 */
	void DrawColors(int screenWidth, int screenHeight);

	/**
	 * Draws the depth buffer.
	 */
	void DrawDepth(int screenWidth, int screenHeight, float zNear, float zFar);


private:
	//---------------------------------------------------------------------------
	// UTILITY FUNCTIONS
	//---------------------------------------------------------------------------
	void InitDepthTexture();
	void CheckExtensions();
	void InitRenderTargetTexture(const char* name, GLuint* texture, GLenum attachment);
	void InitShaders(const string shaderPath);
	void DrawFullScreenQuad(int screenWidth, int screenHeight);
	void DrawDirectTarget(GLuint bufferToDraw, int screenWidth, int screenHeight, float zNear=0.0, float zFar=0.0);

	//---------------------------------------------------------------------------
	// VARIABLES
	//---------------------------------------------------------------------------
	float ambLightColor[3];
	float dirLightColor[3];
	float dirLightDir[3];
	float pntLightColor[3];
	float pntLightPos[3];
	float pntAttVals[3];						// Attenuation: 0 = constant, 1 = linear, 3 = quadratic
	float pntRadius;
	enum   MRT{NORMALS, COLORS, NUM_MRTS};		// NORMALS = 0 (texture for Normals); COLORS = 1 (texture for Color)
	GLuint textures[NUM_MRTS];					// From above, NUM_MRTS = 2
	GLuint fbo;
	GLuint  depthtexture;						// Texture for Depth Buffer
	int  width, height;							// Buffer size
	Shader* dirAmbLightShader;					// GLSL program for Directional & Ambient Light
	Shader* pointLightShader;					// GLSL program for Point Light
	Shader* directTargetShader;					// GLSL program for Final Rendering
	Shader* gatherShader;						// GLSL program for Buffers Build
	static const string GATHER_VERT_SHADER;
	static const string GATHER_FRAG_SHADER;
	static const string DIR_TARGET_FRAG_SHADER;
	static const string DIR_AMB_LIGHT_FRAG_SHADER;
	static const string POINT_LIGHT_VERT_SHADER;
	static const string POINT_LIGHT_FRAG_SHADER;
};

#endif //_DEFERREDLIGHTING_H

