#pragma once
#include "ofBaseTypes.h"

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

class IDragGestureConsumer
{
public:
	virtual void OnUpdateDrag(ofVec2f position, float pressure) = 0;
	virtual void OnEndDrag(ofVec2f position, float pressure) = 0;
};

class IGestureConsumer
{
public:
	virtual void OnSingleTap(ofVec2f position, float pressure) = 0;
	virtual IDragGestureConsumer* 	OnStartDrag(ofVec2f position, float pressure) = 0;
};

