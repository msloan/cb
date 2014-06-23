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
		Recording,
		Playing
	};

private:
	std::vector<Event> Events;

	float	StartTime;
	float	UnconsumedTime;
	int		NextEventIndex;

	IEventReceiver* PlaybackReceiver;

	State CurrentState;
	void SetState(State state) { CurrentState = state; }

	void	PlayNextEvent();
	Event*	NextEvent();
	bool	CaughtUp();
	bool	PlaybackFinished();

public:

	EventPlayer();

	void Record(const Event& newEvent);
	void Clear();
	void StartPlayback(float startTime, IEventReceiver* receiver);
	void Update(float dt);
	State GetState() { return CurrentState; }
};

