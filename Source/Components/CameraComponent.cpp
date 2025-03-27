#include "CameraComponent.h"
#include "../Actors/Actor.h"
#include "../Editor/World.h"
#include "../Manager/Level.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	fov = 90.0f;
	nearDistance = 0.1f;
	farDistance = 100.0f;
	//window = _owner->GetWorld()->GetWindow();

}

CameraComponent::CameraComponent(Actor* _owner, const CameraComponent& _other) : Component(_owner)
{
	fov = _other.fov;
	nearDistance = _other.nearDistance;
	farDistance = _other.farDistance;
	window = _other.window;
}

void CameraComponent::Construct()
{
	SUPER::Construct();
}

void CameraComponent::Deconstruct()
{
	SUPER::Deconstruct();
}