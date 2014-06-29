#include "CircleVisualization.h"
#include "of3dPrimitives.h"

#define STARTING_ALPHA (255.f)
#define CIRCLE_RESOLUTION 100

#define DURATION 1.f
#define CONTRACT_TIME (DURATION / 30.f)
#define MAX_RADIUS 1.3f

CircleVisualization::CircleVisualization()
{
	_Done = false;
}

void CircleVisualization::Initialize(
	ofVec2f position, 
	float radius, 
	float visibleDuration,
	ofColor color,
	float startTime)
{
	Position = position;
	InitialRadius = radius;
	CurrentRadius = InitialRadius;
	InitialColor = color;
	VisibleDuration = visibleDuration;
	CurrentTime = 0.0f;
	_Done = false;

	TweenAlpha(startTime);
}

//Returns a value between startScale and endScale scaling linearly with time.
float Tween(float time, float endTime, float startValue, float endValue)
{
	return startValue + time / endTime * (endValue - startValue);
}

void CircleVisualization::TweenAlpha(float time)
{
	if(time >= CONTRACT_TIME)
	{
		CurrentAlpha = Tween(time, DURATION, STARTING_ALPHA, 0.f);
	}
}

void CircleVisualization::ExpandContractToFixed(float time)
{
	if(time < CONTRACT_TIME)
	{
		CurrentRadius = Tween(time, CONTRACT_TIME, InitialRadius, MAX_RADIUS * InitialRadius);
	}
	else
	{
		CurrentRadius = Tween(time, DURATION, MAX_RADIUS * InitialRadius, 0.0f);
	}
}

void CircleVisualization::Update(float dt)
{
	if (_Done) return;

	CurrentTime += dt;

	if (CurrentTime >= VisibleDuration) _Done = true;

	TweenAlpha(CurrentTime);
	ExpandContractToFixed(CurrentTime);
}

void CircleVisualization::Draw()
{
	ofSetColor(InitialColor, CurrentAlpha);
	ofSetCircleResolution(CIRCLE_RESOLUTION);
	ofCircle(Position.x, Position.y, CurrentRadius);
}
