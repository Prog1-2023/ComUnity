#pragma once
#include "../Utils/CoreMinimal.h"


class Shader
{
	GLuint shaderProgram; //ikr could have named just "program"
	std::string vertexShaderPath;
	std::string fragmentShaderPath;

public:
	Shader(const char* _vertexPath, const char* _fragmentPath);
	Shader(const std::string& _vertexPath, const std::string& _fragmentPath);
	
public:
	GLuint GetShaderProgram() const { return shaderProgram; }

private:
	void Construct(const std::string& _vertexPath, const std::string& _fragmentPath);

public:
	static std::string ReadShader(const char* _shaderPath);
	static std::string ReadShader(const std::string& _shaderPath);

public:
	void Use();
	void SetUniformBool(const std::string& _name, const bool _value)const;
	void SetUniformInt(const std::string& _name, const int _value)const;
	void SetUniformFloat(const std::string& _name, const float _value)const;
	void SetUniformVec4(const std::string& _name, const mat4& _matrice)const;

	void InitShader();
private:
    // Utility function for checking shader compilation/linking errors. (YES)
    // ------------------------------------------------------------------------
	void CheckCompileErrors(unsigned int shader, std::string type);
  
};

