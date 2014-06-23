#pragma once
#include "PooledFactory.h"
#include "VisualizationLayer.h"

class CBApp
{
public:
	enum State
	{
		Recording,
		Playing
	};
	
private:

	PooledFactory<CircleVisualization> CircleFactory;
	VisualizationLayer CurrentLayer;

	EventPlayer Player;

	
	State CurrentState;

	void SetState(State nextState)	{ CurrentState = nextState; }

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

};

