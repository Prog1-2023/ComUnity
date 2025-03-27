#include "World.h"

World::World()
{
	allActors = vector<Actor*>();
	window = nullptr;
}

World::World(Window* _window)
{
	allActors = vector<Actor*>();
	window = _window;
}

World::~World()
{
	for (Actor* _actor : allActors)
	{
		delete _actor;
	}
}

void World::Start()
{
	// TODO Manager to INIT

	//SpawnActor();

	for (Actor* _actor : allActors)
	{
		if (!_actor) return;
		_actor->BeginPlay();
	}
}

void World::Update()
{
	// TODO Manager To UPDATE

	window->Update(); // => ProcessInputs TODO remove

	float _deltaTime = 0.5f;

	for (Actor* _actor : allActors)
	{
		if (!_actor) return;
		_actor->Tick(_deltaTime);
	}
}

void World::Stop()
{
	// TODO Manager to STOP

	for (Actor* _actor : allActors)
	{
		if (!_actor) return;
		_actor->BeginDestroy();
	}
}

LightActor* World::SpawnLight(LightType _type)
{
	LightActor* _light = SpawnActor<LightActor>();
	_light->SetType(_type);
	return _light;
}
