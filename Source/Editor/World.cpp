#include "World.h"

World::World()
{
	allActors = vector<Actor*>();
	window = nullptr;
}

World::~World()
{
	const int& _size = static_cast<const int>(allActors.size());
	for (unsigned int _index = 0; _index < _size; _index++)
		delete allActors[_index];
}
