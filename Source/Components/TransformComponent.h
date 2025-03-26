#pragma once
#include "../Utils/CoreMinimal.h"
#include "Component.h"

class Actor;

class TransformComponent : public Component
{
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

public:
	FORCEINLINE Vector3f GetPosition() const { return position; }
	FORCEINLINE Vector3f GetRotation() const { return rotation; }
	FORCEINLINE Vector3f GetScale() const { return scale; }
	FORCEINLINE void SetPosition(const Vector3f& _newPosition) { position = _newPosition; }
	FORCEINLINE void SetRotation(const Vector3f& _newRotation) { rotation = _newRotation; }
	FORCEINLINE void SetScale(const Vector3f& _newScale) { scale = _newScale; }

public:
	TransformComponent(Actor* _owner, const Vector3f& _position = Vector3(0.0f), const Vector3f& _rotation = Vector3(0.0f), const Vector3f& _scale = Vector3(1.0f));

public:
	void Move(const Vector3f& _offset);
	void Rotate(const Vector3f& _offset);
};

