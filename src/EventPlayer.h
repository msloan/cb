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
		Paused,
		Playing
	};

private:
	std::vector<Event> Events;

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

	void SetReceiver(IEventReceiver* receiver);

	void Record(const Event& newEvent);
	void Reset();

	const std::vector<Event>& GetRecordedEvents();

	void SetPosition(float time);
	void Play();
	void Pause();
	void Replay(IEventReceiver* receiver);
	void Truncate(float time);
	void Update(float dt);

	State GetState() { return CurrentState; }
};

