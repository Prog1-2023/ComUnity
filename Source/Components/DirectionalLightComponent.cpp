#include "DirectionalLightComponent.h"

DirectionalLightComponent::DirectionalLightComponent(Actor* _owner) : LightComponent(_owner)
{
    direction = vec3(0.0f, 0.0f, 0.0f);
}

DirectionalLightComponent::DirectionalLightComponent(Actor* _owner, float _intensity, vec3 _color, vec3 _direction) : LightComponent(_owner, _intensity, _color)
{
    direction = _direction;
}

