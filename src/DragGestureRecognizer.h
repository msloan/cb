#pragma once
#include <vector>

namespace
{
	struct ActiveDrag
	{
		int Id;
		IDragGestureConsumer* Consumer;
	};

	struct MonitoredTouch
	{
		int Id;
	};
}

class DragGestureRecognizer : public IGestureRecognizer
{
	IGestureConsumer* 	Consumer;
	TouchManager* 		Touch;

	std::vector<ActiveDrag> ActiveDrags;
	std::vector<MonitoredTouch> 	MonitoredTouches;

	void RemoveMonitoredTouch(Touch touch);
	MonitoredTouch* FindMonitoredTouch(Touch touch);

public:
	virtual void Initialize(
			IGestureConsumer* consumer,
			std::vector<Touch>* touches);

	virtual void OnTouchDown(Touch touch, float currentTime);
	virtual void OnTouchUp(Touch touch, float currentTime);
	virtual void OnTouchMoved(Touch touch, float currentTime) {}
	virtual void Update(float secondsPassed) {}
};
