#include "PointLightComponent.h"

PointLightComponent::PointLightComponent(Actor* _owner) : LightComponent(_owner)
{
	radius = 1.0f;
}

PointLightComponent::PointLightComponent(Actor* _owner, float _intensity, vec3 _color) : LightComponent(_owner, _intensity, _color)
{
	radius = 1.0f;
}

PointLightComponent::PointLightComponent(Actor* _owner, float _intensity, vec3 _color, float _radius) : LightComponent(_owner, _intensity, _color)
{
	radius = _radius;
}

