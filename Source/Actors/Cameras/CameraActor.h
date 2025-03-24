#pragma once
#include "../../Utils/CoreMinimal.h"
#include "../Actor.h"
#include "../../Components/CameraComponent.h"
#include "../../Components/StaticMeshComponent.h"

class Window;

class CameraActor : public Actor
{
	CameraComponent* camera;
	StaticMeshComponent* mesh;

public:
	float viewRadius;
	float theta;
	float phi;
	float speed;
	float zoomSpeed;

public:
	FORCEINLINE CameraComponent* GetCamera() const { return camera; }
	FORCEINLINE void ZoomIn() { viewRadius += zoomSpeed; }
	FORCEINLINE void ZoomOut() { viewRadius -= zoomSpeed; }
	FORCEINLINE void MoveViewUp() { phi += speed; }
	FORCEINLINE void MoveViewDown() { phi -= speed; }
	FORCEINLINE void MoveViewLeft() { theta -= speed; }
	FORCEINLINE void MoveViewRight() { theta += speed; }

public:
	CameraActor(World* _world);
	~CameraActor();

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltatime) override;
	virtual void BeginDestroy() override;

	mat4 ComputeView();
};

