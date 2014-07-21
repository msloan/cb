#pragma once
#include "ofBaseTypes.h"
#include "Event.h"
#include "EventPlayer.h"
#include "IGestureRecognizer.h"

#include "IEventReceiver.h"

class IGestureConsumer;
class IGestureRecognizer;

class GestureRecognizer : public IEventReceiver
{
	std::vector<ofPtr<IGestureRecognizer> > Recognizers;
	
	std::vector<Touch> Touches;

	void RemoveTouch(Touch touch);
	Touch* FindTouch(int id);

	void OnTouchDown(const Touch& touch);
	void OnTouchUp(const Touch& touch);
	void OnTouchMoved(const Touch& touch);
			

	void NotifyTouchDown(Touch touch, float currentTime);
	void NotifyTouchUp(Touch touch, float currentTime);
	void NotifyTouchMoved(Touch touch, float currentTime);
	void NotifyUpdate(float secondsPassed);

public:
	void Initialize(IGestureConsumer* consumer);
	void SetTouchInUse(int id, bool inUse);

	virtual void OnEvent(const Event& event);
};
