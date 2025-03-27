#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"
#include "Windows/Window.h"
#include "../Actors/Lights/LightActor.h"

using namespace std;

class World
{
	vector<Actor*> allActors;
	Window* window;

public:
	FORCEINLINE vector<Actor*> GetAllActors() const
	{
		return allActors;
	}
	FORCEINLINE void SetWindow(Window* _window)
	{
		window = _window;
	}
	FORCEINLINE Window* GetWindow()
	{
		return window;
	}

public:
	World();
	World(Window* _window);
	~World();

public:
	void Start();
	void Update();
	void Stop();

	LightActor* SpawnLight(LightType _type);
public:
	template<typename Type = Actor>
	Type* SpawnActor()
	{
		Type* _actor = new Type(this);
		allActors.push_back(_actor);
		return _actor;
	}
};