#include "PCH.h"
#include "VisualizationLayer.h"


VisualizationLayer::VisualizationLayer(PooledFactory<CircleVisualization>& circleFactory)
	: CircleFactory(circleFactory)
{
}


VisualizationLayer::~VisualizationLayer()
{
}


void VisualizationLayer::OnEvent(const Event& event)
{
	if (event.Type == Event::TouchDown)
	{
		CircleVisualization* newCircle = CircleFactory.Create();
		newCircle->Initialize(
			ofVec2f(event.Value.Touch.x, event.Value.Touch.y),
			50.f,
			1.f,
			ofColor::blueSteel,
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