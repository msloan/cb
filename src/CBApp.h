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
		Playing,
	};
	
private:

	PooledFactory<CircleVisualization> CircleFactory;

	std::vector<VisualizationLayer> VisualizationLayers;
	std::vector<EventPlayer>		EventPlayers;

	VisualizationLayer& CurrentLayer() 	{ return VisualizationLayers.back(); }
	EventPlayer& CurrentPlayer() 		{ return EventPlayers.back(); }

	
	State CurrentState;

	void SetState(State nextState)	{ CurrentState = nextState; }
	bool DebugButtonPressed(const Event& event);

	void ClearAllLayers();
	void StopAllPlayers();
	void UpdatePlayers(float dt);
	void PlayAllPlayers();

	void CreateNewLayer();

public:
	CBApp::State GetState()			{ return CurrentState; }

	CBApp();
	~CBApp();

	void Initialize();
	void Update(float dt);
	void Draw();

	void PostEvent(const Event& Event);

	void RecordNewLayer();
	void Play();
	void Reset();
	void Stop();
};

