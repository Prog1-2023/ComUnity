#pragma once
#include "../../Utils/CoreMinimal.h"
#include "../Actor.h"
#include "../../Components/DirectionalLightComponent.h"
#include "../../Components/SpotLightComponent.h"
#include "../../Components/PointLightComponent.h"

enum LightType
{
	NONE,
	DIRECTIONAL,
	SPOT,
	POINT
};

class LightActor : public Actor
{
	//ENUM
	LightType type;
	LightComponent* lightComponentActive;

	//3 Connard
	DirectionalLightComponent* directionalRef;
	SpotLightComponent* spotLightRef;
	PointLightComponent* pointLightRef;

public:
	FORCEINLINE LightType GetLightType() const
	{
		return type;
	}
	FORCEINLINE LightComponent* GetLightComponentActive() const
	{
		return lightComponentActive;
	}
	FORCEINLINE void SetColor(vec3 _color)
	{
		if (!lightComponentActive) return;
		lightComponentActive->SetColor(_color);
	}
	void SetType(LightType _type);

public:
	LightActor(World* _world);
	~LightActor();
};