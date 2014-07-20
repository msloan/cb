#pragma once
#include "ofVec2f.h"
class Touch
{
public:
	int 	Id;
	float 	Pressure;
	ofVec2f Position;
	float 	TimeDown;
};

class IGestureRecognizer
{
public:
	virtual void OnTouchDown(Touch touch, float currentTime) = 0;
	virtual void OnTouchUp(Touch touch, float currentTime) = 0;
	virtual void OnTouchMoved(Touch touch, float currentTime) = 0;
	virtual void Update(float secondsPassed) = 0;
};
