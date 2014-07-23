#pragma once
#include <vector>
#include "PooledFactory.h"
#include "IEventReceiver.h"
#include "IGestureConsumer.h"

class CircleVisualization;


class VisualizationLayer : public IEventReceiver, public IGestureConsumer
{
	PooledFactory<CircleVisualization>* CircleFactory;
	std::vector<CircleVisualization*> Circles;

	ofVec2f CanvasDimensions;

	ofVec2f ConvertToScreenSpace(const ofVec2f& normalized);
public:
	VisualizationLayer(
			PooledFactory<CircleVisualization>* circleFactory,
			const ofVec2f& screenDimensions);

	void OnEvent(const Event& Event);
	void Update(float dt);
	void Draw();

	virtual void OnSingleTap(ofVec2f position, float pressure);

	virtual ofPtr<IDragGestureConsumer> OnStartDrag(ofVec2f position, float pressure);



	void Clear();
};

