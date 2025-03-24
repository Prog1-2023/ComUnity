#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
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
in vec3 fragPos;

uniform vec4 uniformColor;
uniform vec3 uniformLightColor;
uniform vec3 uniformLightPos;
uniform vec3 uniformViewPos;
uniform Material uniformMaterial;
uniform Light uniformLight;

out vec4 fragColor;

void main()
{
    vec3 _textureDiffuse = texture(uniformMaterial.diffuse, textureCoords).rgb;
    vec3 _textureSpecular = texture(uniformMaterial.specular, textureCoords).rgb;

    // ambient
    float _ambiantStrength = 0.5f;
//    vec3 _ambient = uniformLightColor * texture(uniformMaterial.diffuse, textureCoords).rgb * _ambiantStrength;
    vec3 _ambient = uniformLight.ambient * _textureDiffuse * _ambiantStrength;
  	
    // diffuse 
    vec3 _norm = normalize(normal);
    vec3 _lightDir = normalize(uniformLight.position - fragPos);
    float _diff = max(dot(_norm, _lightDir), 0.0);
//    vec3 _diffuse = uniformLightColor * _diff;
    vec3 _diffuse = uniformLight.diffuse * _textureDiffuse * _diff;
    
    // specular
    float _specularStrength = 0.5f;
    vec3 _viewDir = normalize(uniformViewPos - fragPos);
    vec3 _reflectDir = reflect(-_lightDir, _norm);  
    float _specAngle = pow(max(dot(_viewDir, _reflectDir), 0.0), uniformMaterial.shininess);
    vec3 _specular = uniformLight.specular * _textureSpecular * _specularStrength * _specAngle;
        
    vec3 result = (_ambient + _diffuse + _specular);
    fragColor = vec4(result, 1.0);

	//fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // couleur statique
	//fragColor = uniformColor; // => couleur unie
	//fragColor = vec4(color, 1.0f) * uniformColor; // => couleur par vertices
    //fragColor = mix(texture(uniformTexture1, textureCoords), texture(uniformTexture2, textureCoords), 0.2) * vec4(color, 1.0f); 
};