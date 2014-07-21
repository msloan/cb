#pragma once
#include <vector>

#include "PooledFactory.h"
#include "ofSoundPlayer.h"
#include "CircleVisualization.h"


class CompositionLayer;
struct Event;

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

private:

	PooledFactory<CircleVisualization> CircleFactory;

	std::vector<ofPtr<CompositionLayer> > Layers;
    ofSoundPlayer SoundPlayer;


	CompositionLayer& CurrentLayer() 	{ return *(Layers.back()); }
	State CurrentState;
	State PreviousState;

	void SetState(State nextState)	
	{ 
		PreviousState = CurrentState;
		CurrentState = nextState; 
	}


	bool DebugButtonPressed(const Event& event);

	void ClearAllLayers();
	void UpdateLayers(float dt);
	void PlayAllLayers();
	void PauseAllLayers();
	void SetLayersPosition(float time);

	void PlayAllSavedLayers();


	void CreateNewLayer();

public:
	CBApp::State GetState()			{ return CurrentState; }

	CBApp();
	~CBApp();

	void Initialize();
	void Update(float dt);
	void Draw();

	void PostEvent(const Event& Event);

	void SaveLayer();
	void Play();
	void Reset();
	void SetPosition(float time);
	void Record();
	void Pause();
};

