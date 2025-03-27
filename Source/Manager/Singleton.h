#pragma once
#include "../Utils/Macro.h"

template <typename T>
class Singleton
{
public:
	FORCEINLINE static T& GetInstance()
	{
		static T _instance;
		return _instance;
	}
};