#pragma once
#include "VisualizationLayer.h"
#include "EventPlayer.h"

class CompositionLayer
{
	VisualizationLayer 	Visuals;
	EventPlayer 		Player;	

	void Replay();

public:
	CompositionLayer(
			PooledFactory<CircleVisualization>& CircleFactory,
			ofVec2f screenDimensions);

	~CompositionLayer();

	EventPlayer::State GetState();

	void SetPosition(float time);
	void Play();
	void Truncate(float time);
	void Record(const Event& event);
	void Reset();
	void Stop();

	void Update(float dt);
	void Draw();
};

