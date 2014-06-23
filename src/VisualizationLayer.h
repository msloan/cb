#pragma once
#include "CircleVisualization.h"
#include "EventPlayer.h"

class VisualizationLayer : public IEventReceiver
{
	PooledFactory<CircleVisualization> CircleFactory;
	std::vector<CircleVisualization*> Circles;

public:
	VisualizationLayer(PooledFactory<CircleVisualization>& circleFactory);

	~VisualizationLayer();

	void OnEvent(const Event& Event);
	void Update(float dt);
	void Draw();

	void Clear();
};

