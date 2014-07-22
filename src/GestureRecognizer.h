#pragma once
#include "ofBaseTypes.h"
#include "Event.h"
#include "EventPlayer.h"
#include "IGestureRecognizer.h"

#include "IEventReceiver.h"
#include "SingleTapGestureRecognizer.h"
#include "DragGestureRecognizer.h"

class IGestureConsumer;
class IGestureRecognizer;

class GestureRecognizer : public IEventReceiver
{
	SingleTapGestureRecognizer TapRecognizer;
	DragGestureRecognizer 		DragRecognizer;
	
	void OnTouchDown(const Touch& touch);
	void OnTouchUp(const Touch& touch);
	void OnTouchMoved(const Touch& touch);
	void OnUpdate(float secondsPassed);

public:

	void Initialize(IGestureConsumer* consumer);
	virtual void OnEvent(const Event& event);
};
