#pragma once
#include "../Utils/CoreMinimal.h"
#include "Component.h"

enum Mobility
{
	STATIC,
	STATIONARY,
	MOVABLE
};


class TransformComponent : public Component
{
	Vector3f localLocation;

	Vector3f location;
	Vector3f rotation;
	Vector3f scale;

	Mobility mobility;

	bool physics = false;
	int moveSpeed = 10;
	float rotateSpeed = 50.25f;

public:
	FORCEINLINE Vector3f GetLocalLocation() { return localLocation; }
	FORCEINLINE Vector3f GetLocation() { return location; }
	FORCEINLINE Vector3f GetRotation() { return rotation; }
	FORCEINLINE Vector3f GetScale() { return scale; }

	FORCEINLINE void SetLocalLocation(const Vector3f& _location) { localLocation = _location; }
	FORCEINLINE void SetLocation(const Vector3f& _location) { location = _location; }
	FORCEINLINE void SetRotation(const Vector3f& _rotation) { rotation = _rotation; }
	FORCEINLINE void SetScale(const Vector3f& _scale) { scale = _scale; }

public:
	TransformComponent(Actor* _owner);
	~TransformComponent();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltatime) override;
	virtual void BeginDestroy() override;

};

