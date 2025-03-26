#pragma once

#include "../Utils/CoreMinimal.h"

class Actor;

class Component
{
protected:
	Actor* owner;

public:
	Component(Actor* _owner);
	virtual ~Component();

public:
	virtual void BeginPlay() {};
	virtual void Tick(const float& _deltaTime) {};
	virtual void BeginDestroy() {};
};
