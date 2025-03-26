#pragma once
#include "../Math/Vector3.h"
#include "../Utils/CoreMinimal.h"
#include "Managers/TextureManager.h"

#include <string>
#include "Shader.h"

class Texture
{
	friend TextureManager;

	//if the texturePath is set, we use it as the texture, else we use the textureValue. This is all determined after calling the constructor
	std::string texturePath; 
	Vector4f textureValue; 

	GLuint textureID;
	aiTextureType type;

private:
	Texture() = delete;
	/// <summary>
	/// You do not have access to the constructor, use the TextureManager::CreateTexture instead
	/// </summary>
	Texture(const char* _path, const aiTextureType& _textureType);
	/// <summary>
	/// You do not have access to the constructor, use the TextureManager::CreateTexture instead
	/// </summary>
	Texture(const std::string& _path, const aiTextureType& _textureType);
	/// <summary>
	/// You do not have access to the constructor, use the TextureManager::CreateTexture instead
	/// </summary>
	Texture(const Vector4f& _textureValue);

public:
	/// <summary>
	/// This is used for the texture manager
	/// </summary>
	/// <returns></returns>
	FORCEINLINE std::string GetStringKey() const { return texturePath.empty() ? textureValue.ToString() : texturePath; }

private:
	/// <summary>
	/// Load the texture during the construction of the object.
	/// Sets the member variable "textureID" insided the method
	/// </summary>
	/// <param name="_path">The path is the path relative from the "Texture" folder of the project</param>
	void LoadTexture(const char* _path);
	/// <summary>
	/// Load the texture during the construction of the object.
	/// Sets the member variable "textureID" insided the method
	/// </summary>
	/// <param name="_path">The value is used to create the texture, for example, when creating the base color, we could use a vec3 to set a uniform color as texture</param>
	void LoadTexture(const Vector4f& _value);

public:
	void Update(Shader* _shader);

};

