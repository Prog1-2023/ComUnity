#pragma once
#include "../Utils/CoreMinimal.h"
#include "Component.h"

class LightComponent : public Component
{
protected:
    float ambientStrength;
    float intensity;
    vec3 color;
    vec3 specularStrenght;
    vec3 diffuse;

public:
    FORCEINLINE float GetIntensity()const { return intensity; }
    FORCEINLINE vec3 GetColor()const { return color; }
    FORCEINLINE void SetColor(const vec3& _color) { color = _color; }
    FORCEINLINE vec3 SetIntensity(const float _intensity) { intensity = _intensity; }
    FORCEINLINE void SetAmbientStrength(const float& _ambientStrength) { ambientStrength = _ambientStrength; }
    FORCEINLINE float GetAmbientStrength() { return ambientStrength; }
    FORCEINLINE vec3 GetSpecularStrength() { return specularStrenght; }
    FORCEINLINE vec3 GetDiffuse() { return diffuse; }

public:
    LightComponent(Actor* _owner);
    LightComponent(Actor* _owner, float _intensity, vec3 _color);

    virtual ~LightComponent();
};