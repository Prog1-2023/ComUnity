#include "SpotLightComponent.h"

SpotLightComponent::SpotLightComponent(Actor* _owner) : LightComponent(_owner)
{
    direction = vec3(0.0f, 0.0f, 0.0f);
    angle = 30.0f;
    cutoff = 0.9f;
    cutoff = 0.9f;
    outerCutoff = 1.0f;
    constant = 1.0f;
    linear = 1.0f;
    quadratic = 1.0f;
}

SpotLightComponent::SpotLightComponent(Actor* _owner, float _intensity, vec3 _color, float _angle, float _cutoff) : LightComponent(_owner, _intensity, _color)
{
    direction = vec3(0.0f, 0.0f, 0.0f);
    angle = _angle;
    cutoff = _cutoff;
    cutoff = 0.9f;
    outerCutoff = 1.0f;
    constant = 1.0f;
    linear = 1.0f;
    quadratic = 1.0f;
}

