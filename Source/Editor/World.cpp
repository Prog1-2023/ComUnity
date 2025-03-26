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
	}
}
