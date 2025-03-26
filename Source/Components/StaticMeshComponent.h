#pragma once
#include "../Utils/CoreMinimal.h"
#include "Component.h"
#include "../NewLightRelated/Texture.h"
#include "../NewLightRelated/Material.h"

class Actor;

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	Vector3f position;
	Vector3f normal;
	Vector2f textureCoords;
	Vector3f tangent;
	Vector3f bitangent;
	int boneIDs[MAX_BONE_INFLUENCE];
	float weights[MAX_BONE_INFLUENCE];

	Vertex() = delete;
	Vertex(const Vector3f& _position, const Vector3f& _normal, const Vector2f& _textureCoords, const Vector3f& _tangent, const Vector3f& _bitangent)
	{
		position = _position;
		normal = _normal;
		textureCoords = _textureCoords;
		tangent = _tangent;
		bitangent = _bitangent;
	}
	Vertex(const Vertex& _other)
	{
		position = _other.position;
		normal = _other.normal;
		textureCoords = _other.textureCoords;
		tangent = _other.tangent;
		bitangent = _other.bitangent;
	}
};

//struct Texture
//{
//	GLuint id;
//	string path;
//	aiTextureType type;
//
//	Texture(const GLuint& _id, const string& _path, const aiTextureType& _type)
//	{
//		id = _id;
//		path = _path;
//		type = _type;
//	}
//};

class StaticMeshComponent : public Component
{
	//GLuint vertexArrayID;

	GLuint shaderProgram;
	string vertexShaderPath;
	string fragmentShaderPath;

	vector<GLfloat> lightColor;
	bool rainbowColor;
	bool rainbowLight;
	bool useTextures;
	int verticesCount;
	int dimension;
	int vertexDataSize;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	mat4 model;
	mat4 view;
	mat4 projection;

	GLuint modelID;
	GLuint viewID;
	GLuint projectionID;

	Material* material;

	map<string, GLuint> allTextures;

	// TODO get from cameraManager
	vec3 cameraLocation;

public:
	FORCEINLINE void SetMVP(const mat4& _model, const mat4& _view, const mat4& _projection)
	{
		glUseProgram(shaderProgram);
		material->SetMVP(_model, _view, _projection);
		/*SetUniformModelMatrix(_model);
		SetUniformViewMatrix(_view);
		SetUniformProjectionMatrix(_projection);*/
	}
	FORCEINLINE void SetUniformModelMatrix(const mat4& _model)
	{
		glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(_model));
	}
	FORCEINLINE void SetUniformViewMatrix(const mat4& _view)
	{
		glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(_view));
	}
	FORCEINLINE void SetUniformProjectionMatrix(const mat4& _projection)
	{
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(_projection));
	}
	FORCEINLINE GLuint GetShaderProgram() { return shaderProgram; }

	FORCEINLINE void SetCameraLocation(const vec3& _cameraLocation) { cameraLocation = _cameraLocation; }

public:
	StaticMeshComponent(Actor* _owner);
	~StaticMeshComponent() = default;

protected:
	virtual void BeginPlay();
	virtual void Tick(const float& _deltaTime) override;
	virtual void BeginDestroy();

private:
	void InitShaders();
	void InitShape();
	bool Generate2DShape(const vector<float> _outerColor, const vector<float> _innerColor);
	vector<Texture> LoadTextures(aiMaterial* _material, const aiTextureType& _type);
	bool Generate3DShape(const vector<float> _color);
	float RoundFloat(const float& _value);
	bool IsNearlyEqual(const float& _a, const float& _b, const float& _tolerance = numeric_limits<float>::epsilon());
	void InitBuffers();
	void InitTextures();
	GLuint LoadTexture(const string& _filePath);
	bool CheckShaderForErrors(const GLuint& _shader, const string& _shaderName);
	void UpdateColors();
	void UpdateTextures();
	void Draw();

public:
	void Init();
	void GenerateShapeFromModel(aiMesh* _mesh, const aiScene* _scene);
	void Update();
	void Clear();
};

template <typename ReturnType = void*, typename Type = GLfloat>
ReturnType SizeOf(const int& _value = 1)
{
	return (ReturnType)(_value * sizeof(Type));
}