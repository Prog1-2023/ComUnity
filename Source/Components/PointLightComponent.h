#pragma once
#include "LightComponent.h"

class PointLightComponent : public LightComponent
{
	float radius;
	float constant;
	float linear;
	float quadratic;

public:
	FORCEINLINE float GetRadius() const
	{
		return radius;
	}
	FORCEINLINE void SetRadius(const float& _radius)
	{
		radius = _radius;
	}
	FORCEINLINE float GetConstant() const
	{
		return constant;
	}
	FORCEINLINE float GetLinear() const
	{
		return linear;
	}
	FORCEINLINE float GetQuadratic() const
	{
		return quadratic;
	}

public:
	PointLightComponent(Actor* _owner);
	PointLightComponent(Actor* _owner, float _intensity, vec3 _color);
	PointLightComponent(Actor* _owner, float _intensity, vec3 _color, float radius);

	~PointLightComponent() = default;

};

