#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Actor.h"
#include "../Actors/Cameras/CameraActor.h"
#include "Windows/Window.h"

class World
{
	vector<Actor*> allActors;
	Window* window;

	CameraActor* currentCamera;

public:
	FORCEINLINE vector<Actor*> GetAllActors() const { return allActors; }
	FORCEINLINE Window* GetWindow() const { return window; }
	FORCEINLINE void SetWindow(Window* _window) { window = _window; }
	
	FORCEINLINE void SetCurrentCamera(CameraActor* _camera) { currentCamera = _camera; }
	FORCEINLINE CameraActor* GetCurrentCamera() const { return currentCamera; }

public:
	World();
	~World();

private:
	
public:
	void Initialize();
	template <typename Type = Actor>
	Type* SpawnActor()
	{
		Type* _actor = new Type(this);
		allActors.push_back(_actor);
		return _actor;
	}

	void SetVM();
};

