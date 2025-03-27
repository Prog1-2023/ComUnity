#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* _owner) : Component(_owner)
{
	position = Vector3f(0.0f,0.0f,0.0f);
	LocalPosition = Vector3f(0.0f,0.0f,0.0f);
	rotation = Vector3f(0.0f,0.0f,0.0f);
	scale = Vector3f(0.0f,0.0f,0.0f);
}
