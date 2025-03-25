#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"

class UIElement
{

public:
	UIElement() = default;
	virtual ~UIElement() = default;

public:
	virtual void Draw() = 0;
};
