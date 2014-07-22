#pragma once
#include <vector>
#include "ofVec2f.h"
#include "IGestureRecognizer.h"
#include "ofTypes.h"

class IDragGestureConsumer;
class GestureRecognizer;
class IGestureConsumer;

class DragGestureRecognizer
{
	struct ActiveDrag
	{
		int Id;
		ofPtr<IDragGestureConsumer> Consumer;
	};

	IGestureConsumer* 		Consumer;
	GestureRecognizer* 		_GestureRecognizer;

	std::vector<ActiveDrag> 	ActiveDrags;
	std::vector<Touch> 			MonitoredTouches;

	void RemoveActiveDrag(ActiveDrag* drag);

	ActiveDrag* FindActiveDrag(Touch touch);

public:
	void Initialize(IGestureConsumer* consumer);
	bool IsMonitoringTouch(int id);

	void OnTouchDown(const Touch& touch);
	void OnTouchUp(const Touch& touch, float currentTime);
	void OnTouchMoved(const Touch& touch, float currentTime);
	void Update(float secondsPassed){}
};
