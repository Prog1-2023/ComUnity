#pragma once
#include "../Utils/CoreMinimal.h"
#include <any>

class Component
{
public:
	class Actor* owner;
public:
	Component(Actor* _owner);
	virtual ~Component() { };

public:
	virtual void BeginPlay() {};
	virtual void Tick(const float _deltatime) {};
	virtual void BeginDestroy() {};

	virtual vector<std::any> GenerateSerialization()
	{
		return vector<std::any>();
	}
};

