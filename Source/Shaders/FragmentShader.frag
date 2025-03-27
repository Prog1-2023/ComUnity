#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 color;
in vec2 textureCoords;
in vec3 fragPos;
in vec3 normal;


uniform vec3 uniformLightPosition;
uniform vec3 uniformViewPosition;
uniform vec3 uniformLightColor;
uniform Material uniformMaterial;
uniform Light uniformLight;

out vec4 fragColor;

 void main() 
 { 
      vec3 _textureDiffuse = texture(uniformMaterial.diffuse, textureCoords).rgb;
      vec3 _textureSpecular = texture(uniformMaterial.specular, textureCoords).rgb;

      // Ambient
      float _ambientStrenght = 0.1f;
//      vec3 _ambient = uniformLightColor * _ambientStrenght;
      vec3 _ambient = _textureDiffuse * uniformLight.ambient;

      // Diffuse
      vec3 _norm = normalize(normal);
      vec3 _lightDir = normalize(uniformLight.position - fragPos);
      float _diff = max(dot(_norm, _lightDir), 0.0);
//      vec3 _diffuse = _diff * uniformLightColor;
      vec3 _diffuse = uniformLight.diffuse * _diff * _textureDiffuse;
      
      // Specular
      float _specularStrength = 1.0f;
      vec3 _viewDirection = normalize(uniformViewPosition - fragPos);
      vec3 _reflectDirection = reflect(-_lightDir, _norm);
      float _spec = pow(max(dot(_viewDirection, _reflectDirection), 0.0), uniformMaterial.shininess);
      vec3 _specular = uniformLight.specular * _spec * _textureSpecular;

      //fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); //Couleur statique
      //fragColor = uniformColor; //Couleur unie
      //fragColor = vec4(color * vec3(0.0f, 0=1.0f, 0.0f) 1.0f); // Couleur par vertices
      //fragColor = mix(texture(uniformTexture1, textureCoords), texture(uniformTexture2, textureCoords), 0.2) * vec4(color, 1.0f);

      //Phong
//      vec3 _result = (_ambient + _specular) * color;
//      vec3 _result = (_ambient + _diffuse + _specular) * color;
//      fragColor = texture(uniformTexture1, textureCoords) * vec4(_result, 1.0f);
       vec3 _result = (_ambient + _diffuse + _specular) * color;
       fragColor = vec4(_result, 1.0f);
 };