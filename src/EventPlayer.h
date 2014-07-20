#pragma once
#include <vector>
#include "Event.h"

class IEventReceiver;

class EventPlayer
{
	std::vector<Event> Events;

	float	UnconsumedTime;
	int		NextEventIndex;

	std::vector<IEventReceiver*> Receivers;

	void	PlayEvent(const Event& event);
	void	PlayNextEvent();
	Event&	NextEvent();
	bool	CaughtUp();
	bool	PlaybackFinished();
	void 	SendTimePassedEvent(float dt);
	bool	GetNextTimeEventIndex(int currentIndex, int* result);

public:
	EventPlayer();

	void Clear();

	void RegisterReceiver(IEventReceiver* receiver);

	void Record(const Event& newEvent);

	void SetPosition(float time);
	void Play(float dt);
	void Replay(IEventReceiver* receiver);
	void Truncate(float time);
};

