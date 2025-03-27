#version 330 core

struct Light 
{
    vec3 position;
    float ambientStrength;
    vec3 specularStrength;
    vec3 color;
    vec3 direction;
    float intensity;
};

uniform Light uniformLight[10];
uniform int uniformLightCount;
out vec4 fragColor;

vec3 result;

void ComputeLightning();

void main()
{
    ComputeLightning();
    fragColor = vec4(result, 1.0f);
};


void ComputeLightning()
{
    result = vec3(0.0f);
    for(int _index = 0; _index < uniformLightCount; _index++)
    {
         result += (uniformLight[_index].color * uniformLight[_index].ambientStrength);
    }
}

