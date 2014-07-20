#include "GestureRecognizer.h"
#include "SingleTapGestureRecognizer.h"

void GestureRecognizer::Initialize(IGestureConsumer* consumer)
{
	SingleTapGestureRecognizer* singleTap = new SingleTapGestureRecognizer();
	singleTap->Initialize(consumer);

	Recognizers.push_back(ofPtr<IGestureRecognizer>(singleTap));
}

void GestureRecognizer::OnEvent(const Event& event)
{
	if (event.Type == Event::TouchDown)
	{
		Touch touch;
		touch.Id = event.Value.Touch.Id;
		touch.Position = ofVec2f(
				event.Value.Touch.x,
				event.Value.Touch.y);
		touch.Pressure = event.Value.Touch.Pressure;

		NotifyTouchDown(touch, ofGetElapsedTimef());
	}
	else if (event.Type == Event::TouchUp)
	{
		Touch touch;
		touch.Id = event.Value.Touch.Id;
		touch.Position = ofVec2f(
				event.Value.Touch.x,
				event.Value.Touch.y);
		touch.Pressure = event.Value.Touch.Pressure;

		NotifyTouchUp(touch, ofGetElapsedTimef());
	}
}

void GestureRecognizer::NotifyTouchDown(Touch touch, float currentTime)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->OnTouchDown(touch, currentTime);
	}
}

void GestureRecognizer::NotifyTouchUp(Touch touch, float currentTime)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->OnTouchUp(touch, currentTime);
	}
}

void GestureRecognizer::NotifyTouchMoved(Touch touch, float currentTime)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->OnTouchMoved(touch, currentTime);
	}
}

void GestureRecognizer::NotifyUpdate(float secondsPassed)
{
	for (int i = 0; i < Recognizers.size(); i++)
	{
		Recognizers[i]->Update(secondsPassed);
	}
}
