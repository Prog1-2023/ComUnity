#include "CameraComponent.h"
#include "../Actors/Actor.h"
#include "../Editor/World.h"
#include "../Manager/LevelManager.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	fov = 90.0f;
	nearDistance = 0.1f;
	farDistance = 100.f;
	targetPos = vec3(0, 0, 0);

	viewRadius = 5.0f;
	theta = 0.0f;
	phi = 0.0f;
	speed = 0.05f;
	zoomSpeed = 0.1f;
}

CameraComponent::CameraComponent(Actor* _owner, const CameraComponent& _other) : Component(_owner)
{
	fov = _other.fov;
	nearDistance = _other.nearDistance;
	farDistance = _other.farDistance;
	targetPos = _other.targetPos;

	viewRadius = _other.viewRadius;
	theta = _other.theta;
	phi = _other.phi;
	speed = _other.speed;
	zoomSpeed = _other.zoomSpeed;
}

void CameraComponent::Construct()
{
	SUPER::Construct();
}

void CameraComponent::Deconstruct()
{
	SUPER::Deconstruct();
}