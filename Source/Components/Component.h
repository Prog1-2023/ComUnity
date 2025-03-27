#pragma once
#include "../Utils/CoreMinimal.h"

class Component
{
protected:
	class Actor* owner;

public:
	FORCEINLINE Actor* GetOwner() const { return owner; }

public:
	Component(Actor* _actor);
	virtual ~Component() {};

public:
	virtual void BeginPlay() {};
	virtual void Tick(const float& _deltaTime) {};
	virtual void BeginDestroy() {};
};

