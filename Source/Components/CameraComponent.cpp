#include "CameraComponent.h"
#include "../Actors/Actor.h"
#include "../Editor/World.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	fov = 90.0f;
	nearDistance = 0.1f;
	farDistance = 100.0f;
	window = _owner->GetWorld()->GetWindow();
}

void CameraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void CameraComponent::Tick(const float _deltatime)
{
	Super::Tick(_deltatime);
}

void CameraComponent::BeginDestroy()
{
	Super::BeginDestroy();
}
