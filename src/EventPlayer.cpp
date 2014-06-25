#include "PCH.h"
#include "EventPlayer.h"

EventPlayer::EventPlayer()
{
	CurrentState = State::Idle;
}

void EventPlayer::Record(const Event& newEvent)
{
	assert(CurrentState == State::Idle);

	Events.push_back(newEvent);
}

void EventPlayer::Reset()
{
	Stop();
	Events.clear();
}

void EventPlayer::Stop()
{
	SetState(State::Idle);
}

void EventPlayer::Clear()
{
	assert(CurrentState == State::Idle);

	Events.clear();
}

void EventPlayer::StartPlayback(float startTime, IEventReceiver* receiver)
{
	assert(receiver != NULL);
	assert(startTime >= 0.f);
	assert(CurrentState == State::Idle);

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
				SetState(State::Idle);
				return;
			}
		}
		break;

	case State::Recording:
	case State::Idle:
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
