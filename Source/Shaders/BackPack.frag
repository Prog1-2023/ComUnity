#version 330 core

uniform sampler2D uniformDiffuseTexture1;
in vec2 textureCoords;
out vec4 fragColor;

void main()
{
	fragColor = texture(uniformDiffuseTexture1, textureCoords);
}