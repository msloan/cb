#include "CircleVisualization.h"
#include "of3dPrimitives.h"

#define STARTING_ALPHA (255.f)
#define CIRCLE_RESOLUTION 100

#define DURATION 1.f
#define CONTRACT_TIME (DURATION / 15.f)
#define MAX_RADIUS 1.3f

//------------------------------------------------------------------------------------
CircleVisualization::CircleVisualization()
{

}

//------------------------------------------------------------------------------------
void CircleVisualization::Initialize(
	ofVec2f position, 
	float radius, 
	ofColor color,
	float startTime)
{
	Position = position;
	InitialRadius = radius;
	InitialColor = color;

	CurrentRadius = InitialRadius;
	CurrentAlpha = STARTING_ALPHA;
	CurrentTime = 0.0f;

	CurrentState = Idle;
}

//------------------------------------------------------------------------------------
void CircleVisualization::TweenAlpha(float time)
{
	CurrentAlpha = ofxTween::map(time, 0.f, DURATION, STARTING_ALPHA, 0, false, easingQuad, ofxTween::easeOut);
}

//------------------------------------------------------------------------------------
void CircleVisualization::ExpandContractToFixed(float time)
{
	if(time < CONTRACT_TIME)
	{
		CurrentRadius = ofxTween::map(time, 0.f, CONTRACT_TIME, InitialRadius, MAX_RADIUS * InitialRadius, false, easingQuad, ofxTween::easeIn);
	}
	else
	{
		CurrentRadius = ofxTween::map(time, CONTRACT_TIME, DURATION, MAX_RADIUS * InitialRadius, 0, false, easingQuad, ofxTween::easeOut);
	}
}

//------------------------------------------------------------------------------------
void CircleVisualization::Update(float dt)
{
	if (CurrentState == Done) return;
	if (CurrentState == Idle) return;

	if (CurrentState == FadingOut)
	{
		UpdateFadingOutAnimation(dt);
	}
}

//------------------------------------------------------------------------------------
void CircleVisualization::UpdateFadingOutAnimation(float dt)
{
	CurrentTime += dt;

	if (CurrentTime >= DURATION) CurrentState = Done;

	TweenAlpha(CurrentTime);
	ExpandContractToFixed(CurrentTime);
}

//------------------------------------------------------------------------------------
void CircleVisualization::Draw()
{
	ofSetColor(InitialColor, CurrentAlpha);
	ofSetCircleResolution(CIRCLE_RESOLUTION);
	ofCircle(Position.x, Position.y, CurrentRadius);
}

//------------------------------------------------------------------------------------
void CircleVisualization::SetPosition(ofVec2f position)
{
	Position = position;
}

//------------------------------------------------------------------------------------
void CircleVisualization::SetSize(float size)
{
	// TODO
}

//------------------------------------------------------------------------------------
void CircleVisualization::StartFadeOutAnimation(ofVec2f position)
{
	SetPosition(position);

	SetState(FadingOut);
}
