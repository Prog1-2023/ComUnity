#include "LightComponent.h"
#include "../Managers/LightManager.h"
#include "../Actors/Actor.h"

LightComponent::LightComponent(Actor* _owner) : Component(_owner)
{
	ambientStrength = 1.0f;
	intensity = 1.0f;
	color = vec3(0.0f, 1.0f, 0.0f);
	LightManager::GetInstance().AddLight(this);
}

LightComponent::LightComponent(Actor* _owner, float _intensity, vec3 _color) : Component(_owner)
{
	intensity = _intensity;
	color = _color;
	LightManager::GetInstance().AddLight(this);
}

LightComponent::~LightComponent()
{
	LightManager::GetInstance().RemoveLight(this);
}

Component* LightComponent::Clone(Actor* _owner) const
{
	return new LightComponent(_owner);
}
