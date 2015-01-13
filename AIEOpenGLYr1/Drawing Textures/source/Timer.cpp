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
#if _DEBUG
	double total = glfwGetTime();
	assert(total != 0.0);
	return total;
#endif

	return glfwGetTime();
}

void Timer::Update()
{
	m_prevTime = totalTime();
}

double Timer::deltaTime()
{
	// time since last update
	return totalTime() - m_prevTime;
}

void Timer::totalTime(double a_newTime)
{
	glfwSetTime(a_newTime);
}