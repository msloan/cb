#include "CircleVisualization.h"
#include "of3dPrimitives.h"

#define STARTING_ALPHA (255.f)
#define CIRCLE_RESOLUTION 100

#define DURATION 1.f
#define CONTRACT_TIME (DURATION / 15.f)
#define MAX_RADIUS 1.3f

CircleVisualization::CircleVisualization()
{

}

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
	_Done = false;

	
	_Done = false;
}

void CircleVisualization::Drag(float x, float y)
{
	Position = ofVec2f(x,y);
	CurrentTime = 0;
}

void CircleVisualization::TweenAlpha(float time)
{
	CurrentAlpha = ofxTween::map(time, 0.f, DURATION, STARTING_ALPHA, 0, false, easingQuad, ofxTween::easeOut);
}

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

void CircleVisualization::Update(float dt)
{
	if (_Done) return;

	CurrentTime += dt;

	if (CurrentTime >= DURATION) _Done = true;

	TweenAlpha(CurrentTime);
	ExpandContractToFixed(CurrentTime);
}

void CircleVisualization::Draw()
{
	ofSetColor(InitialColor, CurrentAlpha);
	ofSetCircleResolution(CIRCLE_RESOLUTION);
	ofCircle(Position.x, Position.y, CurrentRadius);
}

