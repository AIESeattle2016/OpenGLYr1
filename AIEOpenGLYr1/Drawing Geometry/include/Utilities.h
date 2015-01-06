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

struct Vertex
{
	float fPositions[4];
	float fColours[4];
};

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

#endif