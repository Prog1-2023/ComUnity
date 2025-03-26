#pragma once
#include"../Utils/CoreMinimal.h"
#include"../Editor/Windows/Window.h"
#include"../Actors/Actor.h"

#include "../Manager/ActorManager.h"
#include "../Utils/SubclassOf.h"

//#include "CameraManager.h"
//#include "CollisionManager.h"
//#include "AudioManager.h"
//#include "GameMode.h"

//using namespace Camera;
//using namespace UI;

class Level
{
	bool isLoaded;
	string name;
	ActorManager actorManager;
	/*
	Camera::CameraManager cameraManager;
	CollisionManager collisionManager;
	AudioManager audioManager;*/

protected:
	
	//GameMode* gameMode;

public:


	FORCEINLINE string GetName() const
	{
		return name;
	}
	FORCEINLINE ActorManager& GetActorManager()
	{
		return actorManager;
	}
	/*
	FORCEINLINE Camera::CameraManager& GetCameraManager()
	{
		return cameraManager;
	}
	FORCEINLINE CollisionManager& GetCollisionManager()
	{
		return collisionManager;
	}*/

#pragma region GameMode

	/*template<typename Type = GameMode, IS_BASE_OF(GameMode, Type)>
	FORCEINLINE Type* GetGameMode()
	{
		if (!gameMode)
		{
			Type* _type = SpawnGameMode<Type>();
			gameMode = _type;
			return _type;
		}

		return Cast<Type>(gameMode);
	}*/

	/*template<typename Type = GameMode, IS_BASE_OF(GameMode, Type)>
	FORCEINLINE Type* SpawnGameMode()
	{
		GameMode* _gameMode = GetGameModeRef();
		Type* _type = nullptr;

		if (Type* _gameModeCasted = Cast<Type>(_gameMode))
		{
			const SubclassOf<Type>& _gameModeRef = *_gameModeCasted;
			_type = SpawnActor<Type>(_gameModeRef);
		}

		delete _gameMode;
		return _type;
	}*/

	/*FORCEINLINE virtual GameMode* GetGameModeRef()
	{
		return new GameMode(this);
	}*/

#pragma endregion

#pragma region Spawn

#pragma region SpawnActor

	template <typename Type, typename ...Args, IS_BASE_OF(Actor, Type)>
	FORCEINLINE Type* SpawnActor(Args&&... _args)
	{
		Type* _actor = Spawn<Type>(this, forward<Args>(_args)...);
		_actor->Construct();
		_actor->Register();

		return _actor;
	}

	//template <typename Type, IS_BASE_OF(Actor, Type)>
	//FORCEINLINE Type* SpawnActor(const SubclassOf<Type>& _actorRef)
	//{
	//	Type* _actor = Spawn<Type>(_actorRef);
	//	_actor->Construct();
	//	_actor->Register();

	//	return _actor;
	//}

#pragma endregion

	//TODO move into AudioManager
#pragma region SpawnSample

	/*template <typename Type = Sample, typename ...Args, IS_BASE_OF(Sample, Type)>
	FORCEINLINE Type* SpawnSample(const string& _path, const AudioExtensionType& _type = MP3,
		const Time& _time = Time(), const Time& _duration = Time())
	{
		const string& _finalPath = _path + audioManager.GetExtension(_type);
		Type* _sample = audioManager.GetAvailable(_finalPath);

		if (_sample)
		{
			audioManager.PlaySample(_sample, _time, _duration);
			return _sample;
		}

		_sample = SpawnActor<Type>(_finalPath);
		audioManager.RegisterSample(_sample);
		_sample->Stop();
		audioManager.PlaySample(_sample, _time, _duration);
		return _sample;
	}*/

	

#pragma endregion

#pragma endregion

#pragma endregion

public:
	Level(const string& _name);

private:
	

protected:
	virtual void InitLevel();

public:
	void Update(const float _deltaTime);
	virtual void Load();
	virtual void Unload();
};