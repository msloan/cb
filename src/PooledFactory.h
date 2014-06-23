#pragma once
#include <vector>
#include <assert.h>

class Poolable
{
	bool _Aquired;

public:

	Poolable() 
	{ 
		_Aquired = false;
	}


	void Aquire()
	{
		assert(!_Aquired);
		_Aquired = true;
	}

	void Release()
	{
		assert(_Aquired);
		_Aquired = false;
	}

	bool Aquired() { return _Aquired; }
};

template <typename TPooled>
class PooledFactory
{
	std::vector<TPooled> Pool;

public:
	PooledFactory(int initialCapacity)
		: Pool(initialCapacity) 
	{ }

	TPooled* Create()
	{
		for (int i = 0; i < Pool.size(); i++)
		{
			TPooled& item = Pool[i];
			if (!item.Aquired())
			{
				item.Aquire();
				return &item;
			}
		}
		assert(0);
		return NULL;
	}
};


