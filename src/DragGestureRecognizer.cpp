#include "DragGestureRecognizer.h"

void DragGestureRecognizer::Initialize(IGestureConsumer* consumer)
{
}

void DragGestureRecognizer::OnTouchDown(Touch touch, float currentTime)
{
	StartMonitoringTouch(touch);
}

void DragGestureRecognizer::OnTouchUp(Touch touch, float currentTime)
{
}

void DragGestureRecognizer::OnTouchMoved(Touch touch, float currentTime) 
{
}

void DragGestureRecognizer::Update(float secondsPassed) 
{
}
