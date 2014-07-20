#pragma once
#include "CircleVisualization.h"
#include "EventPlayer.h"
#include "SingleTapGestureRecognizer.h"
#include "EventPlayer.h"

class DragVisualUpdater : public IDragGestureConsumer
{
	virtual void OnUpdateDrag(ofVec2f position, float pressure)
	{
	}

	virtual void OnEndDrag(ofVec2f position, float pressure)
	{
	}
};

class VisualizationLayer : public IEventReceiver, public IGestureConsumer
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

	virtual void OnSingleTap(ofVec2f position, float pressure);

	virtual IDragGestureConsumer* OnStartDrag(ofVec2f position, float pressure)
	{
		return new DragVisualUpdater();
	}



	void Clear();
};

