#include "CompositionLayer.h"

CompositionLayer::CompositionLayer(
		PooledFactory<CircleVisualization>& CircleFactory,
		ofVec2f screenDimensions)
: Visuals(CircleFactory, screenDimensions)
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

void CompositionLayer::Truncate(float time)
{
	Player.Truncate(time);
	Replay();
}

void CompositionLayer::Replay()
{
	Visuals.Clear();
	Player.Replay(&Visuals);
}

void CompositionLayer::SetPosition(float time)
{
	Player.SetPosition(time);
	Replay();
}

void CompositionLayer::Play()
{
	Player.Play(&Visuals);
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
