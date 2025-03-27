#pragma once
#pragma once
#include "../Utils/CoreMinimal.h"
#include "LightComponent.h"

class DirectionalLightComponent : public LightComponent
{
protected:
	vec3 direction;

public:
	FORCEINLINE vec3 GetDirection() const { return direction; }
	FORCEINLINE void SetDirection(const vec3& _direction) { direction = _direction; }

public:
	DirectionalLightComponent(Actor* _owner);
	DirectionalLightComponent(Actor* _owner, float _intensity, vec3 _color, vec3 _direction);
	virtual ~DirectionalLightComponent() = default;

};