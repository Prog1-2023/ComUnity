#pragma once

#include "../../Utils/CoreMinimal.h"
#include "../Actor.h"
#include "../../Components/CameraComponent.h"

class CameraActor : public Actor
{
	CameraComponent* camera;

public:
	FORCEINLINE CameraComponent* GetCameraComponent() const { return camera; }

public:
	CameraActor(World* _world);
};

