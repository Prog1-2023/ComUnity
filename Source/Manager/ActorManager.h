#pragma once

#include "../Actors/Actor.h"
#include "../Actors/SoundActor.h"

class ActorManager
{
	Array<Actor*> allActors;
	multimap<string, Actor*> actorsName;
public:
	//SoundActor* sound = nullptr;

public:
	FORCEINLINE void AddActor(Actor* _actor)
	{
		allActors.Add(_actor);
		AddActorName(_actor);
	}
	FORCEINLINE void RemoveActor(Actor* _actor)
	{
		allActors.Remove(_actor);
		RemoveActorName(_actor);
	}
	FORCEINLINE Array<Actor*> GetAllActors() const
	{
		return allActors;
	}

	FORCEINLINE void AddActorName(Actor* _actor)
	{
		actorsName.insert({ _actor->GetName(), _actor });
	}
	FORCEINLINE void RemoveActorName(Actor* _actor)
	{
		const string& _actorName = _actor->GetName();
		using Iterator = multimap<string, Actor*>::iterator;
		const pair<Iterator, Iterator>& _results = actorsName.equal_range(_actorName);

		for (Iterator _it = _results.first; _it != _results.second; )
		{
			if (_it->second == _actor)
			{
				actorsName.erase(_it++);
				break;
			}

			++_it;
		}
	}
	FORCEINLINE string GetDisplayName(Actor* _actor)
	{
		RemoveActorName(_actor);
		AddActorName(_actor);
		return GetAvailableName(_actor->GetName());
	}
	FORCEINLINE string GetAvailableName(const string& _name, const int _index = 1)
	{
		// Je rajoute "_index" au nom actuel
		const string& _fullName = _name + (_index == 0 ? "" : "_" + to_string(_index));

		// Je parcours tous les Actors qui possèdent le même nom 
		using Iterator = multimap<string, Actor*>::iterator;
		const pair<Iterator, Iterator>& _results = actorsName.equal_range(_name);
		if (actorsName.empty() || _results.first == _results.second) return _name;
		bool _isFindSameName = false;
		for (Iterator _it = _results.first; _it != _results.second; ++_it)
		{
			// Si c'est le même
			if (_it->second->GetDisplayName() == _fullName)
			{
				_isFindSameName = true;
				break;
			}
		}

		if (!_isFindSameName)
		{
			return _fullName;
		}

		// Je reteste avec l'index suivant
		return GetAvailableName(_name, _index + 1);
	}

public:
	~ActorManager();

	void Init();

	void BeginPlay();
	void Update(const float _deltaTime);
	void BeginDestroy();
};