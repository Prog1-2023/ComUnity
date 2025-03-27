#version 330 core

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

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 color;
in vec2 textureCoords;
in vec3 normal;
in vec3 fragPosition;

uniform vec3 uniformViewPosition;
uniform Light uniformLight;
uniform Material uniformMaterial;

out vec4 fragColor;

void main()
{
	fragColor = texture(uniformMaterial.baseColor, textureCoords);
}