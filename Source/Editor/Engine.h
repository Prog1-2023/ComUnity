#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Editor/Windows/Window.h"
//#include "../Editor/World.h"

#include "../Manager/LevelManager.h" // TODO Maybe need to remove
#include "../UI/UIManager.h"

class CameraComponent;
class Engine
{
	Window* window;
	//World* world;
	LevelManager levelManager;
	UIManager* uiManager;

public:
	Engine();
	~Engine();

public:
	void Run();

private:
	void Start();
	void Update();
	void Stop();
	void InitInput(CameraComponent* _camera);
};

