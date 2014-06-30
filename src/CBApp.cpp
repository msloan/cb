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
	PlayFromTime = 0.0f;
}


CBApp::~CBApp()
{
}

void CBApp::Initialize()
{
    SoundPlayer.loadSound("now.mp3", true);
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
	switch (CurrentState)
	{
	case Idle:
		UpdateLayers(dt);
		break;
	case LoadingNewPosition:
		if (SoundPlayer.isLoaded())
		{
			if (NextState ==  Playing)
			{
				SoundPlayer.play();
				PlayAllLayers(PlayFromTime);
			}
			else if (NextState == Recording)
			{
				SoundPlayer.play();
				PlayAllLayers(PlayFromTime);
				CreateNewLayer();
			}
			SetState(NextState);
		}
		break;

	case Playing: 
		UpdateLayers(dt);
		if (CurrentLayer().GetState() == EventPlayer::Idle)
		{
			SetState(Idle);
		}
		break;

	case Recording: 
		UpdateLayers(dt);
		Event timePassed;
		timePassed.Type = Event::TimePassed;
		timePassed.Value.TimePassed.DeltaTime = dt;

		PostEvent(timePassed);
		break;
	}
}

void CBApp::Draw()
{
	ofClear(ofColor::black);
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

	SetPositionAndTransition(0.0f, Recording);
}

void CBApp::SetPosition(float time)
{
	SetPositionAndTransition(time, Idle);
}

void CBApp::SetPositionAndTransition(float time, State nextState)
{
	NextState = nextState;
	PlayFromTime = time;
    SoundPlayer.setPosition(time);
	SetState(LoadingNewPosition);
}

void CBApp::PlayAllLayers(float time)
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Play(time);
	}
}

void CBApp::Play()
{
	if (CurrentState != Idle)
	{
		Stop();
	}

	SetPositionAndTransition(0.0f, Playing);
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
    StopAllLayers();
    SetState(Idle);
}
