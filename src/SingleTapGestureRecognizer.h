#pragma once
#include "IGestureRecognizer.h"
#include "IGestureConsumer.h"
#include <vector>

class GestureRecognizer;

namespace
{
	struct MonitoredTouch
	{
		int 	Id;
		float 	TouchDownTime;
	};
}

class SingleTapGestureRecognizer : public IGestureRecognizer
{
	IGestureConsumer* 	Consumer;
	GestureRecognizer*	_GestureRecognizer;

	std::vector<MonitoredTouch> 	MonitoredTouches;

	void RemoveMonitoredTouch(Touch touch);
	MonitoredTouch* FindMonitoredTouch(Touch touch);

public:
	virtual void Initialize(
			GestureRecognizer* gestureRecognizer,
			IGestureConsumer* consumer);

	virtual void OnTouchDown(Touch touch, float currentTime);
	virtual void OnTouchUp(Touch touch, float currentTime);
	virtual void OnTouchMoved(Touch touch, float currentTime) {}
	virtual void Update(float secondsPassed) {}
};
