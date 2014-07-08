#include "GestureListener.h"

bool SingleTapRecognizer::OnEvent(const Event& event, Event& resultGesture)
{
	if (event.Type == Event::TouchDown)
	{
		WatchedTouches.push_back(event);
	}
	else if (event.Type == Event::TimePassed)
	{
		FailHeldTouches(event.Value.TimePassed.DeltaTime);
	}
	else if (event.Type == Event::TouchMove && TouchWatched(event.Value.Touch.Id))
	{
		if (TouchOutOfRange(event.Value.Touch.Id))
		{
			Fail(event.Value.Touch.Id);
		}
	}
	else if (event.Type == Event::TouchUp && TouchWatched(event.Value.Touch.Id))
	{
		resultGesture = GetWatchedTouch(event.Value.Touch.Id);
		return true;
	}

	return false;
}

bool DragRecognizer::OnEvent(const Event& event, std::vector<Event>& resultGestures)
{
	if (event.Type == Event::TouchDown)
	{
		WatchedTouches.push_back(event);
	}
	else if (event.Type == Event::TimePassed)
	{
		resultGestures = PromoteWatchedTouches(event.Value.TimePassed.DeltaTime);
		return true;
	}
	else if (event.Type == Event::TouchMove && TouchIsDragging(event.Value.Touch.Id))
	{
		resultGesture = MakeDragChangedTouch(event.Value.Touch.Id);
		return true;
	}
	else if (event.Type == Event::TouchUp && TouchWatched(event.Value.Touch.Id))
	{
		Fail(event.Value.Touch.Id);
	}

	return false;
	
}

