#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* _owner):Component(_owner)
{
	transform = Transform();
}

TransformComponent::TransformComponent(Actor* _owner, Transform _transform) :Component(_owner)
{
	transform = _transform;
}