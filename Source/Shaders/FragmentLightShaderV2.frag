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

struct Material
{
	sampler2D ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;

	sampler2D baseColor;
	sampler2D metallic;
	sampler2D normalCamera;
	sampler2D height;
	sampler2D ambientOcclusion;

	float shininess;
};

uniform Material uniformMaterial;
uniform Light uniformLight[10];
uniform int uniformLightCount;

out vec4 fragColor;
in vec2 textureCoords;

vec3 result;

void ComputeLightning();

void main()
{
    ComputeLightning();
    fragColor = vec4(result, 1.0f) * texture(uniformMaterial.baseColor, textureCoords);
//  fragColor = vec4(result, 1.0f);
};


void ComputeLightning()
{
    result = vec3(0.0f);
    for(int _index = 0; _index < uniformLightCount; _index++)
    {
         result += (uniformLight[_index].color * uniformLight[_index].ambientStrength);
    }
}
