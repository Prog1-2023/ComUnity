#include "SpotLightComponent.h"

SpotLightComponent::SpotLightComponent(Actor* _owner) : LightComponent(_owner)
{
    angle = 30.0f;
    cutoff = 0.9f;
}

SpotLightComponent::SpotLightComponent(Actor* _owner, float _intensity, vec3 _color, float _angle, float _cutoff) : LightComponent(_owner, _intensity, _color)
{
    angle = _angle;
    cutoff = _cutoff;
}

