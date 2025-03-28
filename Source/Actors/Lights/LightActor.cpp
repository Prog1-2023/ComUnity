#include "LightActor.h"


void LightActor::SetType(LightType _type)
{
	lightComponentActive = new LightComponent(this);
	type = _type;
	if (type == DIRECTIONAL)
	{
		/*if (!directionalRef) directionalRef = new DirectionalLightComponent(this);
		lightComponentActive = directionalRef;*/
		lightComponentActive->SetColor(vec3(1.0f, 0.0f, 0.0f));
	}
	else if (type == SPOT)
	{
		if (!spotLightRef) spotLightRef = new SpotLightComponent(this);
		lightComponentActive = spotLightRef;
	}
	else if (type == POINT)
	{
		if (!pointLightRef) pointLightRef = new PointLightComponent(this);
		lightComponentActive = pointLightRef;
	}
	else if (type == NONE)
	{
		lightComponentActive = new LightComponent(this);
	}
}

LightActor::LightActor(Level* _level): Actor(_level)
{
	type = NONE;
	lightComponentActive = nullptr;
	components.insert(lightComponentActive);
	directionalRef = nullptr;
	pointLightRef = nullptr;
	spotLightRef = nullptr;
	
}

LightActor::~LightActor()
{
	if (directionalRef) delete directionalRef;
	if (spotLightRef) delete spotLightRef;
	if (pointLightRef) delete pointLightRef;
}
