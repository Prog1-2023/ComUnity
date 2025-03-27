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

#pragma region CountLight

    int _directionCount = 0;
    int _spotCount = 0;
    int _pointCount = 0;

    for (int i = 0; i < _lightCount; i++)
    {
        LightActor* _actor = dynamic_cast<LightActor*>(lights[i]->GetOwner());
        if (!_actor) continue;
        if (_actor->GetLightType() == DIRECTIONAL) _directionCount++;
        else if (_actor->GetLightType() == POINT) _pointCount++;
        else if (_actor->GetLightType() == SPOT) _spotCount++;
    }

    const GLuint& _uniformDirectionalCount = glGetUniformLocation(_shaderProgram, "uniformDirectionalCount");
    glUniform1i(_uniformDirectionalCount, _directionCount);

    const GLuint& _uniformPointCount = glGetUniformLocation(_shaderProgram, "uniformPointCount");
    glUniform1i(_uniformPointCount, _pointCount);

    const GLuint& _uniformSpotCount = glGetUniformLocation(_shaderProgram, "uniformSpotCount");
    glUniform1i(_uniformSpotCount, _spotCount);
#pragma endregion

    int _pointIndex = 0;
    int _spotIndex = 0;
    int _directionIndex = 0;

    for (int _index = 0; _index < _lightCount; _index++)
    {
        LightActor* _actor = dynamic_cast<LightActor*>(lights[_index]->GetOwner());
        if (!_actor) continue;

        if (_actor->GetLightType() == DIRECTIONAL)
        {
            DirectionalLightComponent* _light = dynamic_cast<DirectionalLightComponent*>(lights[_index]);
            string _baseDirectional = "uniformDirLight[" + to_string(_directionIndex) + "]";

            const GLuint& _uniformLightDirection = glGetUniformLocation(_shaderProgram, (_baseDirectional + ".direction").c_str());
            glUniform3f(_uniformLightDirection, _light->GetDirection().x, _light->GetDirection().y, _light->GetDirection().z);

            const GLuint& _uniformLightAmbient = glGetUniformLocation(_shaderProgram, (_baseDirectional + ".ambient").c_str());
            glUniform3f(_uniformLightAmbient, _light->GetColor().x, _light->GetColor().y, _light->GetColor().z);

            const GLuint& _uniformLightDiffuse = glGetUniformLocation(_shaderProgram, (_baseDirectional + ".diffuse").c_str());
            glUniform3f(_uniformLightDiffuse, _light->GetDiffuse().x, _light->GetDiffuse().y, _light->GetDiffuse().z);

            const GLuint& _uniformLightSpecular = glGetUniformLocation(_shaderProgram, (_baseDirectional + ".specular").c_str());
            glUniform3f(_uniformLightSpecular, _light->GetSpecularStrength().x, _light->GetSpecularStrength().y, _light->GetSpecularStrength().z);

        }
        else if (_actor->GetLightType() == POINT)
        {
            PointLightComponent* _light = dynamic_cast<PointLightComponent*>(lights[_index]);
            string _basePoint = "uniformPointLight[" + to_string(_pointIndex) + "]";

            const GLuint& _uniformLightPoint = glGetUniformLocation(_shaderProgram, (_basePoint + ".position").c_str());
            glUniform3f(_uniformLightPoint, _actor->GetTransform()->GetPosition().x, _actor->GetTransform()->GetPosition().y, _actor->GetTransform()->GetPosition().z);

            const GLuint& _uniformLightConstant = glGetUniformLocation(_shaderProgram, (_basePoint + ".constant").c_str());
            glUniform1f(_uniformLightConstant, _light->GetConstant());

            const GLuint& _uniformLightLinear = glGetUniformLocation(_shaderProgram, (_basePoint + ".linear").c_str());
            glUniform1f(_uniformLightLinear, _light->GetLinear());

            const GLuint& _uniformLightQuadratic = glGetUniformLocation(_shaderProgram, (_basePoint + ".quadratic").c_str());
            glUniform1f(_uniformLightQuadratic, _light->GetQuadratic());

            const GLuint& _uniformLightAmbient = glGetUniformLocation(_shaderProgram, (_basePoint + ".ambient").c_str());
            glUniform3f(_uniformLightAmbient, _light->GetColor().x, _light->GetColor().y, _light->GetColor().z);

            const GLuint& _uniformLightDiffuse = glGetUniformLocation(_shaderProgram, (_basePoint + ".diffuse").c_str());
            glUniform3f(_uniformLightDiffuse, _light->GetDiffuse().x, _light->GetDiffuse().y, _light->GetDiffuse().z);

            const GLuint& _uniformLightSpecular = glGetUniformLocation(_shaderProgram, (_basePoint + ".specular").c_str());
            glUniform3f(_uniformLightSpecular, _light->GetSpecularStrength().x, _light->GetSpecularStrength().y, _light->GetSpecularStrength().z);

        }
        else if (_actor->GetLightType() == SPOT)
        {
            SpotLightComponent* _light = dynamic_cast<SpotLightComponent*>(lights[_index]);
            string _baseSpot = "uniformSpotLight[" + to_string(_spotIndex) + "]";

            const GLuint& _uniformLightPosition = glGetUniformLocation(_shaderProgram, (_baseSpot + ".position").c_str());
            glUniform3f(_uniformLightPosition, _actor->GetTransform()->GetPosition().x, _actor->GetTransform()->GetPosition().y, _actor->GetTransform()->GetPosition().z);

            const GLuint& _uniformLightDirection = glGetUniformLocation(_shaderProgram, (_baseSpot + ".direction").c_str());
            glUniform3f(_uniformLightDirection, _light->GetDirection().x, _light->GetDirection().y, _light->GetDirection().z);

            const GLuint& _uniformLightCutoff = glGetUniformLocation(_shaderProgram, (_baseSpot + ".cutOff").c_str());
            glUniform1f(_uniformLightCutoff, _light->GetCutoff());

            const GLuint& _uniformLightOuterCutoff = glGetUniformLocation(_shaderProgram, (_baseSpot + ".outerCutOff").c_str());
            glUniform1f(_uniformLightOuterCutoff, _light->GetOuterCutoff());

            const GLuint& _uniformLightConstant = glGetUniformLocation(_shaderProgram, (_baseSpot + ".constant").c_str());
            glUniform1f(_uniformLightConstant, _light->GetConstant());

            const GLuint& _uniformLightLinear = glGetUniformLocation(_shaderProgram, (_baseSpot + ".linear").c_str());
            glUniform1f(_uniformLightLinear, _light->GetLinear());

            const GLuint& _uniformLightQuadratic = glGetUniformLocation(_shaderProgram, (_baseSpot + ".quadratic").c_str());
            glUniform1f(_uniformLightQuadratic, _light->GetQuadratic());

            const GLuint& _uniformLightAmbient = glGetUniformLocation(_shaderProgram, (_baseSpot + ".ambient").c_str());
            glUniform3f(_uniformLightAmbient, _light->GetColor().x, _light->GetColor().y, _light->GetColor().z);

            const GLuint& _uniformLightDiffuse = glGetUniformLocation(_shaderProgram, (_baseSpot + ".diffuse").c_str());
            glUniform3f(_uniformLightDiffuse, _light->GetDiffuse().x, _light->GetDiffuse().y, _light->GetDiffuse().z);

            const GLuint& _uniformLightSpecular = glGetUniformLocation(_shaderProgram, (_baseSpot + ".specular").c_str());
            glUniform3f(_uniformLightSpecular, _light->GetSpecularStrength().x, _light->GetSpecularStrength().y, _light->GetSpecularStrength().z);

        }

       
    }
}