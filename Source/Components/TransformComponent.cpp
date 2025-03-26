#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* _owner) :Component(_owner)
{
    owner = _owner;
}

TransformComponent::TransformComponent(Actor* _owner, const TransformComponent& _other) : Component(_owner)
{
    transform = _other.transform;
}

TransformComponent::TransformComponent(Actor* _owner, Transform _transform) :Component(_owner)
{
    transform = _transform;
}

void TransformComponent::Construct()
{
    SUPER::Construct();
}

void TransformComponent::Deconstruct()
{
    SUPER::Deconstruct();
}