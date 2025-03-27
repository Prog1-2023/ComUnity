#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>


Shader::Shader(const char* _vertexPath, const char* _fragmentPath)
{
	Construct(std::string(_vertexPath), std::string(_fragmentPath));
}

Shader::Shader(const std::string& _vertexPath, const std::string& _fragmentPath)
{
	Construct(_vertexPath, _fragmentPath);
}

void Shader::Construct(const std::string& _vertexPath, const std::string& _fragmentPath)
{
	//Read shader files
	vertexShaderPath = _vertexPath;
	fragmentShaderPath = _fragmentPath;
	const string& _vShaderCodeStr = Shader::ReadShader(GetPath(FolderType::SHADERS) + _vertexPath);
	const string& _fShaderCodeStr = Shader::ReadShader(GetPath(FolderType::SHADERS) + _fragmentPath);
	const char* _vShaderCode = _vShaderCodeStr.c_str();
	const char* _fShaderCode = _fShaderCodeStr.c_str();


	//Compile shaders

	GLuint _vertex, _fragment;
	// Vertex shader
	_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertex, 1, &_vShaderCode, NULL);
	glCompileShader(_vertex);
	CheckCompileErrors(_vertex, "VERTEX");

	// fragment Shader
	_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragment, 1, &_fShaderCode, NULL);
	glCompileShader(_fragment);
	CheckCompileErrors(_fragment, "FRAGMENT");

	// shader Program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, _vertex);
	glAttachShader(shaderProgram, _fragment);
	glLinkProgram(shaderProgram);
	CheckCompileErrors(shaderProgram, "PROGRAM");

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(_vertex);
	glDeleteShader(_fragment);
}

std::string Shader::ReadShader(const char* _shaderPath)
{
	return ReadShader(std::string(_shaderPath));
}

std::string Shader::ReadShader(const std::string& _shaderPath)
{
	std::string _shaderContent;
	std::ifstream _shaderStream(_shaderPath, std::ios::in);
	try
	{
		if (!_shaderStream.is_open())
			throw std::exception(("Shader path not found (" + _shaderPath + ")!").c_str());
		std::stringstream _sstr;
		_sstr << _shaderStream.rdbuf();
		_shaderContent = _sstr.str();
		_shaderStream.close();
	}
	catch (const std::exception& _error)
	{
		std::cerr << _error.what() << std::endl;
	}
	return _shaderContent.c_str();
}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

void Shader::SetUniformBool(const std::string& _name, const bool _value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, _name.c_str()), (int)_value);
}

void Shader::SetUniformInt(const std::string& _name, const int _value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, _name.c_str()), _value);
}

void Shader::SetUniformFloat(const std::string& _name, const float _value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, _name.c_str()), _value);
}

void Shader::SetUniformVec4(const std::string& _name, const mat4& _matrice) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, _name.c_str()), 1, GL_FALSE, value_ptr(_matrice));
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
