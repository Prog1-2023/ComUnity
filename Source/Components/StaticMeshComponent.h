#pragma once
#include "../Utils/CoreMinimal.h"
#include "Component.h"
#include "../NewLightRelated/Texture.h"
#include "../NewLightRelated/Material.h"
#include "../Actors/Transform.h"
#include"../Components/ITransformableModifier.h"
#include"../Components/ITransformableViewer.h"

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

class StaticMeshComponent : public Component, public ITransformableModifier, public ITransformableViewer
{
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

	Transform offsetTransform;

	// TODO get from cameraManager
	vec3 cameraLocation;

public:
	FORCEINLINE void SetMVP(const mat4& _model, const mat4& _view, const mat4& _projection)
	{
		material->SetMVP(_model, _view, _projection);
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

	FORCEINLINE Transform* GetTransform() { return &offsetTransform; }

	FORCEINLINE Material* GetMaterial() const { 

		return material; 
	}

public:
	FORCEINLINE virtual Component* Clone(Actor* _owner) const override
	{
		return new StaticMeshComponent(_owner, *this);
	}


public:
	StaticMeshComponent(Actor* _owner);
	StaticMeshComponent(Actor* _owner, StaticMeshComponent _other);
	void LoadModel(const string& _path);
	void ComputeMeshes(const aiScene* _scene, const aiNode* _node);
	virtual ~StaticMeshComponent() override;

	virtual void Construct() override;
	virtual void Deconstruct() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

private:
	vector<Texture> LoadTextures(aiMaterial* _material, const aiTextureType& _type);
	float RoundFloat(const float& _value);
	bool IsNearlyEqual(const float& _a, const float& _b, const float& _tolerance = numeric_limits<float>::epsilon());
	void InitBuffers();
	void InitTextures();
	GLuint LoadTexture(const string& _filePath);
	bool CheckShaderForErrors(const GLuint& _shader, const string& _shaderName);
	void Draw();

public:
	void Init();
	void GenerateShapeFromModel(aiMesh* _mesh, const aiScene* _scene);
	void Update();
	void Clear();



	// Hérité via ITransformableModifier
	void SetPosition(const Vector3f& _position) override;

	void SetRotation(const Vector3f& _rotation) override;

	void SetScale(const Vector3f& _scale) override;

	void Move(const Vector3f& _offset) override;

	void Rotate(const Vector3f& _angle) override;

	void Scale(const Vector3f& _factor) override;


	// Hérité via ITransformableViewer
	Vector3f GetPosition() const override;

	Vector3f GetRotation() const override;

	Vector3f GetScale() const override;

	Transform GetTransform() const override;


};

template <typename ReturnType = void*, typename Type = GLfloat>
ReturnType SizeOf(const int& _value = 1)
{
	return (ReturnType)(_value * sizeof(Type));
}