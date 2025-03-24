#pragma once
#include "../Components/Component.h"
#include "../Utils/CoreMinimal.h"


#define MAX_BONES_INFLUENCE 4

struct Vertex
{
	Vector3f position;
	Vector3f normal;
	Vector2f textureCoords;
	Vector3f tangents;
	Vector3f biTangents;
	int bonesIDs[MAX_BONES_INFLUENCE];
	float weights[MAX_BONES_INFLUENCE];

	Vertex() = delete;
	Vertex(const Vector3f& _position,const Vector3f& _normal, const Vector2f& _textureCoords, const Vector3f& _tangents, const Vector3f& _biTangents)
	{
		position = _position;
		normal = _normal;
		textureCoords = _textureCoords;
		tangents = _tangents;
		biTangents = _biTangents;
	}
	Vertex(const Vertex& _other)
	{
		position = _other.position;
		normal = _other.normal;
		textureCoords = _other.textureCoords;
		tangents = _other.tangents;
		biTangents = _other.biTangents;
	}
};

struct Texture
{
	GLuint id;
	string path;
	aiTextureType type;

	Texture(const GLuint& _id, const string& _path, const aiTextureType& _type)
	{
		id = _id;
		path = _path;
		type = _type;
	}

};

class StaticMeshComponent : public Component
{
	//Vertex
	GLuint vertexArrayID;

	//Shader
	GLuint shaderProgram;
	string vertexShaderPath;
	string fragmentShaderPath;

	//Shape
	bool useColor;
	int verticesCount;
	int dimension;
	int coordsCount;
	//vector<Vertex> vertices;
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	//Buffers
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	//Matrix
	GLuint modelID;
	GLuint viewID;
	GLuint projectionID;

	//TODO move into Actor
	mat4 model;
	mat4 view;
	mat4 projection;

	//Textures
	map<string, GLuint> allTextures;

	//TODO move into TimerManager
	float elapsedTime;

	//TODO move into CameraManager
	vec3 camPos;

public:
	//TODO move into TimerManager
	FORCEINLINE void SetTime(const float _time) { elapsedTime = _time; }

	FORCEINLINE void SetMVP(const mat4& _model, const mat4& _view, const mat4& _projection)
	{
		glUseProgram(shaderProgram);
		SetUniformModel(_model);
		SetUniformView(_view);
		SetUniformProjection(_projection);
	}

	//TODO move into CameraManager
	FORCEINLINE void SetCamPos(const vec3& _pos) { camPos = _pos; }

	FORCEINLINE void SetUniformModel(const mat4& _model)
	{
		glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(_model));
	}
	FORCEINLINE void SetUniformView(const mat4& _view)
	{
		glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(_view));
	}
	FORCEINLINE void SetUniformProjection(const mat4& _projection)
	{
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(_projection));
	}
	FORCEINLINE GLuint GetShaderProgram() const { return shaderProgram; }



public:
	StaticMeshComponent(Actor* _owner);
	~StaticMeshComponent();

	void Init();
	virtual void Tick(const float _deltatime) override;
protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:

	void InitShaders();
	bool CheckShaderForErrors(const GLuint& _shader, const string& _shaderName);

	void InitShape();
	bool IsNearlyEqual(float _a, float _b, float _tolerance = numeric_limits<float>::epsilon());
	float RoundFloat(const float _value);
	bool Generate2DShape();
	void AddEdge(std::set<std::pair<GLuint, GLuint>>& indices, GLuint vertex1, GLuint vertex2);
	bool Generate3DShape();
	vector<Texture> LoadTextures(aiMaterial* _material, const aiTextureType& _type);

	void InitBuffers();

	void InitTextures();
	GLuint LoadTexture(const string& _filePath);

	void InitLighting();

	void UpdateColors();
	void UpdateTextures();


	void Clear();

public:
	void GenerateShapeFromModel(aiMesh* _mesh, const aiScene* _scene);
	void Draw();
	void SetModel(const mat4& _model);
	void SetView(const mat4& _view);
	void SetProjection(const mat4& _projection);
};

template <typename RetType = void*, typename Type = GLfloat>
RetType SizeOf(const int _count = 1)
{
	return (RetType)(_count * sizeof(Type));
}