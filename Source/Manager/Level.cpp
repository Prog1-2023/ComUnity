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
	skyBox = nullptr;
	grid = nullptr;
	/*cameraManager = Camera::CameraManager();
	collisionManager = CollisionManager();
	audioManager = AudioManager();
	gameMode = nullptr;*/

	/*window.create(VideoMode({ 1200, 600 }), _name);
	window.setVisible(false);*/

	M_LEVEL.RegisterLevel(_name, this);
	//InitLevel();
}

Level::~Level()
{
	delete skyBox;
	delete grid;
}

void Level::InitLevel()
{
	/*CameraActor* _camera = SpawnActor<CameraActor>("DefaultCamera");
	cameraManager.Register(_camera->GetCamera());*/
	
	InitDefaultSkyBox();
	grid = SpawnActor<Grid>();
	grid->Init(10, 2.0f);
	
	/*Actor* _actor = SpawnActor<Actor>();
	_actor->CreateComponent<StaticMeshComponent>();*/
}

void Level::Update(const float _deltaTime)
{

	actorManager.Update(_deltaTime);
	grid->Draw();
	skyBox->Draw();
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


void Level::InitDefaultSkyBox()
{
	skyBox = SpawnActor<SkyBox>();
	skyBox->Init({ "cube_right.png", "cube_left.png","cube_down.png",
		"cube_up.png",  "cube_front.png","cube_back.png" });
}

void Level::InitSkyBox(const vector<string>& _textures, const float& _scale)
{
	skyBox = SpawnActor<SkyBox>();
	skyBox->Init(_textures);
}
