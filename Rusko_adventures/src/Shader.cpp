#include "Shader.h"

Shader::Shader() : shaderProg(0), vert(0), frag(0)
{
}

Shader::~Shader()
{
	glDetachShader(shaderProg, vert);
	glDeleteShader(vert);
	glDetachShader(shaderProg, frag);
	glDeleteShader(frag);
	glDeleteProgram(shaderProg);
}

bool Shader::attach()
{
	if(shaderProg)	glUseProgram(shaderProg);
	else			return false;
	return true;
}

bool Shader::detach()
{
	if(shaderProg)	glUseProgram(0);
	else			return false;
	return true;
}

bool Shader::addVert(const char * filename)
{
	// load the vertex shader
	const char *shaderText = (const char*)textFileRead(filename);
	if (!shaderText) return false;
	// set the vertex shader
	return addSubShader(filename, shaderText, &vert, GL_VERTEX_SHADER);
}

bool Shader::addFrag(const char * filename)
{
	// load the fragment shader
	const char *shaderText = (const char*)textFileRead(filename);
	if (!shaderText) return false;
	// set the fragment shader
	return addSubShader(filename, shaderText, &frag, GL_FRAGMENT_SHADER);
}

bool Shader::addSubShader(const char* name, const char* shaderBuffer, GLuint* subShader, GLenum type)
{
	// Get some text and error check
	const char* typeText;
	if (type==GL_VERTEX_SHADER)			typeText = "Vertex";
	else if (type==GL_FRAGMENT_SHADER)	typeText = "Fragment";
	else								return false;

	// no code, use fixed functionality
	if (!shaderBuffer) {
		if (!shaderProg) shaderProg = glCreateProgram();
		if(*subShader) {
			glDetachShader(shaderProg, *subShader);
			glDeleteShader(*subShader);
			*subShader = NULL;
		}
		return true;
	}

	// set the shader
	if (!*subShader) *subShader = glCreateShader(type);
	glShaderSource(*subShader, 1, &shaderBuffer, 0);
	free((void*)shaderBuffer);
	shaderBuffer = NULL;

	glCompileShader(*subShader);

	if (!shaderProg) shaderProg = glCreateProgram();
	glAttachShader(shaderProg, *subShader);

	// print debug info
	printf("Shader: %s Shader [%s]\n", typeText, name);
	printShaderInfoLog(*subShader);
	return true;
}

bool Shader::build()
{
	glLinkProgram(shaderProg);
	printProgramInfoLog();
	return true;
}

void Shader::printShaderInfoLog(GLuint s)
{
	if (!SHADER_DEBUG_INFO) return;
	int infoLogLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(s, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		infoLog = (char*)malloc(infoLogLength);
		glGetShaderInfoLog(s, infoLogLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}

void Shader::printProgramInfoLog()
{
	if (!SHADER_DEBUG_INFO) return;
	int infoLogLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(shaderProg, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0) {
		infoLog = (char *)malloc(infoLogLength);
		glGetProgramInfoLog(shaderProg, infoLogLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
	}
}
