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
	World();
	World(Window* _window);
	~World();

public:
	FORCEINLINE vector<Actor*> GetAllActors() const
	{
		return allActors;
	}
public:
	void Start();
	void Update();
	void Stop();

public:
	template<typename Type = Actor>
	Type* SpawnActor()
	{
		Type* _actor = new Type(this);
		allActors.push_back(_actor);
		return _actor;
	}

	//LightActor* SpawnLight(LightType _type);
};
