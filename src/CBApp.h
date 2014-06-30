#pragma once
#include "PooledFactory.h"
#include <vector>
#include "CompositionLayer.h"
#include "ofSoundPlayer.h"



class CBApp
{
public:
	enum State
	{
		Idle,
		Recording,
		Playing,

		LoadingNewPosition,
	};
	
private:

	PooledFactory<CircleVisualization> CircleFactory;

	std::vector<CompositionLayer> Layers;
    ofSoundPlayer SoundPlayer;

	CompositionLayer& CurrentLayer() 	{ return Layers.back(); }
	State CurrentState;
	State NextState;

	float PlayFromTime;

	void SetState(State nextState)	
	{ 
		CurrentState = nextState; 
	}

	bool DebugButtonPressed(const Event& event);

	void ClearAllLayers();
	void StopAllLayers();
	void UpdateLayers(float dt);
	void PlayAllLayers(float dt);

	void CreateNewLayer();
	void SetPositionAndTransition(float time, State nextState);

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
	void SetPosition(float time);
};

