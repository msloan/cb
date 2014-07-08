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
private:
	std::vector<Event> Events;

	float	UnconsumedTime;
	int		NextEventIndex;

	ofPtr<IEventReceiver> PlaybackReceiver;

	void	PlayNextEvent();
	Event&	NextEvent();
	bool	CaughtUp();
	bool	PlaybackFinished();
	void 	SendTimePassedEvent(float dt);
	bool	GetNextTimeEventIndex(int currentIndex, int* result);

public:
	EventPlayer();

	void Clear();

	void SetReceiver(ofPtr<IEventReceiver> receiver);

	void Record(const Event& newEvent);

	void SetPosition(float time);
	void Play(float dt);
	void Replay(ofPtr<IEventReceiver> receiver);
	void Truncate(float time);
};

