#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"

class UIElement : public Actor
{
protected:
	string name;

public:
	UIElement(World* _world,const string& _name);
	~UIElement();

public:
	virtual void Draw() = 0;
};
