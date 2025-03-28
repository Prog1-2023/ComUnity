#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Editor/Windows/Window.h"
#include "../Editor/World.h"

#include "../Manager/LevelManager.h" // TODO Maybe need to remove

class Engine
{
	Window* window;
	//World* world;
	LevelManager* levelManager;

public:
	Engine();
	~Engine();

public:
	void Run();

private:
	void Start();
	void Update();
	void Stop();
};

