#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"

class UIElement : public Actor
{
	string name;

public:
	UIElement(World* _world,const string& _name);
	virtual ~UIElement() { };

private:
};
