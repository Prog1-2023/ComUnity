#include "LightManager.h"
#include "../Actors/Lights/LightActor.h"

void LightManager::AddLight(LightComponent* _light)
{
    lights.push_back(_light);
}

void LightManager::RemoveLight(LightComponent* _light)
{
    lights.erase(find(lights.begin(), lights.end(), _light));
}

void LightManager::ApplyLighting(GLuint _shaderProgram)
{
    glUseProgram(_shaderProgram);

    int _lightCount = lights.size();
    glUniform1i(glGetUniformLocation(_shaderProgram, "uniformLightCount"), _lightCount);

    for (int _index = 0; _index < _lightCount; _index++)
    {
        LightActor* _actor = dynamic_cast<LightActor*>(lights[_index]->GetOwner());
        if (!_actor) continue;

        _actor->GetLightType();

        string _base = "uniformLight[" + to_string(_index) + "]";

        const GLuint& _uniformLightPosition = glGetUniformLocation(_shaderProgram, (_base + ".position").c_str());
        glUniform3f(_uniformLightPosition, 0.0f, 0.0f,0.0f);

        const GLuint& _uniformLightColor = glGetUniformLocation(_shaderProgram, (_base + ".color").c_str());
        glUniform3f(_uniformLightColor, lights[_index]->GetColor().x, lights[_index]->GetColor().y, lights[_index]->GetColor().z);

        const GLuint& _uniformLightAmbientStrength = glGetUniformLocation(_shaderProgram, (_base + ".ambientStrength").c_str());
        glUniform1f(_uniformLightAmbientStrength, lights[_index]->GetAmbientStrength());

        const GLuint& _uniformLightIntensity = glGetUniformLocation(_shaderProgram, (_base + ".intensity").c_str());
        glUniform1f(_uniformLightIntensity, lights[_index]->GetIntensity());
    }
}