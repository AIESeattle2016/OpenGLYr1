//////////////////////////////////////////////////////////////////////////
// File: Timer.cpp
// Author: Terry Nguyen
// Date: 01/13/2015
// Brief: Platform-independent timer
//
//////////////////////////////////////////////////////////////////////////

#include <Timer.h>

#include <assert.h>

#include <GLFW\glfw3.h>

double Timer::totalTime()
{
	return glfwGetTime();
}

void Timer::Update()
{
	m_prevTime = m_curTime;
	m_curTime = totalTime();
}

double Timer::deltaTime()
{
	// time since last update
	return m_curTime - m_prevTime;
}

void Timer::totalTime(double a_newTime)
{
	glfwSetTime(a_newTime);
}