#include "GestureRecognizer.h"
#include "SingleTapGestureRecognizer.h"
#include "DragGestureRecognizer.h"
#include <assert.h>

#define MAX_TOUCHES 50

//------------------------------------------------------------------------------------
void GestureRecognizer::Initialize(IGestureConsumer* consumer)
{
	TapRecognizer.Initialize(consumer);
	DragRecognizer.Initialize(consumer);
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnEvent(const Event& event)
{
	Touch touch;
	touch.Id = event.Value.Touch.Id;
	touch.Position = ofVec2f(
			event.Value.Touch.x,
			event.Value.Touch.y);
	touch.Pressure = event.Value.Touch.Pressure;
	touch.TimeDown = ofGetElapsedTimef();

	if (event.Type == Event::TouchDown)
	{
		OnTouchDown(touch);
	}
	else if (event.Type == Event::TouchUp)
	{
		OnTouchUp(touch);
	}
	else if (event.Type == Event::TouchMove)
	{
		OnTouchMoved(touch);
	}
	else if (event.Type == Event::TimePassed)
	{
		OnUpdate(event.Value.TimePassed.DeltaTime);
	}
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchMoved(const Touch& touch)
{
	if (TapRecognizer.IsMonitoringTouch(touch.Id))
	{
		TapRecognizer.OnTouchMoved(touch, ofGetElapsedTimef());
	}
	else if (DragRecognizer.IsMonitoringTouch(touch.Id))
	{
		DragRecognizer.OnTouchMoved(touch, ofGetElapsedTimef());
	}
	else
	{
		DragRecognizer.OnTouchDown(touch);
	}
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchDown(const Touch& touch)
{
	TapRecognizer.OnTouchDown(touch);
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchUp(const Touch& touch)
{
	if (TapRecognizer.IsMonitoringTouch(touch.Id))
	{
		TapRecognizer.OnTouchUp(touch, ofGetElapsedTimef());
	}
	else 
	{
		DragRecognizer.OnTouchUp(touch, ofGetElapsedTimef());
	}
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnUpdate(float secondsPassed)
{
	Touch canceledTouches[MAX_MONITORED_TOUCHES];
	int canceledTouchesCount;

	TapRecognizer.Update(ofGetElapsedTimef(), &canceledTouches[0], &canceledTouchesCount);

	for (int i = 0; i < canceledTouchesCount; i++)
	{
		Touch& canceledTouch = canceledTouches[i];
		DragRecognizer.OnTouchDown(canceledTouch);
	}
}
