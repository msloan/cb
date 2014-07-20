#pragma once

struct Event;

class IEventReceiver
{
public:
	virtual void OnEvent(const Event& event) = 0;
};

