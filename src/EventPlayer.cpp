#include "PCH.h"
#include "EventPlayer.h"

EventPlayer::EventPlayer()
{
	CurrentState = State::Idle;
	_PlaybackFinished = false;
	NextEventIndex = 0;
	UnconsumedTime = 0.f;
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
	_PlaybackFinished = false;

	SetState(Playing);
}

void EventPlayer::Update(float dt)
{
	switch (CurrentState)
	{
	case Playing:
		if (_PlaybackFinished)
		{
			// Continue notifying event receiver that time is passing until EventPlayer is
			// explicitly told to stop. This lets the visualizations at the end of a layer 
			// continue to animate/fade away even if the playback was cut short.
			SendTimePassedEvent(dt);
			return;
		}

		UnconsumedTime += dt;
		while (!CaughtUp())
		{
			if (NextEvent().Type == Event::TimePassed)
			{
				UnconsumedTime -= NextEvent().Value.TimePassed.DeltaTime;
			}

			PlayNextEvent();
			if (PlaybackFinished())
			{
				_PlaybackFinished = true;
				return;
			}
		}
		break;

	case State::Idle:
		break;
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
	return NextEventIndex == (Events.size() - 1);
}
