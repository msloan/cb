#include "CircleVisualization.h"
#include "of3dPrimitives.h"

#define STARTING_ALPHA (255.f)
#define CIRCLE_RESOLUTION 100


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
	InitialColor = color;
	VisibleDuration = visibleDuration;
	CurrentTime = 0.0f;
	_Done = false;

	TweenAlpha(startTime);
}

void CircleVisualization::TweenAlpha(float time)
{
	CurrentAlpha = STARTING_ALPHA * (1 - (CurrentTime / VisibleDuration));
}

void CircleVisualization::Update(float dt)
{
	if (_Done) return;

	CurrentTime += dt;

	if (CurrentTime >= VisibleDuration) _Done = true;

	TweenAlpha(CurrentTime);
}

void CircleVisualization::Draw()
{
	ofSetColor(InitialColor, CurrentAlpha);
	ofSetCircleResolution(CIRCLE_RESOLUTION);
	ofCircle(Position.x, Position.y, InitialRadius);
}