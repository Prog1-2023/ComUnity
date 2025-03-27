#include "Material.h"
#include "Managers/TextureManager.h"
#include "Shader.h"

Material::Material(const char* _vertexPath, const char* _fragmentPath)
{
	shader = new Shader(_vertexPath, _fragmentPath); //TODO move into a ShaderManager
	albedo = nullptr;
	metallic = nullptr;
	ambientOcclusion = nullptr;
	normal = nullptr;
	specular = nullptr;
}

Material::~Material()
{
	delete shader; //TODO should not be there after having a shader manager
	shader = nullptr;
}

void Material::InitAlbedo(const std::string& _albedoTexturePath)
{
	albedo = InitTexture(_albedoTexturePath, aiTextureType_BASE_COLOR);
}

void Material::InitAlbedo(const Vector4f& _albedoTextureValue)
{
	albedo = InitTexture(_albedoTextureValue);
}

void Material::InitMetallic(const std::string& _metallicTexturePath)
{
	metallic = InitTexture(_metallicTexturePath, aiTextureType_METALNESS);
}

void Material::InitMetallic(const Vector4f& _metallicTextureValue)
{
	metallic = InitTexture(_metallicTextureValue);
}

void Material::InitAO(const std::string& _aoTexturePath)
{
	ambientOcclusion = InitTexture(_aoTexturePath, aiTextureType_AMBIENT_OCCLUSION);
}

void Material::InitAO(const Vector4f& _aoTextureValue)
{
	ambientOcclusion = InitTexture(_aoTextureValue);
}

void Material::InitNormal(const std::string& _normalTexturePath)
{
	normal = InitTexture(_normalTexturePath, aiTextureType_NORMAL_CAMERA);
}

void Material::InitNormal(const Vector4f& _normalTextureValue)
{
	normal = InitTexture(_normalTextureValue);
}

void Material::InitSpecular(const std::string& _specularTexturePath)
{
	specular = InitTexture(_specularTexturePath, aiTextureType_SPECULAR);
}

void Material::InitSpecular(const Vector4f& _specularTextureValue)
{
	specular = InitTexture(_specularTextureValue);
}

void Material::SetMVP(const mat4& _model, const mat4& _view, const mat4& _projection)
{
	if (!shader)return;
	shader->Use();
	shader->SetUniformVec4("uniformModel", _model);
	shader->SetUniformVec4("uniformView", _view);
	shader->SetUniformVec4("uniformProjection", _projection);
}

void Material::Update()
{
	//TODO find a way to clean the following up. But really...
	if (albedo)albedo->Update(shader);
	if (metallic)metallic->Update(shader);
	if (ambientOcclusion)ambientOcclusion->Update(shader);
	if (normal)normal->Update(shader);
	if (specular)specular->Update(shader);

}

Texture* Material::InitTexture(const std::string& _textureToLoadOrInit, const aiTextureType& _textureType)
{
	return TextureManager::CreateTexture(_textureToLoadOrInit, _textureType);
}

Texture* Material::InitTexture(const Vector4f& _textureValue)
{
	return TextureManager::CreateTexture(_textureValue);
}
