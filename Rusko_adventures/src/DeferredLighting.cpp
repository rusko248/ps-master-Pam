#include "DeferredLighting.h"

//Some constants
const string DeferredLighting::GATHER_VERT_SHADER = "/deferred_gather.vert";
const string DeferredLighting::GATHER_FRAG_SHADER = "/deferred_gather.frag";
const string DeferredLighting::DIR_TARGET_FRAG_SHADER = "/deferred_direct_target.frag";
const string DeferredLighting::DIR_AMB_LIGHT_FRAG_SHADER = "/dLight.frag";
const string DeferredLighting::POINT_LIGHT_VERT_SHADER = "/pLight.vert";
const string DeferredLighting::POINT_LIGHT_FRAG_SHADER = "/pLight.frag";

DeferredLighting::DeferredLighting(int p_width, int p_height)
{
	width = p_width;
	height = p_height;
	gatherShader = NULL;
	pointLightShader = NULL;
	dirAmbLightShader = NULL;
	directTargetShader = NULL;

	CheckExtensions();
}

DeferredLighting::~DeferredLighting(void)
{
}

void
DeferredLighting::Init(const string shaderPath)
{
	printf("\n***DeferredLighting INITIALIZATION***\n\n");
	// FBO
	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	//Depth
	glActiveTexture(GL_TEXTURE0);
	InitDepthTexture();
	// Normals texture		Gather Shader will reference gl_FragData[0]
	InitRenderTargetTexture("Normal Map", &textures[NORMALS], GL_COLOR_ATTACHMENT0_EXT);
	// Colors texture		Gather Shader will reference gl_FragData[1]
	InitRenderTargetTexture("Color Map", &textures[COLORS], GL_COLOR_ATTACHMENT1_EXT);

	// Set targets to draw buffers
	GLenum attachmentList[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT };
	glDrawBuffers(2, attachmentList);		// 2 because only normals and color attachments

	// Status Check
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (status!= GL_FRAMEBUFFER_COMPLETE_EXT) {
		printf("Framebuffer loading error...\n");
		exit(-1);
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind FBO for now

   //Shaders
   printf("\n");
   InitShaders(shaderPath);

   printf("\n***DeferredLighting INIT COMPLETED***\n");
}

void
DeferredLighting::PreDrawScene()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Must have this after switching to the FBO!
	gatherShader->attach();
}

void
DeferredLighting::PostDrawScene()
{
	gatherShader->detach();
	glPopAttrib();			// Reset GL_VIEWPORT_BIT
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void
DeferredLighting::SetMaterialTexture(int texture, bool useTexture)
{
	GLint loc = glGetUniformLocation(gatherShader->shaderProg, "texture");
	glUniform1i(loc, texture);
	loc = glGetUniformLocation(gatherShader->shaderProg, "useTexture");
	if (useTexture)	glUniform1i(loc, 1);
	else			glUniform1i(loc, 0);
}

void
DeferredLighting::DrawDirectionalAndAmbient(int screenWidth, int screenHeight)
{
	dirAmbLightShader->attach();
	//Set shader uniforms
	GLint loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "normals");		// Get uniform sampler location
	glActiveTexture(GL_TEXTURE0);													// Bind to unit
	glBindTexture(GL_TEXTURE_2D, textures[NORMALS]);								//  normals texture 0
	glUniform1i(loc, 0);															// Pass 0 to denote texture unit 0

	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "depths");				// Get uniform sampler location
	glActiveTexture(GL_TEXTURE1);													// Bind to unit
	glBindTexture(GL_TEXTURE_2D, depthtexture);										//  depths texture 1
	glUniform1i(loc, 1);															// Pass 1 to denote texture unit 1

	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "colors");			// Get uniform sampler location
	glActiveTexture(GL_TEXTURE2);													// Bind to unit
	glBindTexture(GL_TEXTURE_2D, textures[COLORS]);									//  colors texture 2
	glUniform1i(loc, 2);															// Pass 2 to denote texture unit 2

	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "screenWidth");
	glUniform1i(loc, screenWidth);

	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "screenHeight");
	glUniform1i(loc, screenHeight);

//	float lightDir[3] = {-2.0f, 2.0f, 6.0f};
	float lightDir[3] = {2.0f, -2.0f, 6.0f};
	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "lightDirection");
	glUniform3fv(loc, 1, lightDir);

	float lightColor[3] = {0.0f, 0.0f, 0.0f};
//	float lightColor[3] = {0.1f, 0.1f, 0.1f};
//	float lightColor[3] = {1.0f, 1.0f, 1.0f};
	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "diffuseLightColor");
	glUniform3fv(loc, 1, lightColor);

	float ambientColor[3] = {0.1, 0.1, 0.1};
//	float ambientColor[3] = {0.01, 0.01, 0.01};
//	float ambientColor[3] = {0.0, 0.0, 0.0};
	loc = glGetUniformLocation(dirAmbLightShader->shaderProg, "ambientLightColor");
	glUniform3fv(loc, 1, ambientColor);

	// draw
	DrawFullScreenQuad(screenWidth, screenHeight);

	//breakdown
	dirAmbLightShader->detach();
}

void
DeferredLighting::PreDrawPointLights(int screenWidth, int screenHeight, int zNear, int zFar)
{
	pointLightShader->attach();
	// Set shader uniforms
	GLint loc = glGetUniformLocation(pointLightShader->shaderProg, "normals");	// Get uniform sampler location
	glActiveTexture(GL_TEXTURE0);												// Bind to unit
	glBindTexture(GL_TEXTURE_2D, textures[NORMALS]);							//  normals texture 0
	glUniform1i(loc, 0);														// Pass 0 to denote texture unit 0

	loc = glGetUniformLocation(pointLightShader->shaderProg, "depths");			// Get uniform sampler location
	glActiveTexture(GL_TEXTURE1);												// Bind to unit
	glBindTexture(GL_TEXTURE_2D, depthtexture);									//  depths texture 1
	glUniform1i(loc, 1);														// Pass 1 to denote texture unit 1

	loc = glGetUniformLocation(pointLightShader->shaderProg, "colors");			// Get uniform sampler location
	glActiveTexture(GL_TEXTURE2);												// Bind to unit
	glBindTexture(GL_TEXTURE_2D, textures[COLORS]);								//  colors texture 2
	glUniform1i(loc, 2);														// Pass 2 to denote texture unit 2

	loc = glGetUniformLocation(pointLightShader->shaderProg, "screenWidth");
	glUniform1i(loc, screenWidth);

	loc = glGetUniformLocation(pointLightShader->shaderProg, "screenHeight");
	glUniform1i(loc, screenHeight);

	loc = glGetUniformLocation(pointLightShader->shaderProg, "near");
	glUniform1f(loc, zNear);

	loc = glGetUniformLocation(pointLightShader->shaderProg, "far");
	glUniform1f(loc, zFar);

	loc = glGetUniformLocation(pointLightShader->shaderProg, "radius");
	glUniform1f(loc, 10.0f);

	loc = glGetUniformLocation(pointLightShader->shaderProg, "diffuseLightColor");
	glUniform3fv(loc, 1, lightColor);

	// Setup required OpenGL state
	glFrontFace(GL_CW);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
}

void
DeferredLighting::SetPointLightColor(float r, float g, float b)
{
	lightColor[0] = r;
	lightColor[1] = g;
	lightColor[2] = b;
	GLint loc = glGetUniformLocation(pointLightShader->shaderProg, "diffuseLightColor");
	glUniform3fv(loc, 1, lightColor);
//	float testlight[3];
//	glGetUniformfv(pointLightShader->shaderProg, loc, testlight);
//	printf("testlight = ( %f, %f, %f )\n", testlight[0], testlight[1], testlight[2]);
}

void
DeferredLighting::SetPointLightPosition(float x, float y, float z)
{
	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;
	GLint loc = glGetUniformLocation(pointLightShader->shaderProg, "LightPosition");
	glUniform3fv(loc, 1, lightPosition);
}

void
DeferredLighting::SetPointAttenuation(float constant, float linear, float quadratic)
{
	attVals[0] = constant;
	attVals[1] = linear;
	attVals[2] = quadratic;
	GLint loc = glGetUniformLocation(pointLightShader->shaderProg, "LightAttenuation");
	glUniform3fv(loc, 1, attVals);
}

void
DeferredLighting::SetRadius(float r) {
   GLint loc = glGetUniformLocation(pointLightShader->shaderProg, "radius");
   glUniform1f(loc, r);
}

void
DeferredLighting::PostDrawPointLights()
{
	//return the OpenGL state back to a "normal" state.
	//TODO: record what these settings were and restore them to their previous values so I don't clobber other people's stuff.
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	pointLightShader->detach();
}

void
DeferredLighting::DrawNormals(int screenWidth, int screenHeight)
{
	DrawDirectTarget(textures[NORMALS], screenWidth, screenHeight);
}

void 
DeferredLighting::DrawColors(int screenWidth, int screenHeight)
{
	DrawDirectTarget(textures[COLORS], screenWidth, screenHeight);
}

void
DeferredLighting::DrawDepth(int screenWidth, int screenHeight, float zNear, float zFar)
{
	DrawDirectTarget(depthtexture, screenWidth, screenHeight, zNear, zFar);
}

/**
 * Initialize the texture to be used for the Depth Buffer
 */
void
DeferredLighting::InitDepthTexture() {
	printf("\tDepth Map activating...");
	glGenTextures(1, &depthtexture);
	glBindTexture(GL_TEXTURE_2D, depthtexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthtexture, 0);
	printf("DONE\n");
}

void
DeferredLighting::InitRenderTargetTexture(const char* name, GLuint* texture, GLenum attachment) {
	printf("\t%s activating...", name);
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Bind texture to attachment
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachment, GL_TEXTURE_2D, *texture, 0);
	printf("DONE\n");
}

void
DeferredLighting::InitShaders(const string shaderPath)
{
	string shaderName;
	// GATHER SHADER
	gatherShader = new Shader();
	shaderName = shaderPath + GATHER_VERT_SHADER;
	if (gatherShader->addVert(shaderName.c_str())) {
		printf("\tGATHER_VERT_SHADER '%s' added\n", shaderName.c_str());
	} else {
		printf("\tGATHER_VERT_SHADER '%s' failed\n", shaderName.c_str());
	}
	shaderName = shaderPath + GATHER_FRAG_SHADER;
	if (gatherShader->addFrag(shaderName.c_str())) {
		printf("\tGATHER_FRAG_SHADER '%s' added\n", shaderName.c_str());
	} else {
		printf("\tGATHER_FRAG_SHADER '%s' failed\n", shaderName.c_str());
	}
	gatherShader->build();
	// DIRECT TARGET SHADER
	directTargetShader = new Shader();
	shaderName = shaderPath + DIR_TARGET_FRAG_SHADER;
	if (directTargetShader->addFrag(shaderName.c_str())) {
		printf("\tDIR_TARGET_FRAG_SHADER '%s' added\n", shaderName.c_str());
	} else {
		printf("\tDIR_TARGET_FRAG_SHADER '%s' failed\n", shaderName.c_str());
	}
	directTargetShader->build();
	// DIRECTIONAL AND AMBIENT LIGHT SHADER
	dirAmbLightShader = new Shader();
	shaderName = shaderPath + DIR_AMB_LIGHT_FRAG_SHADER;
	if (dirAmbLightShader->addFrag(shaderName.c_str())) {
		printf("\tDIR_AMB_LIGHT_FRAG_SHADER '%s' added\n", shaderName.c_str());
	} else {
		printf("\tDIR_AMB_LIGHT_FRAG_SHADER '%s' failed\n", shaderName.c_str());
	}
	dirAmbLightShader->build();
	// POINT LIGHT SHADER
	pointLightShader = new Shader();
	shaderName = shaderPath + POINT_LIGHT_VERT_SHADER;
	if (pointLightShader->addVert(shaderName.c_str())) {
		printf("\tPOINT_LIGHT_VERT_SHADER '%s' added\n", shaderName.c_str());
	} else {
		printf("\tPOINT_LIGHT_VERT_SHADER '%s' failed\n", shaderName.c_str());
	}
	shaderName = shaderPath + POINT_LIGHT_FRAG_SHADER;
	if (pointLightShader->addFrag(shaderName.c_str())) {
		printf("\tPOINT_LIGHT_FRAG_SHADER '%s' added\n", shaderName.c_str());
	} else {
		printf("\tPOINT_LIGHT_FRAG_SHADER '%s' failed\n", shaderName.c_str());
	}
	pointLightShader->build();
}

void
DeferredLighting::DrawFullScreenQuad(int screenWidth, int screenHeight)
{
	// Matrix setup
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,screenWidth,0,screenHeight,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Set OpenGL settings
	glColor3f(0,0,1);
	GLboolean depthTestEnabled;
	glGetBooleanv(GL_DEPTH_TEST, &depthTestEnabled);
	glDisable(GL_DEPTH_TEST);
	GLboolean lightingEnabled;
	glGetBooleanv(GL_LIGHTING, &lightingEnabled);
	glDisable(GL_LIGHTING);

	// Draw a Big Quad
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(screenWidth, 0, 0);
	glVertex3f(screenWidth, screenHeight, 0);
	glVertex3f(0, screenHeight, 0);
	glEnd();

	// Restore OpenGL settings
	if (depthTestEnabled)	glEnable(GL_DEPTH_TEST);
	if (lightingEnabled)	glEnable(GL_LIGHTING);

	// Matrix breakdown
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void
DeferredLighting::DrawDirectTarget(GLuint bufferToDraw, int screenWidth, int screenHeight, float zNear, float zFar) {
   directTargetShader->attach();
   //Set shader uniforms
   GLint loc = glGetUniformLocation(directTargetShader->shaderProg, "bufferToDraw"); //Get uniform sampler location
   glActiveTexture(GL_TEXTURE0);               // Bind         to         unit
   glBindTexture(GL_TEXTURE_2D, bufferToDraw); //      texture    texture      0
   glUniform1i(loc, 0); //pass 0 to denote texture unit 0
   loc = glGetUniformLocation(directTargetShader->shaderProg, "screenWidth");
   glUniform1i(loc, screenWidth);
   loc = glGetUniformLocation(directTargetShader->shaderProg, "screenHeight");
   glUniform1i(loc, screenHeight);
   loc = glGetUniformLocation(directTargetShader->shaderProg, "near");
   glUniform1f(loc, zNear);
   loc = glGetUniformLocation(directTargetShader->shaderProg, "far");
   glUniform1f(loc, zFar);
   loc = glGetUniformLocation(directTargetShader->shaderProg, "doDepth");
   glUniform1i(loc, bufferToDraw==depthtexture);
   // draw
   DrawFullScreenQuad(screenWidth, screenHeight);
   //breakdown
   directTargetShader->detach();
}

void
DeferredLighting::CheckExtensions()
{
	printf("***DeferredLighting EXTENSION CHECK START***\n\n");

	//Check for OpenGL 2.0 for shaders and stuff
    /*
	if (!glewIsSupported("GL_VERSION_2_0")) {
		printf("\tERROR: OpenGL 2.0 not supported.\n");
		printf("\t%s\n", (char*)glGetString( GL_VERSION ) );
		exit(-1);
	}
	printf("\tOpenGL 2.0 supported.  OpenGL Version = %s  GLEW Version = %s\n", (char*)glGetString(GL_VERSION), glewGetString(GLEW_VERSION));
     */

	//Check for number of available buffers
	GLint maxbuffers;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);
	if(maxbuffers < NUM_MRTS) {
		printf("\tERROR: fewer than 4 render targets available.\n");
		exit(-1);
	}
	printf("\t%d render targets available.\n", maxbuffers);

	printf("\n***DeferredLighting EXTENSION CHECK DONE!***\n");
}
