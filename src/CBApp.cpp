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
}


CBApp::~CBApp()
{
}

void CBApp::Initialize()
{
    SoundPlayer.loadSound("now.mp3", true);

	SoundPlayer.play();
	Pause();

	CreateNewLayer();

	PreviousState = Paused;
	CurrentMode = mode_Edit;
}

bool CBApp::DebugButtonPressed(const Event& event)
{
	float x = event.Value.Touch.x;
	float y = event.Value.Touch.y;
	if (event.Type == Event::TouchDown)
	{
		if (x < 0.05f && y <0.05f)
		{
			Record();
			return true;
		}
		else if (x > 0.9f && y > 0.9f)
		{
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
    case Paused:
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
	case Paused:
		break;
	case LoadingNewPosition:
		if (SoundPlayer.isLoaded())
		{
			switch (PreviousState)
			{
				case Playing: 	Play(); 	break;
				case Recording: Record(); 	break;
				case Paused: 	Pause(); 	break;

				default: break;
			}
		}
		break;

	case Playing: 
		UpdateLayers(dt);
		if (CurrentLayer().GetState() == EventPlayer::Paused)
		{
			SetState(Paused);
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

void CBApp::SaveLayer()
{
	assert(Layers.size() > 0);

	CreateNewLayer();
	SetPosition(0.0f);
	Pause();
}
void CBApp::CreateNewLayer()
{
	assert(Layers.size() < MAX_LAYERS);

	CompositionLayer layer = CompositionLayer(
		CircleFactory,
		ofVec2f((float)ofGetWidth(), (float)ofGetHeight()));

	Layers.push_back(layer);
}


void CBApp::Record()
{
	SoundPlayer.setPaused(false);
	PlayAllSavedLayers();
	SetState(Recording);
}

void CBApp::Pause()
{
	SoundPlayer.setPaused(true);
	SetState(Paused);
}

void CBApp::SetPosition(float time)
{
    SoundPlayer.setPosition(time);
	SetLayersPosition(time);	
	SetState(LoadingNewPosition);
}

void CBApp::SetLayersPosition(float time)
{
	if (CurrentMode == mode_Edit)
	{
		for (int i = 0; i < Layers.size() - 1; ++i)
		{
			CompositionLayer& layer = Layers[i];
			if (&layer == &CurrentLayer())
			{
				CurrentLayer().Truncate(time);
			}
			else
			{
				Layers[i].SetPosition(time);
			}
		}
	}
	else if (CurrentMode == mode_Play)
	{
		for (int i = 0; i < Layers.size() - 1; ++i)
		{
			Layers[i].SetPosition(time);
		}
	}
}

void CBApp::PlayAllLayers()
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		Layers[i].Play();
	}
}

void CBApp::PlayAllSavedLayers()
{
	for (int i = 0; i < Layers.size(); ++i)
	{
		if (&Layers[i] != &CurrentLayer())
		{
			Layers[i].Play();
		}
	}
}

void CBApp::Play()
{
	SoundPlayer.play();
	PlayAllLayers();
}

void CBApp::Reset()
{
	Layers.clear();
}
