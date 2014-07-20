#pragma once

#include "of3dPrimitives.h"
#include "PooledFactory.h"
#include "../tween/ofxTween.h"
#include "IGestureConsumer.h"

class CircleVisualization : public Poolable, public IDragGestureConsumer
{

	bool	_Done;

	ofVec2f Position;
	ofColor InitialColor;
	float 	InitialRadius;

	float	CurrentTime;
	float	CurrentAlpha;
	float	CurrentRadius;

	ofxTween tweenQuart;
	ofxEasingExpo easingExpo;
	ofxEasingQuad easingQuad;

	void TweenAlpha(float time);
	void TweenRadius(float time);
	void ExpandContractToFixed(float time);
public:

	CircleVisualization();

	void Initialize(
		ofVec2f position, 
		float radius, 
		ofColor color,
		float startTime = 0.0f);

	bool Done()			{ return _Done; }

	void Update(float dt);
	void Draw();

	virtual void OnUpdateDrag(ofVec2f position, float pressure);
	virtual void OnEndDrag(ofVec2f position, float pressure) {}
};

