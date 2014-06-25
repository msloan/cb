#include "CBApp.h"
#include "PCH.h"
#include <vector>
#include "ofAppRunner.h"


#define MAX_CIRCLE_VISUALIZATIONS 1000

CBApp::CBApp()
	: CircleFactory(MAX_CIRCLE_VISUALIZATIONS), 
	CurrentLayer(CircleFactory)
{
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
			StartRecording();
			return true;
		}
		else if (x > 0.9f * ofGetWidth() && y > 0.9f *ofGetHeight())
		{
			Stop();
			PlayRecording();		
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
		Player.Record(event);
		CurrentLayer.OnEvent(event);
		break;
	}
}

void CBApp::Update(float dt)
{
	Player.Update(dt);

	switch (CurrentState)
	{
	case State::Idle:
		break;

	case State::Playing: 
		if (Player.GetState() == EventPlayer::Idle)
		{
			SetState(State::Idle);
		}
		break;

	case State::Recording: 
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
	assert(CurrentState == State::Idle);

	CurrentLayer.Clear();
	Player.Clear();
	SetState(State::Recording);
}

void CBApp::PlayRecording()
{
	assert(CurrentState == State::Idle);

	CurrentLayer.Clear();
	Player.StartPlayback(0.0f, &CurrentLayer);
	SetState(State::Playing);
}

void CBApp::Reset()
{
	CurrentLayer.Clear();
	Player.Reset();
	SetState(State::Idle);
}

void CBApp::Stop()
{
	CurrentLayer.Clear();
	Player.Stop();
	SetState(State::Idle);
}
