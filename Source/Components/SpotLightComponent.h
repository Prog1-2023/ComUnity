#pragma once
#include "../Utils/CoreMinimal.h"
#include "LightComponent.h"

class SpotLightComponent : public LightComponent
{
protected:
	float angle;
	float cutoff; //attenuation threshold

public:
	FORCEINLINE float GetAngle()const { return angle; }
	FORCEINLINE float GetCutoff()const { return cutoff; }
	FORCEINLINE void SetAngle(const float& _angle) { angle = _angle; }
	FORCEINLINE void SetCutoff(const float& _cutoff) { cutoff = _cutoff; }

public:
	SpotLightComponent(Actor* _owner);
	SpotLightComponent(Actor* _owner, float _intensity, vec3 _color, float _angle, float _cutoff);
	virtual ~SpotLightComponent() = default;

};
