#pragma once

#include "of3dPrimitives.h"
#include "PooledFactory.h"
#include "../tween/ofxTween.h"
#include "IGestureConsumer.h"

class CircleVisualization : public Poolable
{
	enum State
	{
		Idle,
		FadingOut,
		Done
	};

	ofVec2f Position;
	ofColor InitialColor;
	float 	InitialRadius;

	float	CurrentTime;
	float	CurrentAlpha;
	float	CurrentRadius;

	ofxTween tweenQuart;
	ofxEasingExpo easingExpo;
	ofxEasingQuad easingQuad;

	void UpdateFadingOutAnimation(float dt);

	void TweenAlpha(float time);
	void TweenRadius(float time);
	void ExpandContractToFixed(float time);

	State CurrentState;
	void SetState(State nextState) { CurrentState = nextState; }
public:

	CircleVisualization();

	void Initialize(
		ofVec2f position, 
		float radius, 
		ofColor color,
		float startTime = 0.0f);

	bool IsDone()			{ return CurrentState == Done; }

	void Update(float dt);
	void Draw();

	void SetPosition(ofVec2f position);
	void SetSize(float size);
	void StartFadeOutAnimation(ofVec2f position);
};

