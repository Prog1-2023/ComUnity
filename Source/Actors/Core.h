#pragma once
#include "../Utils/CoreMinimal.h"


class Level;
class Core
{
	bool isActive = false;

protected:
	Level* world;


public:
	FORCEINLINE Level* GetWorld()
	{
		return world;
	}


	FORCEINLINE virtual void SetActive(const bool _active)
	{
		isActive = _active;
	}
	FORCEINLINE bool IsActive() const
	{
		return isActive;
	}
public:
	Core() {};
	Core(Level* _world);
public:
	virtual void Construct() = 0;
	virtual void Deconstruct() = 0;
	virtual void BeginPlay() = 0;
	virtual void Tick(const float _deltaTime) = 0;
	virtual void BeginDestroy() = 0;
};