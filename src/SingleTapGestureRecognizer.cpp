#include "SingleTapGestureRecognizer.h"
#include "GestureRecognizer.h"
#include <assert.h>

#define MAX_MONITORED_TOUCHES 100
#define ALLOWED_CONTACT_TIME 0.05f

//-----------------------------------------------------------------------------------
void SingleTapGestureRecognizer::Initialize(
		GestureRecognizer* recognizer,
		IGestureConsumer* consumer)
{
	_GestureRecognizer = recognizer;
	Consumer = consumer;

	MonitoredTouches.reserve(MAX_MONITORED_TOUCHES);
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::RemoveMonitoredTouch(int touchId)
{
	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		if (MonitoredTouches[i] == touchId)
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
	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		if (MonitoredTouches[i] == touchId) return true;
	}
	return false;
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::OnTouchMoved(const Touch& touch, float currentTime)
{
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::OnTouchDown(const Touch& touch)
{
	MonitoredTouches.push_back(touch.Id);
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::OnTouchUp(const Touch& touch, float currentTime)
{
    ofLog() << "["<<touch.Id<<"] "<< "TAP";
    Consumer->OnSingleTap(touch.Position, touch.PeakPressure);
    RemoveMonitoredTouch(touch.Id);
}

//------------------------------------------------------------------------------------
bool SingleTapGestureRecognizer::TapStillPossible(const Touch& touch, float currentTime)
{
	return (currentTime - touch.TimeDown < ALLOWED_CONTACT_TIME);
}

//------------------------------------------------------------------------------------
void SingleTapGestureRecognizer::Update(
		float currentTime, 
		int* out_canceledTouches, 
		int* out_canceledTouchesCount)
{
	*out_canceledTouchesCount = 0;

	for (int i = 0; i < MonitoredTouches.size(); i++)
	{
		const Touch& touch = GetTouch(MonitoredTouches[i]);
		if (!TapStillPossible(touch, currentTime))
		{
			out_canceledTouches[*out_canceledTouchesCount] = touch.Id;
			*out_canceledTouchesCount = *out_canceledTouchesCount + 1;
			RemoveMonitoredTouch(touch.Id);
		}
	}
}

//------------------------------------------------------------------------------------
const Touch& SingleTapGestureRecognizer::GetTouch(int id) 
{ 
	return _GestureRecognizer->GetTouch(id); 
}
