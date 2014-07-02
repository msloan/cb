#include "PCH.h"
#include "EventPlayer.h"

EventPlayer::EventPlayer()
{
	CurrentState = Paused;
	_PlaybackFinished = false;
	NextEventIndex = 0;
	UnconsumedTime = 0.f;
}

void EventPlayer::Record(const Event& newEvent)
{
	assert(CurrentState == Paused);

	Events.push_back(newEvent);
	NextEventIndex = Events.size();
}

void EventPlayer::Reset()
{
	Pause();
	Events.clear();
}

void EventPlayer::Pause()
{
	SetState(Paused);
}

void EventPlayer::Clear()
{
	assert(CurrentState == Paused);

	Events.clear();
}

void EventPlayer::SetPosition(float time)
{
	// TODO
	NextEventIndex = 0;
	UnconsumedTime = 0.f;
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

void EventPlayer::Play()
{
	assert(CurrentState == Paused);

	_PlaybackFinished = false;
	SetState(Playing);
}

void EventPlayer::Update(float dt)
{
	switch (CurrentState)
	{
	case Playing:
		if (PlaybackFinished())
		{
			// Continue notifying event receiver that time is passing until EventPlayer is
			// explicitly told to stop. This lets the visualizations at the end of a layer 
			// continue to animate/fade away even if the playback was cut short.
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
		break;

	case Paused:
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
	return NextEventIndex == Events.size();
}
