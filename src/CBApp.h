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
		Paused,
		Recording,
		Playing,

		LoadingNewPosition,
	};

	enum Mode
	{
		mode_Play,
		mode_Edit
	};
	
private:

	PooledFactory<CircleVisualization> CircleFactory;

	std::vector<CompositionLayer> Layers;
    ofSoundPlayer SoundPlayer;

	CompositionLayer& CurrentLayer() 	{ return Layers.back(); }
	State CurrentState;
	State PreviousState;

	float PlayFromTime;

	Mode CurrentMode;

	void SetState(State nextState)	
	{ 
		PreviousState = CurrentState;
		CurrentState = nextState; 
	}

	void SetMode(Mode newMode)
	{
		CurrentMode = newMode;
	}

	bool DebugButtonPressed(const Event& event);

	void ClearAllLayers();
	void UpdateLayers(float dt);
	void PlayAllLayers();
	void PlayAllSavedLayers();
	void SetLayersPosition(float time);

	void SetPositionAndTransition(float time, State nextState);

public:
	CBApp::State GetState()			{ return CurrentState; }

	CBApp();
	~CBApp();

	void Initialize();
	void Update(float dt);
	void Draw();

	void PostEvent(const Event& Event);

	void CreateNewLayer();

	void Play();
	void Reset();
	void SetPosition(float time);
	void Record();
	void Pause();
};

