#include "CBApp.h"
#include "PCH.h"


CBApp::CBApp()
	: CircleFactory(MAX_CIRCLE_VISUALIZATIONS), CurrentLayer(CircleFactory)
{
	CurrentState = Recording;
}

CBApp::~CBApp()
{
}

void CBApp::Initialize()
{
}

void CBApp::PostEvent(const Event& Event)
{
	switch (CurrentState)
	{
	case Playing: return;

	case Recording: 
		Player.Record(Event);
		CurrentLayer.OnEvent(Event);
		break;
	}
}

void CBApp::Update(float dt)
{
	Player.Update(dt);

	switch (CurrentState)
	{
	case Playing: 
		if (Player.GetState() == EventPlayer::Recording)
		{
			SetState(Recording);
		}
		return;

	case Recording: 
		Event timePassed;
		timePassed.Type = Event::TimePassed;
		timePassed.Value.TimePassed.DeltaTime = dt;

		Player.Record(timePassed);
		CurrentLayer.OnEvent(timePassed);
		break;
	}
}

void CBApp::Draw()
{
	CurrentLayer.Draw();
}

void CBApp::StartRecording()
{
	assert(CurrentState == Recording);

	CurrentLayer.Clear();
	Player.Clear();
	SetState(Recording);
}

void CBApp::PlayRecording()
{
	assert(CurrentState == Recording);

	CurrentLayer.Clear();
	Player.StartPlayback(0.0f, &CurrentLayer);
	SetState(Playing);
}

