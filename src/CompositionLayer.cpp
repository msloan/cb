#include "CompositionLayer.h"

CompositionLayer::CompositionLayer(PooledFactory<CircleVisualization>& CircleFactory)
: Visuals(CircleFactory)
{
}

CompositionLayer::~CompositionLayer()
{
	Visuals.Clear();
}

EventPlayer::State CompositionLayer::GetState()
{
	return Player.GetState();
}

void CompositionLayer::Play(float startTime)
{
	Player.Stop();
	Player.StartPlayback(startTime, &Visuals);
}

void CompositionLayer::Record(const Event& event)
{
	Player.Record(event);
	Visuals.OnEvent(event);
}

void CompositionLayer::Reset()
{
	Player.Clear();
	Visuals.Clear();
}

void CompositionLayer::Stop()
{
	Visuals.Clear();
	Player.Stop();
}

void CompositionLayer::Update(float dt)
{
	Player.Update(dt);
}

void CompositionLayer::Draw()
{
	Visuals.Draw();
}
