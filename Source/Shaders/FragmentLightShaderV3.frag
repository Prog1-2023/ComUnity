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

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};


uniform Material uniformMaterial;

uniform DirLight uniformDirLight[5];
uniform PointLight uniformPointLight[5];
uniform SpotLight uniformSpotLight[5];

uniform int uniformDirectionalCount;
uniform int uniformPointCount;
uniform int uniformSpotCount;


uniform vec3 viewPos;

out vec4 fragColor;
in vec3 fragPos;
in vec2 textureCoords;
in vec3 normal;

vec3 result;

void ComputeDirLight(DirLight _light, vec3 _normal, vec3 _viewDir);
void ComputePointLight(PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);
void ComputeSpotLight(SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);

void main()
{
    result = vec3(0.0f);

    vec3 _normal = normalize(normal);
    vec3 _viewDir = normalize(viewPos - fragPos);

    //DirectionalLight
    for(int i = 0; i < uniformDirectionalCount; i++)
        ComputeDirLight(uniformDirLight[i], _normal, _viewDir);
    //PointLight
    for(int i = 0; i < uniformPointCount; i++)
        ComputePointLight(uniformPointLight[i], _normal, fragPos ,_viewDir);
    //SpotLight
    for(int i = 0; i < uniformSpotCount; i++)
        ComputeSpotLight(uniformSpotLight[i], _normal, fragPos ,_viewDir);

    fragColor = vec4(result, 1.0f) * texture(uniformMaterial.baseColor, textureCoords);

};

void ComputeDirLight(DirLight _light, vec3 _normal, vec3 _viewDir)
{
    vec3 _lightDir = normalize(-_light.direction);

    //diffuse 
     float _diff = max(dot(_normal, _lightDir), 0.0);
    //specular
    vec3 _reflectDir = reflect(-_lightDir, _normal);
    float _spec = pow(max(dot(_viewDir, _reflectDir), 0.0), uniformMaterial.shininess);
    //combine
    vec3 ambient = (_light.ambient *0.1)* texture(uniformMaterial.baseColor, textureCoords).rgb;
    vec3 diffuse = _light.diffuse *  _diff * texture(uniformMaterial.baseColor, textureCoords).rgb;
    vec3 specular = _light.specular * _spec * texture(uniformMaterial.specular, textureCoords).rgb;
    result += (ambient + diffuse + specular );
}

void ComputePointLight(PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
    vec3 _lightDir = normalize(_light.position - fragPos);
    // diffuse shading
    float _diff = max(dot(_normal, _lightDir), 0.0);
    // specular shading
    vec3 _reflectDir = reflect(-_lightDir, _normal);
    float _spec = pow(max(dot(_viewDir, _reflectDir), 0.0), uniformMaterial.shininess);
    // attenuation
    float _distance = length(_light.position - fragPos);
    float attenuation = 1.0 / (_light.constant + _light.linear * _distance + _light.quadratic * (_distance * _distance));    
    // combine results
    vec3 ambient = _light.ambient * texture(uniformMaterial.baseColor, textureCoords).rgb;
    vec3 diffuse = _light.diffuse * _diff * texture(uniformMaterial.baseColor, textureCoords).rgb;
    vec3 specular = _light.specular * _spec * texture(uniformMaterial.specular, textureCoords).rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    result += (ambient + diffuse + specular);
}

void ComputeSpotLight(SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
    vec3 _lightDir = normalize(_light.position - _fragPos);
    // diffuse shading
    float _diff = max(dot(_normal, _lightDir), 0.0);
    // specular shading
    vec3 _reflectDir = reflect(-_lightDir, _normal);
    float _spec = pow(max(dot(_viewDir, _reflectDir), 0.0), uniformMaterial.shininess);
    // attenuation
    float _distance = length(_light.position - _fragPos);
    float _attenuation = 1.0 / (_light.constant + _light.linear * _distance + _light.quadratic * (_distance * _distance));    
    // spotlight intensity
    float _theta = dot(_lightDir, normalize(-_light.direction)); 
    float _epsilon = _light.cutOff - _light.outerCutOff;
    float _intensity = clamp((_theta - _light.outerCutOff) / _epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = _light.ambient * texture(uniformMaterial.baseColor, textureCoords).rgb;
    vec3 diffuse = _light.diffuse * _diff * texture(uniformMaterial.baseColor, textureCoords).rgb;
    vec3 specular = _light.specular * _spec * texture(uniformMaterial.specular, textureCoords).rgb;
    ambient *= _attenuation * _intensity;
    diffuse *= _attenuation * _intensity;
    specular *= _attenuation * _intensity;
    result += (ambient + diffuse + specular);
}