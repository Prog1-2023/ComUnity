#include "LightActor.h"
#include "../../Editor/World.h"


void LightActor::SetType(LightType _type)
{
	lightComponentActive = CreateComponent<LightComponent>();
	type = _type;
	if (type == DIRECTIONAL)
	{
		/*if (!directionalRef) directionalRef = new DirectionalLightComponent(this);
		lightComponentActive = directionalRef;*/
		lightComponentActive->SetColor(vec3(1.0f, 0.0f, 0.0f));
	}
	else if (type == SPOT)
	{
		if (!spotLightRef) 
			spotLightRef = CreateComponent<SpotLightComponent>();
		lightComponentActive = spotLightRef;
	}
	else if (type == POINT)
	{
		if (!pointLightRef)
			CreateComponent<PointLightComponent>();
		lightComponentActive = pointLightRef;
	}
	else if (type == NONE)
	{
		lightComponentActive = new LightComponent(this);
	}
}

LightActor::LightActor(Level* _level, const LightType& _type): Actor(_level)
{
	type = NONE;
	lightComponentActive = nullptr;
	directionalRef = nullptr;
	pointLightRef = nullptr;
	spotLightRef = nullptr;
	SetType(_type);
}

LightActor::~LightActor()
{
	if (directionalRef) delete directionalRef;
	if (spotLightRef) delete spotLightRef;
	if (pointLightRef) delete pointLightRef;
}
