#pragma once
#include "../Utils/CoreMinimal.h"
#include "Texture.h"
#include "Shader.h"

class Material
{
	Shader* shader;

	Texture* albedo;
	Texture* metallic;
	Texture* ambientOcclusion;
	Texture* normal;
	Texture* specular;

public:
	Material() = delete;
	Material(const char* _vertexPath, const char* _fragmentPath);
	~Material();

public:
	FORCEINLINE Shader* GetShader() const { return shader; }

public:
	/// <summary>
	/// Init the albedo
	/// </summary>
	/// <param name="_albedoTexturePath">Path RELATIVE from the Texture folder</param>
	void InitAlbedo(const std::string& _albedoTexturePath);
	void InitAlbedo(const Vector4f& _albedoTextureValue);

	/// <summary>
	/// Init the metallic
	/// </summary>
	/// <param name="_albedoTexturePath">Path RELATIVE from the Texture folder</param>
	void InitMetallic(const std::string& _metallicTexturePath);
	void InitMetallic(const Vector4f& _metallicTextureValue);

	/// <summary>
	/// Init the ambient occlusion
	/// </summary>
	/// <param name="_albedoTexturePath">Path RELATIVE from the Texture folder</param>
	void InitAO(const std::string& _aoTexturePath);
	void InitAO(const Vector4f& _aoTextureValue);

	/// <summary>
	/// Init the normal
	/// </summary>
	/// <param name="_albedoTexturePath">Path RELATIVE from the Texture folder</param>
	void InitNormal(const std::string& _normalTexturePath);
	void InitNormal(const Vector4f& _normalTextureValue);

	/// <summary>
	/// Init the specular
	/// </summary>
	/// <param name="_albedoTexturePath">Path RELATIVE from the Texture folder</param>
	void InitSpecular(const std::string& _specularTexturePath);
	void InitSpecular(const Vector4f& _specularTextureValue);
	
	void SetMVP(const mat4& _model, const mat4& _view, const mat4& _projection);

	void Update();

private:
	Texture* InitTexture(const std::string& _textureToLoadOrInit, const aiTextureType& _textureType);
	Texture* InitTexture(const Vector4f& _textureValue);
};


