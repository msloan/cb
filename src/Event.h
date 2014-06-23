#pragma once

#include "of3dPrimitives.h"
struct Event
{
	enum Type {
		TouchDown,
		TouchUp,
		TouchMove,
		
		TimePassed
	} Type;

	union Value
	{
		struct Touch
		{
			int 	Id;
			float	x;
			float	y;
		} Touch;


		struct TimePassed
		{
			float   DeltaTime;
		} TimePassed;
	} Value;

};

