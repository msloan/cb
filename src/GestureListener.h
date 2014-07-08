#pragma once

class IGestureReceiver
{
	virtual void BeginGesture(int touchId, ofVec2f startPosition, float pressure) = 0;
	virtual void UpdateGesture(int touchId, ofVec2f position, float pressure) = 0;
	virtual void EndGesture(int touchId, ofVec2f position) = 0;
};

enum GestureState
{
	Possible,
	Failed

	// Continuous gestures only
	Began,
	Changed,
	Ended,

	// Discrete gestures only
	Recognized,
}

class IGestureRecognizer
{
	virtual void Initialize(IGestureReceiver* receiver) = 0;
	virtual GestureState GetState() = 0;
	void Reset() = 0;
	bool OnEvent(const Event& event, vector<int> touchesConsumed) = 0;
	void CancelTouches(const vector<int>& canceledTouches);
	bool IsContinuous();
}

class IDiscreteGestureRecognizer : IGestureRecognizer
{
	virtual IsContinuous() { return false; }
}

class IsContinuousGestureRecognizer : IGestureRecognizer
{
	virtual IsContinuous() { return true; }
}

class DragRecognizer : IsContinuousGestureRecognizer
{
	void Initialize(IGestureReceiver* receiver);
	GestureState GetCurrentState();
	void Reset();
	void OnEvent(const Event& event);
}

class SingleTapRecognizer : IDiscreteGestureRecognizer
{
	void Initialize(IDiscreteGestureReceiver* receiver);
	GestureState GetCurrentState();
	void Reset();
	void OnEvent(const Event& event);
}

class GestureListener
{
	struct Touch
	{
		int Id;
		bool InUse;
	}
	std::vector<Event> Touches;	
	
	void OnEvent(const Event& event)
	{
		Event resultEvent;
		for (int i = 0; i < Recognizers.size(); ++i)
		{
			if (Recognizers[i]->OnEvent(event, resultEvent))
			{
				VisualizationLayer->OnGestureEvent(resultEvent);
			}
		}
	}
}
