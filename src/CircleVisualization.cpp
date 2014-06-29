#include "CircleVisualization.h"
#include "of3dPrimitives.h"

#define STARTING_ALPHA (255.f)
#define CIRCLE_RESOLUTION 100
#define CIRCLE_RADIUS 40.f


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
	CurrentRadius = radius;
	InitialColor = color;
	VisibleDuration = visibleDuration;
	CurrentTime = 0.0f;
	_Done = false;

	TweenAlpha(startTime);
}

//Returns a value between startScale and endScale scaling linearly with time.
float tween(float time, float endTime, float startScale, float endScale)
{
	return startScale + time / endTime * (endScale - startScale);
}

void CircleVisualization::TweenAlpha(float time)
{
	CurrentAlpha = STARTING_ALPHA * (1 - (time / (VisibleDuration - VisibleDuration/2.f)));
}

void CircleVisualization::ExpandContractToFixed(float time)
{
	float contractTime;
	float fixedTime;
	if(time < (contractTime = VisibleDuration / 17.f))
	{
		CurrentRadius = tween(time, contractTime, 1, 1.10) * CIRCLE_RADIUS;
	}
	else if(time < (fixedTime = VisibleDuration / 3.0f))
	{
		CurrentRadius = tween(time, fixedTime, 1.10, 0.4) * CIRCLE_RADIUS;
	}
	else
	{
		CurrentRadius = 0.4 * CIRCLE_RADIUS;
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