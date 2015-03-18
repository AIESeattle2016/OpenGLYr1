//////////////////////////////////////////////////////////////////////////
// File: Timer.h
// Author: Terry Nguyen
// Date: 01/13/2015
// Brief: Platform-independent timer
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	double totalTime();
	void totalTime(double a_newTime);
	double deltaTime();

	void Update();
private:
	double m_prevTime = 0.0f;
	double m_curTime = 0.0f;
};

#endif