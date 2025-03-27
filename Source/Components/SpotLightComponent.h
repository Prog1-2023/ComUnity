#pragma once
#include "../Utils/CoreMinimal.h"
#include "LightComponent.h"

class SpotLightComponent : public LightComponent
{
protected:
	vec3 direction;

	float angle;
	float cutoff;
	float outerCutoff;


	float constant;
	float linear;
	float quadratic;
public:
	FORCEINLINE vec3 GetDirection() const { return direction; }
	FORCEINLINE float GetAngle()const { return angle; }
	FORCEINLINE float GetCutoff()const { return cutoff; }
	FORCEINLINE float GetOuterCutoff()const { return outerCutoff; }
	FORCEINLINE float GetConstant()const { return constant; }
	FORCEINLINE float GetLinear()const { return linear; }
	FORCEINLINE float GetQuadratic()const { return quadratic; }
	FORCEINLINE void SetAngle(const float& _angle) { angle = _angle; }
	FORCEINLINE void SetCutoff(const float& _cutoff) { cutoff = _cutoff; }

public:
	SpotLightComponent(Actor* _owner);
	SpotLightComponent(Actor* _owner, float _intensity, vec3 _color, float _angle, float _cutoff);
	virtual ~SpotLightComponent() = default;
};
