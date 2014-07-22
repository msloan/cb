#pragma once
#include "IGestureRecognizer.h"
#include "IGestureConsumer.h"
#include <vector>

class GestureRecognizer;

class SingleTapGestureRecognizer
{
	IGestureConsumer* 	Consumer;
	GestureRecognizer*	_GestureRecognizer;

	std::vector<Touch> 	MonitoredTouches;

	bool TapStillPossible(const Touch& touch, float currentTime);
	void RemoveMonitoredTouch(Touch touch);
	Touch* FindMonitoredTouch(int touch);

public:
	void Initialize(
			IGestureConsumer* consumer);

	bool IsMonitoringTouch(int touchId);

	void OnTouchDown(const Touch& touch);
	void OnTouchUp(const Touch& touch, float currentTime);
	void OnTouchMoved(const Touch& touch, float currentTime);

	void Update(
			float currentTime, 
			Touch* out_canceledTouches, 
			int* out_canceledTouchesCount);
};
