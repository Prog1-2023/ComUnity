#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Components/DirectionalLightComponent.h"
#include "../Components/SpotLightComponent.h"
#include "../Components/PointLightComponent.h"

struct Light
{
    vec3 position;
    float ambientStrength;
    vec3 specularStrength;
    vec3 color;
    vec3 direction;
    float intensity;

    Light(const vec3& _position, float _ambientStrength,
        const vec3& _specularStrength, const vec3& _color, const vec3& _direction, float _intensity)
    {
        position = _position;
        ambientStrength = _ambientStrength;
        specularStrength = _specularStrength;
        color = _color;
        direction = _direction;
        intensity = _intensity;
    }
};



class LightManager
{
    vector<LightComponent*> lights;
public:
    static LightManager& GetInstance()
    {
        static LightManager _instance;
        return _instance;
    }
    vector<LightComponent*> GetLights() { return lights; }

public:
    void AddLight(LightComponent* _light);
    void RemoveLight(LightComponent* _light);
    void ApplyLighting(GLuint _shaderProgram);

};