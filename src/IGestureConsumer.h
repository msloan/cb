#pragma once
#include "ofBaseTypes.h"

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

