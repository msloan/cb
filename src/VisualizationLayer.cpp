#include "VisualizationLayer.h"
#include "CircleVisualization.h"
#include "Event.h"

#define CIRCLE_RADIUS_MODIFIER (1.f / (500.f))

class CircleUpdater : public IDragGestureConsumer
{
	ofVec2f CanvasDimensions;
	CircleVisualization* Circle;

public:
	CircleUpdater(const ofVec2f& canvasDimensions, CircleVisualization* circle)
		: CanvasDimensions(canvasDimensions), Circle(circle)
	{
	}

	virtual void UpdateDrag(ofVec2f position, float pressure)
	{
		ofVec2f modifiedPosition(
				position.x * CanvasDimensions.x,
				position.y * CanvasDimensions.y);

		Circle->SetPosition(modifiedPosition);
		Circle->SetSize(pressure);
	}

	virtual void EndDrag(ofVec2f position, float pressure) 
	{
		ofVec2f modifiedPosition(
				position.x * CanvasDimensions.x,
				position.y * CanvasDimensions.y);

		Circle->StartFadeOutAnimation(modifiedPosition);
	}
};

//---------------------------------------------------------------------
VisualizationLayer::VisualizationLayer(
		PooledFactory<CircleVisualization>* circleFactory,
		const ofVec2f& canvasDimensions)
	:CanvasDimensions(canvasDimensions)
{
	CircleFactory = circleFactory;
}

//---------------------------------------------------------------------
ofPtr<IDragGestureConsumer> VisualizationLayer::OnStartDrag(ofVec2f position, float pressure)
{
	ofVec2f modifiedPosition(
				position.x * CanvasDimensions.x,
				position.y * CanvasDimensions.y);

	CircleVisualization* newCircle = CircleFactory->Create();
	newCircle->Initialize(
			modifiedPosition,
			CIRCLE_RADIUS_MODIFIER * CanvasDimensions.y * pressure,
			ofColor::yellow,
			0.0f);

	Circles.push_back(newCircle);
	return ofPtr<IDragGestureConsumer>(
			new CircleUpdater(CanvasDimensions, newCircle));
}

//---------------------------------------------------------------------
ofVec2f VisualizationLayer::ConvertToScreenSpace(const ofVec2f& position)
{
	return ofVec2f(
			position.x * CanvasDimensions.x,
			position.y * CanvasDimensions.y);
}

//---------------------------------------------------------------------
void VisualizationLayer::OnSingleTap(ofVec2f position, float pressure)
{
	ofVec2f modifiedPosition = ConvertToScreenSpace(position);

	CircleVisualization* newCircle = CircleFactory->Create();
	newCircle->Initialize(
			modifiedPosition,
			CIRCLE_RADIUS_MODIFIER * CanvasDimensions.y * pressure,
			ofColor::yellow,
			0.0f);

	Circles.push_back(newCircle);
	newCircle->StartFadeOutAnimation(modifiedPosition);
}

//---------------------------------------------------------------------
void VisualizationLayer::OnEvent(const Event& event)
{
	if (event.Type == Event::TimePassed)
	{
		Update(event.Value.TimePassed.DeltaTime);
	}
}

//---------------------------------------------------------------------
void VisualizationLayer::Update(float dt)
{
	for (int i = 0; i < Circles.size(); i++)
	{
		CircleVisualization& circle = *(Circles[i]);
		if (circle.IsDone())
		{
			circle.Release();
			Circles.erase(Circles.begin() + i);
		}
		else
		{
			circle.Update(dt);
		}
	}
}

//---------------------------------------------------------------------
void VisualizationLayer::Draw()
{
	for (int i = 0; i < Circles.size(); i++)
	{
		Circles[i]->Draw();
	}
}

//---------------------------------------------------------------------
void VisualizationLayer::Clear()
{
	for (int i = 0; i < Circles.size(); i++)
	{
		Circles[i]->Release();
	}
	Circles.clear();
}
