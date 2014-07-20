#include "CompositionLayer.h"


CompositionLayer::CompositionLayer(
		PooledFactory<CircleVisualization>& CircleFactory,
		ofVec2f screenDimensions) 
	: Visuals(new VisualizationLayer(CircleFactory, screenDimensions))
{
	Gestures.Initialize(Visuals.get());

	Player.RegisterReceiver(Visuals.get());
	Player.RegisterReceiver(&Gestures);
}

CompositionLayer::~CompositionLayer()
{
	Visuals->Clear();
}

CompositionLayer::State CompositionLayer::GetState()
{
	return CurrentState;
}

void CompositionLayer::SetState(State newState)
{
	CurrentState = newState;
}

void CompositionLayer::Truncate(float time)
{
	Player.Truncate(time);
	Replay();
}

void CompositionLayer::Replay()
{
	Visuals->Clear();
	Player.Replay(Visuals);
}

void CompositionLayer::SetPosition(float time)
{
	Visuals->Clear();
	Pause();
	Player.SetPosition(time);
}

void CompositionLayer::Play()
{
	SetState(Playing);
}

void CompositionLayer::Record(const Event& event)
{
	Player.Record(event);

	Gestures.OnEvent(event);
	Visuals->OnEvent(event);

	SetState(Recording);
}

void CompositionLayer::Reset()
{
	Player.Clear();
	Visuals->Clear();
}

void CompositionLayer::Pause()
{
	SetState(Paused);
}

void CompositionLayer::Update(float dt)
{
	if (CurrentState == Playing)
	{
		Player.Play(dt);
	}
}

void CompositionLayer::Draw()
{
	Visuals->Draw();
}
