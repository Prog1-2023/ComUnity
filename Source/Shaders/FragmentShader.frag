#version 330 core
//uniform vec4 uniformColor;
//uniform sampler2D uniformTexture2;

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

//uniform vec3 uniformLightColor;
uniform vec3 uniformViewPosition;
uniform Material uniformMaterial;
uniform Light uniformLight;

out vec4 fragColor;

void main()
{
    //fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // couleur statique
    //fragColor = uniformColor; // => couleuyr unie
    //fragColor = vec4(color, 1.0f) * uniformColor; // => couleur par vertices
    //fragColor = mix(texture(uniformTexture1, textureCoords), texture(uniformTexture2, textureCoords), 0.2) * vec4(color, 1.0f);
    
    vec3 _textureDiffuse = texture(uniformMaterial.diffuse, textureCoords).rgb;
    vec3 _textureSpecular = texture(uniformMaterial.specular, textureCoords).rgb;

    // Ambiant
    float _ambiantStrength = 0.2f;
    //vec3 _ambiant = uniformLightColor * _ambiantStrength;
    vec3 _ambiant = uniformLight.ambient * _textureDiffuse * _ambiantStrength;

    // Diffuse
    vec3 _normalizedNormal = normalize(normal);
    vec3 _lightDirection = normalize(uniformLight.position - fragPos);
    float _diffuseAngle = max(dot(_normalizedNormal, _lightDirection), 0.0f);
    //vec3 _diffuse = uniformLightColor * _diffuseAngle;
    vec3 _diffuse = uniformLight.diffuse * _textureDiffuse * _diffuseAngle;

    // Specular
    float _specularStrength = 1.0f;
    vec3 _viewDirection = normalize(uniformViewPosition - fragPos);
    vec3 _reflectDirection = reflect(-_lightDirection, _normalizedNormal);
    float _specularAngle = pow(max(dot(_viewDirection, _reflectDirection), 0.0f), uniformMaterial.shininess);
    vec3 _specular = _textureSpecular * _specularStrength * _specularAngle;
    
    // Phong
    //vec3 _result = (_ambiant + _diffuse + _specular) * color;
    vec3 _result = vec3(1.0f , 0.0f , 0.0f) ;//* color;
    fragColor = vec4(_result, 1.0f);
    //fragColor = texture(uniformTexture1, textureCoords) * vec4(_result, 1.0f);

    fragColor.rgb = pow(fragColor.rgb, vec3(1.0f / 1.0f));
};