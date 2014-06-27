#pragma once
#include <vector>
#include "Event.h"

class IEventReceiver
{
public:
	virtual void OnEvent(const Event& event) = 0;
};

class EventPlayer
{
public:
	enum State
	{
		Idle,
		Playing
	};

private:
	std::vector<Event> Events;

	float	StartTime;
	float	UnconsumedTime;
	int		NextEventIndex;
	bool	_PlaybackFinished;

	IEventReceiver* PlaybackReceiver;

	State CurrentState;
	void SetState(State state) { CurrentState = state; }

	void	PlayNextEvent();
	Event&	NextEvent();
	bool	CaughtUp();
	bool	PlaybackFinished();
	void 	SendTimePassedEvent(float dt);

public:
	EventPlayer();

	void Clear();

	void Record(const Event& newEvent);
	void Reset();
	void Stop();

	const std::vector<Event>& GetRecordedEvents();

	void StartPlayback(float startTime, IEventReceiver* receiver);
	void Update(float dt);

	State GetState() { return CurrentState; }
};

