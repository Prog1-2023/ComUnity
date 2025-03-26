#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"
#include "Windows/Window.h"

class World
{
	vector<Actor*> allActors;
	Window* window;

public:
	FORCEINLINE void SetWindow(Window* _window)
	{
		window = _window;
	}
	FORCEINLINE Window* GetWindow()
	{
		return window;
	}
	FORCEINLINE vector<Actor*> GetAllActors() const
	{
		return allActors;
	}

public:
	World();
	~World();

private:

public:
	template<typename Type = Actor>
	Type* SpawnActor()
	{
		Type* _actor = new Type(this);
		allActors.push_back(_actor);
		return _actor;
	}
};

