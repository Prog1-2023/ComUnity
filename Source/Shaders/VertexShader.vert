#version 330 core

// layout (location = 1) in vec3 aColor;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in int[] aIDs;
layout (location = 6) in float[] aWeights;

out vec3 color;
out vec2 textureCoords;
out vec3 normal;
out vec3 fragPosition;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformProjection;

void main()
{
	fragPosition = vec3(uniformModel * vec4(aPos, 1.0f));
	gl_Position = uniformProjection * uniformView * vec4(fragPosition, 1.0f);
	//color = aColor;
	textureCoords = aTexture;
	normal = aNormal;
	//normal = mat3(transpose(inverse(uniformModel))) * aNormal;
}