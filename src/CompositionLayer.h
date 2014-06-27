#pragma once
#include "VisualizationLayer.h"
#include "EventPlayer.h"

class CompositionLayer
{
	VisualizationLayer 	Visuals;
	EventPlayer 		Player;	

public:
	CompositionLayer(PooledFactory<CircleVisualization>& CircleFactory);
	~CompositionLayer();

	EventPlayer::State GetState();
	void Play(float startTime);
	void Record(const Event& event);
	void Reset();
	void Stop();

	void Update(float dt);
	void Draw();
};

