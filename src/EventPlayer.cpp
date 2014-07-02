#include "PCH.h"
#include "EventPlayer.h"

EventPlayer::EventPlayer()
{
	NextEventIndex = 0;
	UnconsumedTime = 0.f;
}

void EventPlayer::Record(const Event& newEvent)
{
	Events.push_back(newEvent);
	NextEventIndex = Events.size();
}

void EventPlayer::Clear()
{
	Events.clear();
}

bool EventPlayer::GetNextTimeEventIndex(int currentIndex, int* result)
{
	do
	{
		++currentIndex;
		if (currentIndex >= Events.size()) 
		{
			return false;
		} 
	}
	while (Events[currentIndex].Type != Event::TimePassed);

	*result = currentIndex;
	return true;
}
void EventPlayer::SetPosition(float time)
{
	float accumulatedTime = 0.0f;
	float nextTimeToAccumulate = 0.0f;
	int eventsIndex = 0;
	NextEventIndex = 0;
	while (GetNextTimeEventIndex(eventsIndex, &eventsIndex))
	{
		nextTimeToAccumulate = Events[eventsIndex].Value.TimePassed.DeltaTime;
		if (accumulatedTime + nextTimeToAccumulate < time)
		{
			accumulatedTime += nextTimeToAccumulate;
			NextEventIndex = eventsIndex;
		}
		else
		{
			break;
		}
	}

	UnconsumedTime = -(time - accumulatedTime);
}

void EventPlayer::Replay(ofPtr<IEventReceiver> receiver)
{
	// TODO
}

void EventPlayer::Truncate(float time)
{
	// TODO
}

void EventPlayer::SetReceiver(ofPtr<IEventReceiver> receiver) 
{ 
	PlaybackReceiver = receiver; 
}

void EventPlayer::Play(float dt)
{
	if (PlaybackFinished())
	{
		// Continue notifying event receiver that time is passing until EventPlayer is
		// explicitly told to stop. This lets the visualizations at the end of a layer 
		// continue to animate even if the playback was cut short.
		SendTimePassedEvent(dt);
		return;
	}

	UnconsumedTime += dt;
	while (!PlaybackFinished() && !CaughtUp())
	{
		if (NextEvent().Type == Event::TimePassed)
		{
			UnconsumedTime -= NextEvent().Value.TimePassed.DeltaTime;
		}

		PlayNextEvent();
	}
}

void EventPlayer::SendTimePassedEvent(float dt)
{
	Event timePassed;
	timePassed.Type = Event::TimePassed;
	timePassed.Value.TimePassed.DeltaTime = dt;
	PlaybackReceiver->OnEvent(timePassed);
}

void EventPlayer::PlayNextEvent()
{
	PlaybackReceiver->OnEvent(Events[NextEventIndex]);
	NextEventIndex++;
}

Event& EventPlayer::NextEvent()
{
	return Events[NextEventIndex];
}

bool EventPlayer::CaughtUp()
{
	return NextEvent().Type == Event::TimePassed
		&& NextEvent().Value.TimePassed.DeltaTime > UnconsumedTime;
}

bool EventPlayer::PlaybackFinished()
{
	return NextEventIndex == Events.size();
}
