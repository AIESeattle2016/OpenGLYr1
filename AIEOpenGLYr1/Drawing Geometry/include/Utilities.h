//////////////////////////////////////////////////////////////////////////
// File: Utilities.h
// Author: Terry Nguyen
// Date: 01/06/2015
// Brief: Functions for convenience in working with OpenGL
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <vector>
#include <string>
#include <fstream>

#include <GL\glew.h>

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);

#endif