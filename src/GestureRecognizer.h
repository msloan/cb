#pragma once
#include "ofBaseTypes.h"
#include "Event.h"
#include "EventPlayer.h"

#include "IEventReceiver.h"

class IGestureConsumer;
class IGestureRecognizer;
class Touch;

class GestureRecognizer : public IEventReceiver
{
	std::vector<ofPtr<IGestureRecognizer> > Recognizers;

	void NotifyTouchDown(Touch touch, float currentTime);
	void NotifyTouchUp(Touch touch, float currentTime);
	void NotifyTouchMoved(Touch touch, float currentTime);
	void NotifyUpdate(float secondsPassed);

public:
	virtual void OnEvent(const Event& event);

	void Initialize(IGestureConsumer* consumer);
};
