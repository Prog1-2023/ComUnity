#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 ABiTangent;
layout (location = 5) in int[] aID;
layout (location = 6) in float[] aWeight;

out vec3 color;
out vec2 textureCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformProjection;

void main()
{
	fragPos = vec3(uniformModel * vec4(aPos,1.0));

	gl_Position = uniformProjection * uniformView * vec4(fragPos, 1.0f);

	color = vec3(1.0f);
	textureCoords = aTexture;
	//normal = aNormal;
	normal = mat3(transpose(inverse(uniformModel))) * aNormal;
};