#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Transform.h"

class ITransformableViewer
{

public:
	FORCEINLINE virtual Vector3f GetPosition() const = 0;
	FORCEINLINE virtual Vector3f GetRotation() const = 0;
	FORCEINLINE virtual Vector3f GetScale() const = 0;
	FORCEINLINE virtual Transform GetTransform() const = 0;
};
