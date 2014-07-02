#pragma once
#include "VisualizationLayer.h"
#include "EventPlayer.h"
#include "ofMain.h"

class CompositionLayer
{
public:

	enum State
	{
		Paused,
		Playing,
		Recording
	};

private:

	ofPtr<VisualizationLayer> 	Visuals;
	EventPlayer 				Player;	
	State 						CurrentState;

	void Replay();
	void SetState(State state);

	CompositionLayer(const CompositionLayer& other) {}

public:
	CompositionLayer(
			PooledFactory<CircleVisualization>& CircleFactory,
			ofVec2f screenDimensions);

	~CompositionLayer();

	State GetState();

	void SetPosition(float time);
	void Play();
	void Truncate(float time);
	void Record(const Event& event);
	void Reset();
	void Pause();

	void Update(float dt);
	void Draw();
};

