#include "GestureRecognizer.h"
#include "SingleTapGestureRecognizer.h"
#include "DragGestureRecognizer.h"
#include <assert.h>

#define MAX_TOUCHES 50

//------------------------------------------------------------------------------------
void GestureRecognizer::Initialize(IGestureConsumer* consumer)
{
	TapRecognizer.Initialize(this, consumer);
	DragRecognizer.Initialize(consumer);
	Touches.reserve(MAX_TOUCHES);
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnEvent(const Event& event)
{
	if (event.Type == Event::TouchDown)
	{
		Touch touch;
		touch.Id = event.Value.Touch.Id;
		touch.Position = ofVec2f(
				event.Value.Touch.x,
				event.Value.Touch.y);
		touch.StartPosition = touch.Position;
		touch.Pressure = event.Value.Touch.Pressure;
		touch.PeakPressure = touch.Pressure;
		touch.TimeDown = ofGetElapsedTimef();
		Touches.push_back(touch);

		OnTouchDown(touch.Id);
	}
	else if (event.Type == Event::TouchUp)
	{
        if (Touches.size() == 0) return; // hack related to debug buttons
		UpdateTouch(event);
		OnTouchUp(event.Value.Touch.Id);
        RemoveTouch(event.Value.Touch.Id);
	}
	else if (event.Type == Event::TouchMove)
	{
        if (Touches.size() == 0) return; // hack related to debug buttons
		UpdateTouch(event);
		OnTouchMoved(event.Value.Touch.Id);
	}
	else if (event.Type == Event::TimePassed)
	{
		OnUpdate(event.Value.TimePassed.DeltaTime);
	}
}

void GestureRecognizer::RemoveTouch(int id)
{
    for (int i = 0; i < Touches.size(); i++)
    {
        if (Touches[i].Id == id)
        {
            Touches.erase(Touches.begin() + i);
            return;
        }
    }
    assert(0);
}
//------------------------------------------------------------------------------------
void GestureRecognizer::UpdateTouch(const Event& event)
{
	Touch& touch = GetTouch(event.Value.Touch.Id);

	touch.Position = ofVec2f(
			event.Value.Touch.x,
			event.Value.Touch.y);

	touch.PeakPressure = std::max(
			touch.Pressure,
			event.Value.Touch.Pressure);

	touch.Pressure = event.Value.Touch.Pressure;
}


//------------------------------------------------------------------------------------
Touch& GestureRecognizer::GetTouch(int id)
{
	for (int i = 0; i < Touches.size(); i++)
	{
		if (Touches[i].Id == id) return Touches[i];
	}

	assert(0);
	Touch dummy;
	return dummy;
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchMoved(int touchId)
{
	Touch& touch = GetTouch(touchId);

	if (TapRecognizer.IsMonitoringTouch(touchId))
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
void GestureRecognizer::OnTouchDown(int touchId)
{
	TapRecognizer.OnTouchDown(
			GetTouch(touchId));
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchUp(int touchId)
{
	Touch& touch = GetTouch(touchId);
	if (TapRecognizer.IsMonitoringTouch(touchId))
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
	int canceledTouches[MAX_MONITORED_TOUCHES];
	int canceledTouchesCount;

	TapRecognizer.Update(ofGetElapsedTimef(), &canceledTouches[0], &canceledTouchesCount);

	for (int i = 0; i < canceledTouchesCount; i++)
	{
		Touch& canceledTouch = GetTouch(
				canceledTouches[i]);

		DragRecognizer.OnTouchDown(canceledTouch);
	}
}
