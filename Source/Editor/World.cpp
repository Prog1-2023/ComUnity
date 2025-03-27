#include "World.h"

World::World()
{
	allActors = vector<Actor*>();
	window = nullptr;
}

World::~World()
{
	for (Actor* _actor : allActors)
	{
		delete _actor;
		_actor = nullptr;
	}
}

LightActor* World::SpawnLight(LightType _type)
{
	LightActor* _light = SpawnActor<LightActor>();
	_light->SetType(_type);
	return _light;
}
