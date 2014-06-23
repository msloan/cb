#include "PCH.h"
#include "EventPlayer.h"

EventPlayer::EventPlayer()
{
	CurrentState = State::Recording;
}

void EventPlayer::Record(const Event& newEvent)
{
	assert(CurrentState == State::Recording);

	Events.push_back(newEvent);
}

void EventPlayer::Clear()
{
	assert(CurrentState == State::Recording);

	Events.clear();
}

void EventPlayer::StartPlayback(float startTime, IEventReceiver* receiver)
{
	assert(receiver != NULL);
	assert(startTime >= 0.f);
	assert(CurrentState == State::Recording);

	PlaybackReceiver = receiver;

	// TODO: find NextEventIndex based on startTime
	StartTime = startTime;
	NextEventIndex = 0;
	UnconsumedTime = 0.f;

	SetState(State::Playing);
}

void EventPlayer::Update(float dt)
{
	switch (CurrentState)
	{
	case State::Playing:
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
				SetState(State::Recording);
				Clear();
				return;
			}
		}
		break;

	case State::Recording:
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
	return NextEvent()->Type == Event::Type::TimePassed
		&& NextEvent()->Value.TimePassed.DeltaTime > UnconsumedTime;
}

bool EventPlayer::PlaybackFinished()
{
	return NextEventIndex == (Events.size() - 1);
}