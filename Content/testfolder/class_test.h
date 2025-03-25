#pragma once

#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"

class class_test : public Actor
{

public:
	class_test();
	~class_test();

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(const float _deltatime) override;
};
