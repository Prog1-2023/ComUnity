#pragma once
#include "../Utils/CoreMinimal.h"

class Component
{
	class Actor* owner;
public:
	Component(Actor* _owner);
	virtual ~Component() { };

public:
	virtual void BeginPlay() {};
	virtual void Tick(const float _deltatime) {};
	virtual void BeginDestroy() {};
};

