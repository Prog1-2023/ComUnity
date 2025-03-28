#include "ActorManager.h"
#include "../UI/UIManager.h"
#include "../UI/HierarchyWidget.h"

ActorManager::~ActorManager()
{
	for (Actor* _actor : allActors)
	{
		delete _actor;
	}
	//allActors.Clear();
}

void ActorManager::Init()
{
	UIManager::GetInstance().GetWidgetOfType<HierarchyWidget>()->OnActorDeleteAction().Add(this, &ActorManager::RemoveActor);
}

void ActorManager::BeginPlay()
{
	for (Actor* _actor : allActors)
	{
		_actor->BeginPlay();
	}
}

void ActorManager::Update(const float _deltaTime)
{
	vector<Actor*> _garbage;

	for (Actor* _actor : allActors)
	{
		if (_actor->IsActive())
		{
			_actor->Tick(_deltaTime);
		}

		if (_actor->IsToDelete())
		{
			_garbage.push_back(_actor);
		}
	}

	for (Actor* _actor : _garbage)
	{
		_actor->Deconstruct();
		delete _actor;
	}
}

void ActorManager::BeginDestroy()
{
	for (Actor* _actor : allActors)
	{
		_actor->BeginDestroy();
	}
}