#pragma once
#include "CircleVisualization.h"
#include "EventPlayer.h"

class VisualizationLayer : public IEventReceiver
{
	PooledFactory<CircleVisualization> CircleFactory;
	std::vector<CircleVisualization*> Circles;

	ofVec2f CanvasDimensions;

public:
	VisualizationLayer(
			PooledFactory<CircleVisualization>& circleFactory,
			const ofVec2f& screenDimensions);

	~VisualizationLayer();

	void OnEvent(const Event& Event);
	void Update(float dt);
	void Draw();

	void Clear();
};

