#include "CircleVisualization.h"
#include "of3dPrimitives.h"

#define STARTING_ALPHA (255.f)
#define CIRCLE_RESOLUTION 100
#define CIRCLE_RADIUS 50.f


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

float tween(float time, float startTime, float endTime, float startValue, float endValue, float value)
{
	return (endValue - startValue)/(endTime - startTime) * (time - startTime) * value;
}

void CircleVisualization::TweenAlpha(float time)
{
	CurrentAlpha = STARTING_ALPHA * (1 - (CurrentTime / VisibleDuration));
}

void CircleVisualization::TweenRadius(float time)
{
	CurrentRadius = tween(time,CurrentTime,CurrentTime + VisibleDuration, 1,0, CIRCLE_RADIUS);
}

void CircleVisualization::ExpandContractToZero(float time)
{
	CurrentRadius = CIRCLE_RADIUS * (1 - (CurrentTime / VisibleDuration));
	CurrentAlpha = STARTING_ALPHA * (1 - (CurrentTime / VisibleDuration));
}

void CircleVisualization::Update(float dt)
{
	if (_Done) return;

	CurrentTime += dt;

	if (CurrentTime >= VisibleDuration) _Done = true;

	TweenAlpha(CurrentTime);
	TweenRadius(CurrentTime);
}

void CircleVisualization::Draw()
{
	ofSetColor(InitialColor, CurrentAlpha);
	ofSetCircleResolution(CIRCLE_RESOLUTION);
	ofCircle(Position.x, Position.y, CurrentRadius);
}