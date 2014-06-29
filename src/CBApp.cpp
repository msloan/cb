#include "CBApp.h"
#include "PCH.h"
#include <vector>
#include "ofAppRunner.h"


#define MAX_CIRCLE_VISUALIZATIONS 1000
#define MAX_LAYERS 100

CBApp::CBApp()
	: CircleFactory(MAX_CIRCLE_VISUALIZATIONS)
{
	Layers.reserve(MAX_LAYERS);
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
		if (x < 0.05f && y <0.05f)
		{
			RecordNewLayer();
			return true;
		}
		else if (x > 0.9f && y > 0.9f)
		{
			Stop();
			Play();		
			return true;
		}
		else if (x > 0.9f && y < 0.05f)
		{
			Reset();		
			return true;
		}
		else if (x < 0.1f && y > 0.9f)
		{
			Stop();
			return true;
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
		CurrentLayer().Record(event);
		break;
	}
}

void CBApp::UpdateLayers(float dt)
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Update(dt);
	}
}

void CBApp::Update(float dt)
{
	UpdateLayers(dt);

	switch (CurrentState)
	{
	case State::Idle:
		break;

	case State::Playing: 
		if (CurrentLayer().GetState() == EventPlayer::Idle)
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
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Draw();
	}
}

void CBApp::CreateNewLayer()
{
	assert(Layers.size() < MAX_LAYERS);

	CompositionLayer layer = CompositionLayer(
		CircleFactory,
		ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));

	Layers.push_back(layer);
}

void CBApp::RecordNewLayer()
{
	if (CurrentState != State::Idle)
	{
		Stop();
	}

	PlayAllLayers();
	CreateNewLayer();

	SetState(Recording);
}

void CBApp::PlayAllLayers()
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Play(0.0f);
	}
}

void CBApp::Play()
{
	if (CurrentState != State::Idle)
	{
		Stop();
	}

	PlayAllLayers();
	SetState(Playing);
}

void CBApp::Reset()
{
	Layers.clear();
	SetState(Idle);
}

void CBApp::StopAllLayers()
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Stop();
	}
}

void CBApp::Stop()
{
	SetState(State::Idle);
}
