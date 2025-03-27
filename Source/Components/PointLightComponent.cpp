#include "PointLightComponent.h"

PointLightComponent::PointLightComponent(Actor* _owner) : LightComponent(_owner)
{
	radius = 1.0f;
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

PointLightComponent::PointLightComponent(Actor* _owner, float _intensity, vec3 _color) : LightComponent(_owner, _intensity, _color)
{
	radius = 1.0f;
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

PointLightComponent::PointLightComponent(Actor* _owner, float _intensity, vec3 _color, float _radius) : LightComponent(_owner, _intensity, _color)
{
	radius = _radius;
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

