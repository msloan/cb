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
	std::vector<Touch> Touches;

	SingleTapGestureRecognizer TapRecognizer;
	DragGestureRecognizer 		DragRecognizer;
	
	void OnTouchDown(int touchId);
	void OnTouchUp(int touchId);
	void OnTouchMoved(int touchId);
	void OnUpdate(float secondsPassed);

	void UpdateTouch(const Event& event);

public:

	void Initialize(IGestureConsumer* consumer);
	virtual void OnEvent(const Event& event);

	Touch& GetTouch(int id);
};
