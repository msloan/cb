#pragma once
#include "ofVec2f.h"
#define MAX_MONITORED_TOUCHES 100

class Touch
{
public:
	int 	Id;
	float 	TimeDown;

	float 	Pressure;
	float 	PeakPressure;

	ofVec2f StartPosition;
	ofVec2f Position;
};

class IGestureRecognizer
{
public:
	virtual bool IsMonitoringTouch(int touchid);

	virtual void OnTouchDown(Touch touch, float currentTime) = 0;
	virtual bool OnTouchMoved(Touch touch, float currentTime) = 0;
	virtual void OnTouchUp(Touch touch, float currentTime) = 0;
	virtual void Update(float secondsPassed, const std::vector<int> ) = 0;
};
