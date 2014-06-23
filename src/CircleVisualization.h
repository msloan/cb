#pragma once

#include "of3dPrimitives.h"
#include "PooledFactory.h"

class CircleVisualization : public Poolable
{

	bool	_Done;

	ofVec2f Position;
	float	InitialRadius;
	ofColor InitialColor;
	float	VisibleDuration;

	float	CurrentTime;
	float	CurrentAlpha;

	void TweenAlpha(float time);
public:

	CircleVisualization();

	void Initialize(
		ofVec2f position, 
		float radius, 
		float visibleDuration,
		ofColor color,
		float startTime = 0.0f);

	bool Done()			{ return _Done; }

	void Update(float dt);
	void Draw();
};

