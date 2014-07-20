#pragma once
#include "IGestureRecognizer.h"
#include <vector>


class MonitoredTouch
{
public:
	int 	Id;
	float 	TouchDownTime;
};

class SingleTapGestureRecognizer : public IGestureRecognizer
{

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
