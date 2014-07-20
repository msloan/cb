#include "SingleTapGestureRecognizer.h"
#include <assert.h>

#define MAX_MONITORED_TOUCHES 100
#define ALLOWED_CONTACT_TIME 0.5f

void SingleTapGestureRecognizer::Initialize(IGestureConsumer* consumer)
{
	Consumer = consumer;
	MonitoredTouches.reserve(MAX_MONITORED_TOUCHES);
}

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

SingleTapGestureRecognizer::MonitoredTouch* SingleTapGestureRecognizer::FindMonitoredTouch(Touch touch)
{
	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		if (MonitoredTouches[i].Id == touch.Id) 
		{
			return &MonitoredTouches[i];
		}
	}
	return NULL;
}

void SingleTapGestureRecognizer::OnTouchDown(Touch touch, float currentTime)
{
	MonitoredTouch monitoredTouch;
	monitoredTouch.Id = touch.Id;
	monitoredTouch.TouchDownTime = currentTime;
	MonitoredTouches.push_back(monitoredTouch);
}

void SingleTapGestureRecognizer::OnTouchUp(Touch touch, float currentTime)
{
	MonitoredTouch* monitored = FindMonitoredTouch(touch);

	if (monitored == NULL) return;

	if (currentTime - monitored->TouchDownTime < ALLOWED_CONTACT_TIME)
	{
		Consumer->OnSingleTap(touch.Position, touch.Pressure);
	}

	RemoveMonitoredTouch(touch);
}
