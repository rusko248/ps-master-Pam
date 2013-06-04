//------------------------------------------------------------------------------
// Ian Stewart & Ryan Schmitt
// 
//
// Description:
// Shader object to manage a pair of shaders (vertex & fragment)
//------------------------------------------------------------------------------

#ifndef __SHADER_H__
#define __SHADER_H__

#include "stglew.h"
#include <stdlib.h>
#include <stdio.h>
#include "textfile.h"

#define SHADER_DEBUG_INFO  1

class Shader {
public:
    Shader();
    ~Shader();

    bool addVert(const char*);
    bool addFrag(const char*);
    bool build();

    bool attach();
    bool detach();

    void printProgramInfoLog();
    void printShaderInfoLog(GLuint);

    GLuint shaderProg;
    GLuint vert;
    GLuint frag;

private:
   bool addSubShader(const char* name, const char* shaderBuffer, GLuint* subShader, GLenum type);
};

#endif __SHADER_H__
