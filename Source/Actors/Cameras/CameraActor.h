#pragma once

#include "../../Utils/CoreMinimal.h"
#include "../Actor.h"
#include "../../Components/CameraComponent.h"

class Level;

class CameraActor : public Actor
{
	CameraComponent* camera;

public:
	FORCEINLINE CameraComponent* GetCameraComponent() const { return camera; }

public:
	CameraActor(Level* _level);
};

