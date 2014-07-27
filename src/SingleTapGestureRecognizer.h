#pragma once
#include "IGestureRecognizer.h"
#include "IGestureConsumer.h"
#include <vector>

class GestureRecognizer;

class SingleTapGestureRecognizer
{
	IGestureConsumer* 	Consumer;
	GestureRecognizer*	_GestureRecognizer;

	std::vector<int> MonitoredTouches;

	bool TapStillPossible(const Touch& touch, float currentTime);
	void RemoveMonitoredTouch(int touchId);

	const Touch& GetTouch(int id);

public:
	void Initialize(
			GestureRecognizer* recognizer,
			IGestureConsumer* consumer);

	bool IsMonitoringTouch(int touchId);

	void OnTouchDown(const Touch& touch);
	void OnTouchUp(const Touch& touch, float currentTime);
	void OnTouchMoved(const Touch& touch, float currentTime);

	void Update(
			float currentTime, 
			int* out_canceledTouches, 
			int* out_canceledTouchesCount);
};
