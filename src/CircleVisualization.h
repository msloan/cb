#pragma once

#include "of3dPrimitives.h"
#include "PooledFactory.h"

class CircleVisualization : public Poolable
{

	bool	_Done;

	ofVec2f Position;
	ofColor InitialColor;
	float	VisibleDuration;

	float	CurrentTime;
	float	CurrentAlpha;
	float	CurrentRadius;

	void TweenAlpha(float time);
	void TweenRadius(float time);
	void ExpandContractToFixed(float time);
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

