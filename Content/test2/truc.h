#pragma once

#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"

class truc : public Actor
{

public:
	truc();
	~truc();

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(const float _deltatime) override;
};
