#include "CBApp.h"
#include "PCH.h"
#include <vector>
#include "ofMain.h"




#define MAX_CIRCLE_VISUALIZATIONS 1000
#define MAX_LAYERS 100

CBApp::CBApp()
	: CircleFactory(MAX_CIRCLE_VISUALIZATIONS)
{
	Layers.reserve(MAX_LAYERS);
	CurrentState = Idle;
}


CBApp::~CBApp()
{
}

void CBApp::Initialize()
{
    SoundPlayer.loadSound("now.m4a", true);
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
	case Playing:
    case Idle:
            return;

	case Recording: 
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
	case Idle:
		break;

	case Playing: 
		if (CurrentLayer().GetState() == EventPlayer::Idle)
		{
			SetState(Idle);
		}
		break;

	case Recording: 
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
	if (CurrentState != Idle)
	{
		Stop();
	}

	PlayAllLayers();
	CreateNewLayer();

	SetState(Recording);
}

void CBApp::PlayAllLayers()
{

    SoundPlayer.play();
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Play(0.0f);
	}
}

void CBApp::Play()
{
	if (CurrentState != Idle)
	{
		Stop();
	}


	PlayAllLayers();
	SetState(Playing);
}

void CBApp::Reset()
{
    Stop();
	Layers.clear();
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
    SoundPlayer.stop();
    SoundPlayer.setPosition(0.0);
    StopAllLayers();
    SetState(Idle);
}
