#version 330 core



struct Material
{
	sampler2D diffuse1;
	sampler2D specular1;
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

//uniform vec3 uniformLightPosition;
//uniform vec3 uniformLightColor;
uniform vec3 uniformViewPosition;
uniform Light uniformLight;
uniform Material uniformMaterial;

out vec4 fragColor;

void main()
{
	// Use if no textures
	//fragColor = vec4(color, 1.0f) * uniformColor;
	// Use if textures
	//fragColor = mix(texture(uniformTexture1, textureCoords), texture(uniformTexture2, textureCoords), 0.2) * vec4(color, 1.0f);

	vec3 _textureDiffuse = texture(uniformMaterial.diffuse1, textureCoords).rgb * color;
	vec3 _textureSpecular = texture(uniformMaterial.specular1, textureCoords).rgb  * color;

	float _ambientStrength = 1.0f;
	//vec3 _ambient = _ambientStrength * uniformLightColor;
	vec3 _ambient = uniformLight.ambient * _ambientStrength * _textureDiffuse;

	vec3 _normalizedNormal = normalize(normal);
	vec3 _lightDirection = normalize(uniformLight.position - fragPosition);
	float _diffuseAngle = max(dot(_normalizedNormal, _lightDirection), 0.0f);
	//vec3 _diffuse = uniformLightColor * _diffuseAngle;
	vec3 _diffuse = uniformLight.ambient * _textureDiffuse * _diffuseAngle;

	float _specularStrength = 0.5f;
	vec3 _viewDirection = normalize(uniformViewPosition - fragPosition);
	vec3 _reflectDirection = reflect(-_lightDirection, _normalizedNormal);
	float _specularAngle = pow(max(dot(_viewDirection, _reflectDirection), 0.0f), uniformMaterial.shininess);
	//vec3 _specular = _specularStrength * _specularAngle * uniformLightColor;
	vec3 _specular = uniformLight.specular * _specularStrength * _specularAngle * _textureSpecular;

	//vec3 _result = (_ambient + _diffuse + _specular) * color;
	vec3 _result = _ambient + _diffuse + _specular;
	fragColor = vec4(_textureDiffuse, 1.0f);

//	fragColor.rgb = pow(fragColor.rgb, vec3(1.0f / 1.0f));
}