#include "PCH.h"
#include "EventPlayer.h"

EventPlayer::EventPlayer()
{
	CurrentState = Recording;
}

void EventPlayer::Record(const Event& newEvent)
{
	assert(CurrentState == Recording);

	Events.push_back(newEvent);
}

void EventPlayer::Clear()
{
	assert(CurrentState == Recording);

	Events.clear();
}

void EventPlayer::StartPlayback(float startTime, IEventReceiver* receiver)
{
	assert(receiver != NULL);
	assert(startTime >= 0.f);
	assert(CurrentState == Recording);

	PlaybackReceiver = receiver;

	// TODO: find NextEventIndex based on startTime
	StartTime = startTime;
	NextEventIndex = 0;
	UnconsumedTime = 0.f;

	SetState(Playing);
}

void EventPlayer::Update(float dt)
{
	switch (CurrentState)
	{
	case Playing:
		UnconsumedTime += dt;
		while (!CaughtUp())
		{
			if (NextEvent()->Type == Event::TimePassed)
			{
				UnconsumedTime -= NextEvent()->Value.TimePassed.DeltaTime;
			}

			PlayNextEvent();
			if (PlaybackFinished())
			{
				SetState(Recording);
				Clear();
				return;
			}
		}
		break;

	case Recording:
		break;
	}
}

void EventPlayer::PlayNextEvent()
{
	PlaybackReceiver->OnEvent(Events[NextEventIndex]);
	NextEventIndex++;
}

Event* EventPlayer::NextEvent()
{
	return &Events[NextEventIndex];
}

bool EventPlayer::CaughtUp()
{
	return NextEvent()->Type == Event::TimePassed
		&& NextEvent()->Value.TimePassed.DeltaTime > UnconsumedTime;
}

bool EventPlayer::PlaybackFinished()
{
	return NextEventIndex == (Events.size() - 1);
}