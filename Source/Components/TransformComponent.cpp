#include "TransformComponent.h"
#include "../Actors/Actor.h"

TransformComponent::TransformComponent(Actor* _owner, const Vector3f& _position, const Vector3f& _rotation, const Vector3f& _scale) : Component(_owner)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;
}

void TransformComponent::Move(const Vector3f& _offset)
{
	position += _offset;
}

void TransformComponent::Rotate(const Vector3f& _offset)
{
	rotation += _offset;
}
