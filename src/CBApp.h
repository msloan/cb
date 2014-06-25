#pragma once
#include "PooledFactory.h"
#include "VisualizationLayer.h"
#include <vector>

class CBApp
{
public:
	enum State
	{
		Idle,
		Recording,
		Playing
	};
	
private:

	PooledFactory<CircleVisualization> CircleFactory;

	VisualizationLayer CurrentLayer;

	EventPlayer Player;

	
	State CurrentState;

	void SetState(State nextState)	{ CurrentState = nextState; }
	bool DebugButtonPressed(const Event& event);

public:
	CBApp::State GetState()			{ return CurrentState; }

	CBApp();
	~CBApp();

	void Initialize();
	void Update(float dt);
	void Draw();

	void PostEvent(const Event& Event);

	void StartRecording();
	void PlayRecording();
	void Reset();
	void Stop();
};

