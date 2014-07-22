#include "SingleTapGestureRecognizer.h"
#include "GestureRecognizer.h"
#include <assert.h>

#define MAX_MONITORED_TOUCHES 100
#define ALLOWED_CONTACT_TIME 0.1f

//-----------------------------------------------------------------------------------
void SingleTapGestureRecognizer::Initialize(
		IGestureConsumer* consumer)
{
	Consumer = consumer;

	MonitoredTouches.reserve(MAX_MONITORED_TOUCHES);
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::RemoveMonitoredTouch(Touch touch)
{
	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		if (MonitoredTouches[i].Id == touch.Id)
		{
			MonitoredTouches.erase(MonitoredTouches.begin() + i);
			return;
		}
	}
	assert(0);
}

//------------------------------------------------------------------------------------
bool SingleTapGestureRecognizer::IsMonitoringTouch(int touchId)
{
	return FindMonitoredTouch(touchId) != NULL;
}

//------------------------------------------------------------------------------------
Touch* SingleTapGestureRecognizer::FindMonitoredTouch(int touchId)
{
	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		if (MonitoredTouches[i].Id == touchId) 
		{
			return &MonitoredTouches[i];
		}
	}
	return NULL;
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::OnTouchMoved(const Touch& touch, float currentTime)
{
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::OnTouchDown(const Touch& touch)
{
	MonitoredTouches.push_back(touch);
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::OnTouchUp(const Touch& touch, float currentTime)
{
	if (TapStillPossible(touch, currentTime))
	{
		Consumer->OnSingleTap(touch.Position, touch.Pressure);
	}

	RemoveMonitoredTouch(touch);
}

//------------------------------------------------------------------------------------
bool SingleTapGestureRecognizer::TapStillPossible(const Touch& touch, float currentTime)
{
	return (currentTime - touch.TimeDown < ALLOWED_CONTACT_TIME);
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::Update(
		float currentTime, 
		Touch* out_canceledTouches, 
		int* out_canceledTouchesCount)
{
	*out_canceledTouchesCount = 0;

	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		Touch& touch = MonitoredTouches[i];
		if (!TapStillPossible(touch, currentTime))
		{
			out_canceledTouches[*out_canceledTouchesCount] = touch;	
			*out_canceledTouchesCount = *out_canceledTouchesCount + 1;
			RemoveMonitoredTouch(touch);
		}
	}
}
