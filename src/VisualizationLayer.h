#pragma once
#include "CircleVisualization.h"
#include "EventPlayer.h"
#include "SingleTapGestureRecognizer.h"

class VisualizationLayer : public IEventReceiver, public ISingleTapVisualizer
{
	PooledFactory<CircleVisualization> CircleFactory;
	std::vector<CircleVisualization*> Circles;

	ofVec2f CanvasDimensions;

	SingleTapGestureRecognizer TapRecognizer;


public:
	VisualizationLayer(
			PooledFactory<CircleVisualization>& circleFactory,
			const ofVec2f& screenDimensions);

	~VisualizationLayer();

	void OnEvent(const Event& Event);
	void Update(float dt);
	void Draw();

	void OnSingleTap(ofVec2f position, float pressure);

	void Clear();
};

