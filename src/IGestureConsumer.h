#pragma once
#include "ofBaseTypes.h"

class IDragGestureConsumer
{
public:
	virtual void UpdateDrag(ofVec2f position, float pressure) = 0;
	virtual void EndDrag(ofVec2f position, float pressure) = 0;
};

class IGestureConsumer
{
public:
	virtual void OnSingleTap(ofVec2f position, float pressure) = 0;
	virtual ofPtr<IDragGestureConsumer> OnStartDrag(ofVec2f position, float pressure) = 0;
};

