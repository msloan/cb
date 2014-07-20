#pragma once
#include "IGestureRecognizer.h"
#include "GestureManager.h"


class MonitoredTouch
{
public:
	int 	Id;
	float 	TouchDownTime;
};

class SingleTapGestureRecognizer : public IGestureRecognizer
{

	ISingleTapVisualizer* 	Visualizer;

	vector<MonitoredTouch> 	MonitoredTouches;

	void RemoveMonitoredTouch(Touch touch);
	MonitoredTouch* FindMonitoredTouch(Touch touch);

public:
	virtual void Initialize(ISingleTapVisualizer* visualizer);

	virtual void OnTouchDown(Touch touch, float currentTime);
	virtual void OnTouchUp(Touch touch, float currentTime);
	virtual void OnTouchMoved(Touch touch, float currentTime) {}
	virtual void Update(float secondsPassed) {}
};
