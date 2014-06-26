#include "CBApp.h"
#include "PCH.h"
#include <vector>
#include "ofAppRunner.h"


#define MAX_CIRCLE_VISUALIZATIONS 1000
#define MAX_LAYERS 100

CBApp::CBApp()
	: CircleFactory(MAX_CIRCLE_VISUALIZATIONS)
{
	VisualizationLayers.reserve(MAX_LAYERS);
	EventPlayers.reserve(MAX_LAYERS);
	CurrentState = State::Idle;
}


CBApp::~CBApp()
{
}

void CBApp::Initialize()
{
}

bool CBApp::DebugButtonPressed(const Event& event)
{
	float x = event.Value.Touch.x;
	float y = event.Value.Touch.y;
	if (event.Type == Event::TouchDown)
	{
		if (x < 100 && y <100)
		{
			RecordNewLayer();
			return true;
		}
		else if (x > 0.9f * ofGetWidth() && y > 0.9f *ofGetHeight())
		{
			Stop();
			Play();		
			return true;
		}
		else if (x > 0.9f * ofGetWidth() && y < 100)
		{
			Reset();		
			return true;
		}
		else if (x < 0.1f * ofGetWidth() && y > 0.9f * ofGetHeight())
		{
			Stop();
		}
	}
	return false;
}
void CBApp::PostEvent(const Event& event)
{
	if (DebugButtonPressed(event)) return;

	switch (CurrentState)
	{
	case State::Playing: return;

	case State::Recording: 
		CurrentPlayer().Record(event);
		CurrentLayer().OnEvent(event);
		
		break;
	}
}

void CBApp::UpdatePlayers(float dt)
{
	for (int i = 0; i < EventPlayers.size(); ++i)
	{
		EventPlayers[i].Update(dt);
	}
}

void CBApp::Update(float dt)
{
	UpdatePlayers(dt);

	switch (CurrentState)
	{
	case State::Idle:
		break;

	case State::Playing: 
		if (CurrentPlayer().GetState() == EventPlayer::Idle)
		{
			SetState(State::Idle);
		}
		break;

	case State::Recording: 
		Event timePassed;
		timePassed.Type = Event::TimePassed;
		timePassed.Value.TimePassed.DeltaTime = dt;

		PostEvent(timePassed);
		break;
	}
}

void CBApp::Draw()
{
	for (int i = 0; i < VisualizationLayers.size(); ++i)
	{
		VisualizationLayers[i].Draw();
	}
}

void CBApp::CreateNewLayer()
{
	assert(VisualizationLayers.size() < MAX_LAYERS);

	VisualizationLayers.push_back(VisualizationLayer(CircleFactory));
	EventPlayers.push_back(EventPlayer());
}

void CBApp::RecordNewLayer()
{
	if (CurrentState != State::Idle)
	{
		Stop();
	}

	PlayAllPlayers();
	CreateNewLayer();

	SetState(Recording);
}

void CBApp::PlayAllPlayers()
{
	for (int i = 0; i < EventPlayers.size(); ++i)
	{
		EventPlayers[i].StartPlayback(0.0f, &(VisualizationLayers[i]));
	}
}

void CBApp::Play()
{
	if (CurrentState != State::Idle)
	{
		Stop();
	}

	PlayAllPlayers();
	SetState(Playing);
}

void CBApp::Reset()
{
	ClearAllLayers();
	EventPlayers.clear();

	SetState(Idle);
}

void CBApp::ClearAllLayers()
{
	for (int i = 0; i < VisualizationLayers.size(); ++i)
	{
		VisualizationLayers[i].Clear();
	}
}

void CBApp::StopAllPlayers()
{
	for (int i = 0; i < EventPlayers.size(); ++i)
	{
		EventPlayers[i].Stop();
	}
}

void CBApp::Stop()
{
	ClearAllLayers();
	StopAllPlayers();
	SetState(State::Idle);
}
