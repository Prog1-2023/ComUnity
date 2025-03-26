#include "CameraComponent.h"
#include "../Actors/Actor.h"
#include "../Editor/World.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	fov = 90.0f;
	nearDistance = 0.1f;
	farDistance = 100.0f;
	targetPosition = vec3(0.0f, 0.0f, 0.0f);
	window = _owner->GetWorld()->GetWindow();
}
