#include "PCH.h"
#include "VisualizationLayer.h"

#define CIRCLE_RADIUS_MODIFIER (1.f / (500.f))

VisualizationLayer::VisualizationLayer(
		PooledFactory<CircleVisualization>& circleFactory,
		const ofVec2f& canvasDimensions)
	: CircleFactory(circleFactory), CanvasDimensions(canvasDimensions)
{
}


VisualizationLayer::~VisualizationLayer()
{
}


void VisualizationLayer::OnEvent(const Event& event)
{
	if (event.Type == Event::TouchDown)
	{
		ofVec2f position(
				event.Value.Touch.x * CanvasDimensions.x,
				event.Value.Touch.y * CanvasDimensions.y);

		CircleVisualization* newCircle = CircleFactory.Create();
		newCircle->Initialize(
			position,
			CIRCLE_RADIUS_MODIFIER * CanvasDimensions.y * event.Value.Touch.Pressure,
            ofColor::yellow,
			0.0f);

		Circles.push_back(newCircle);
	}
	else if (event.Type == Event::TimePassed)
	{
		Update(event.Value.TimePassed.DeltaTime);
	}
}

void VisualizationLayer::Update(float dt)
{
	for (int i = 0; i < Circles.size(); i++)
	{
		CircleVisualization& circle = *(Circles[i]);
		if (circle.Done())
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

void VisualizationLayer::Draw()
{
	for (int i = 0; i < Circles.size(); i++)
	{
		Circles[i]->Draw();
	}
}

void VisualizationLayer::Clear()
{
	for (int i = 0; i < Circles.size(); i++)
	{
		Circles[i]->Release();
	}
	Circles.clear();
}
