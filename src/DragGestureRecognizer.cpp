#include "DragGestureRecognizer.h"
#include "GestureRecognizer.h"
#include "IGestureConsumer.h"
#include <assert.h>

//-------------------------------------------------------------------------------------
void DragGestureRecognizer::Initialize(
		IGestureConsumer* consumer)
{
	Consumer = consumer;

	MonitoredTouches.reserve(MAX_MONITORED_TOUCHES);
	ActiveDrags.reserve(MAX_MONITORED_TOUCHES);
}

//-------------------------------------------------------------------------------------
void DragGestureRecognizer::OnTouchDown(const Touch& touch)
{
	ActiveDrag drag;
	drag.Id = touch.Id;
	drag.Consumer = Consumer->OnStartDrag(touch.Position, touch.PeakPressure);
    ofLog() << "["<<touch.Id<<"] "<< "START DRAG";
	ActiveDrags.push_back(drag);
}

//-------------------------------------------------------------------------------------
void DragGestureRecognizer::OnTouchUp(const Touch& touch, float currentTime)
{
	ActiveDrag* drag = FindActiveDrag(touch);

	drag->Consumer->EndDrag(touch.Position, touch.Pressure);

	RemoveActiveDrag(drag);
}

//-------------------------------------------------------------------------------------
void DragGestureRecognizer::OnTouchMoved(const Touch& touch, float currentTime) 
{
	ActiveDrag* drag = FindActiveDrag(touch);

	drag->Consumer->UpdateDrag(touch.Position, touch.Pressure);
}

//-------------------------------------------------------------------------------------
DragGestureRecognizer::ActiveDrag* DragGestureRecognizer::FindActiveDrag(Touch touch)
{
	for (int i = 0; i < ActiveDrags.size(); i++)
	{
		if (ActiveDrags[i].Id == touch.Id)
		{
			return &ActiveDrags[i];
		}
	}
	assert(0);
	return NULL;
}

//-------------------------------------------------------------------------------------
void DragGestureRecognizer::RemoveActiveDrag(ActiveDrag* drag)
{
	for (int i = 0; i < ActiveDrags.size(); i++)
	{
		if (&ActiveDrags[i] == drag)
		{
			ActiveDrags.erase(ActiveDrags.begin() + i);
			return;
		}
	}
	assert(0);
}

//-------------------------------------------------------------------------------------
bool DragGestureRecognizer::IsMonitoringTouch(int id)
{
	for (int i = 0; i < ActiveDrags.size(); i++)
	{
		if (ActiveDrags[i].Id == id)
		{
			return true;
		}
	}
	return false;
}
