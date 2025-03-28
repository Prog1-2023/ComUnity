#pragma once
#include "CoreMinimal.h"

template <typename T>
class Singleton
{
public:
	__forceinline static T& GetInstance()
	{
		static T _instance;
		return _instance;
	}
};