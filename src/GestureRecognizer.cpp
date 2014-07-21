#include "GestureRecognizer.h"
#include "SingleTapGestureRecognizer.h"
#include <assert.h>

#define MAX_TOUCHES 50

//------------------------------------------------------------------------------------
void GestureRecognizer::Initialize(IGestureConsumer* consumer)
{
	SingleTapGestureRecognizer* singleTap = new SingleTapGestureRecognizer();
	singleTap->Initialize(this, consumer);

	Touches.reserve(MAX_TOUCHES);
	Recognizers.push_back(ofPtr<IGestureRecognizer>(singleTap));
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
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchMoved(const Touch& touch)
{
	NotifyTouchMoved(touch, ofGetElapsedTimef());
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchDown(const Touch& touch)
{
	Touches.push_back(touch);
	NotifyTouchDown(touch, ofGetElapsedTimef());
}

//------------------------------------------------------------------------------------
void GestureRecognizer::OnTouchUp(const Touch& touch)
{
	NotifyTouchUp(touch, ofGetElapsedTimef());
	RemoveTouch(touch);
}

//------------------------------------------------------------------------------------
void GestureRecognizer::NotifyTouchDown(Touch touch, float currentTime)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->OnTouchDown(touch, currentTime);
	}
}

//------------------------------------------------------------------------------------
void GestureRecognizer::NotifyTouchUp(Touch touch, float currentTime)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->OnTouchUp(touch, currentTime);
	}
}

//------------------------------------------------------------------------------------
void GestureRecognizer::RemoveTouch(Touch touch)
{
	for (int i = 0; i < Touches.size(); i++)
	{
		if (Touches[i].Id == touch.Id) 
		{
			Touches.erase(Touches.begin() + i);
			return;
		}
	}
	assert(0);
}

//------------------------------------------------------------------------------------
void GestureRecognizer::NotifyTouchMoved(Touch touch, float currentTime)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->OnTouchMoved(touch, currentTime);
	}
}

//------------------------------------------------------------------------------------
void GestureRecognizer::NotifyUpdate(float secondsPassed)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->Update(secondsPassed);
	}
}

//------------------------------------------------------------------------------------
Touch* GestureRecognizer::FindTouch(int id)
{
	for (int i = 0; i < Touches.size(); i++)
	{
		if (Touches[i].Id == id)
		{
			return &Touches[i];
		}
	}
	assert(0);
	return NULL;
}
//------------------------------------------------------------------------------------
void GestureRecognizer::SetTouchInUse(int id, bool inUse)
{
	Touch* touch = FindTouch(id);

	assert(inUse != touch->InUse);

	touch->InUse = inUse;
}

