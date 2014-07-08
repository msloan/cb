#pragma once

#include "of3dPrimitives.h"
struct Event
{
	enum Type {
		TouchDown,
		TouchUp,
		TouchMove,
		
		GestureRecognized,

		GestureBegin,
		GestureChanged,
		GestureEnd,

		TimePassed
	} Type;

	union Value
	{
		struct Touch
		{
			int 	Id;
			float	x;
			float	y;
            float   Pressure;
		} Touch;


		struct TimePassed
		{
			float   DeltaTime;
		} TimePassed;
	} Value;

};

