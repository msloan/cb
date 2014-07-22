#pragma once
#include "ofVec2f.h"
#define MAX_MONITORED_TOUCHES 100

class Touch
{
public:
	int 	Id;
	float 	Pressure;
	ofVec2f Position;
	float 	TimeDown;
	bool 	InUse;

	Touch()
	{
		InUse = false;
	}
};
extern Touch NullTouch;

class IGestureRecognizer
{
public:
	virtual bool IsMonitoringTouch(int touchid);

	virtual void OnTouchDown(Touch touch, float currentTime) = 0;
	virtual bool OnTouchMoved(Touch touch, float currentTime) = 0;
	virtual void OnTouchUp(Touch touch, float currentTime) = 0;
	virtual void Update(float secondsPassed, const std::vector<int> ) = 0;
};
