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

#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>

#include <GL\glew.h>

using glm::mat4;

struct Vertex
{
	float fPositions[4];
	float fColours[4];
	float fUVs[2];
};

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);

mat4 getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);

glm::vec2 pixelToScreen(glm::vec2 pixels, glm::vec2 screenResolution);

#endif