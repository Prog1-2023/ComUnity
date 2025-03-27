#include "Level.h"
//#include "LevelManager.h"
//#include "ActorManager.h"
//#include "CameraManager.h"
//#include "InputManager.h"
//#include "AudioManager.h"
//#include "GameMode.h"

#include "../Manager/LevelManager.h"
#include "../Components/StaticMeshComponent.h"

#define M_LEVEL LevelManager::GetInstance()

Level::Level(const string& _name)
{
	isLoaded = false;
	name = _name;
	actorManager = ActorManager();
	/*cameraManager = Camera::CameraManager();
	collisionManager = CollisionManager();
	audioManager = AudioManager();
	gameMode = nullptr;*/

	/*window.create(VideoMode({ 1200, 600 }), _name);
	window.setVisible(false);*/

	M_LEVEL.RegisterLevel(_name, this);
	InitLevel();
}

Level::~Level()
{

}

void Level::InitLevel()
{
	/*CameraActor* _camera = SpawnActor<CameraActor>("DefaultCamera");
	cameraManager.Register(_camera->GetCamera());*/

	Actor* _actor = SpawnActor<Actor>();
	_actor->CreateComponent<StaticMeshComponent>();
}

void Level::Update(const float _deltaTime)
{

	actorManager.Update(_deltaTime);


}

void Level::Load()
{
	if (!isLoaded)
	{
		InitLevel();
		isLoaded = true;
	}


	actorManager.BeginPlay();
}

void Level::Unload()
{

	actorManager.BeginDestroy();
}