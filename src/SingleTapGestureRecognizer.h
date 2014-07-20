#pragma once
#include "IGestureRecognizer.h"
#include "IGestureConsumer.h"
#include <vector>


class SingleTapGestureRecognizer : public IGestureRecognizer
{
	class MonitoredTouch
	{
	public:
		int 	Id;
		float 	TouchDownTime;
	};


	IGestureConsumer* 	Consumer;

	std::vector<MonitoredTouch> 	MonitoredTouches;

	void RemoveMonitoredTouch(Touch touch);
	MonitoredTouch* FindMonitoredTouch(Touch touch);

public:
	virtual void Initialize(IGestureConsumer* consumer);

	virtual void OnTouchDown(Touch touch, float currentTime);
	virtual void OnTouchUp(Touch touch, float currentTime);
	virtual void OnTouchMoved(Touch touch, float currentTime) {}
	virtual void Update(float secondsPassed) {}
};
