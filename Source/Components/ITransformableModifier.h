#pragma once
#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Actors/Transform.h"

class ITransformableModifier
{
public:
	FORCEINLINE virtual void SetPosition(const Vector3f& _position) = 0;
	FORCEINLINE virtual void SetRotation(const Vector3f& _rotation) = 0;
	FORCEINLINE virtual void SetScale(const Vector3f& _scale) = 0;
	FORCEINLINE virtual void SetTransform(const Transform& _transformData)
	{
		SetPosition(_transformData.location);
		SetRotation(_transformData.rotation);
		SetScale(_transformData.scale);
		
	}
	FORCEINLINE virtual void Move(const Vector3f& _offset) = 0;
	FORCEINLINE virtual void Rotate(const Vector3f& _angle) = 0;
	FORCEINLINE virtual void Scale(const Vector3f& _factor) = 0;
};