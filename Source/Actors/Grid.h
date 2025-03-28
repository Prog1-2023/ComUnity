#pragma once
#include "../Utils/CoreMinimal.h"
#include "Actor.h"

class Grid : public Actor
{
	vector<float> vertices;
	int gridSize;
	float spacing;

	GLuint shaderProgram;
	GLuint VAO;
	GLuint VBO;

	GLuint modelID;
	GLuint viewID;
	GLuint projectionID;

	string vertexShaderPath;
	string fragmentShaderPath;

public:

	Grid(Level* _level);

	FORCEINLINE void SetMVP(const mat4& _model,const mat4& _view, const mat4& _projection)
	{
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(_model));
		glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(_view));
		glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(_projection));
	}


private:
	void GenerateGridVertices();
	void Reset();
	void InitShader();
	void InitBuffers();
	unsigned int CreateShader(const string& _shaderPath, const bool& _isVertex);
	bool CheckShaderForErrors(const GLuint& _shader, const string& _shaderName);

	virtual void Tick(const float _deltaTime) override;

public:
	void Draw();

public:
	void Init(const int& _gridSize,const float& _spacing);

};