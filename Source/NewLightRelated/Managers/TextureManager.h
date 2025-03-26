#pragma once
#include "../../Utils/CoreMinimal.h"
#include <string>

class Texture;

class TextureManager
{

public:
	static TextureManager& GetInstance()
	{
		static TextureManager s_instance;
		return s_instance;
	}

private:
	TextureManager() = default;
	~TextureManager();

private:
	std::map<std::string, Texture*> allTextures;

public:
	/// <summary>
	/// Construct a texture using a path
	/// </summary>
	/// <param name="_path">The path is the path relative from the "Texture" folder of the project</param>
	static Texture* CreateTexture(const char* _path, const aiTextureType& _textureType) { return GetInstance().InternCreateTexture(_path, _textureType); }
	/// <summary>
	/// Construct a texture using a path
	/// </summary>
	/// <param name="_path">The path is the path relative from the "Texture" folder of the project</param>
	static Texture* CreateTexture(const std::string& _path, const aiTextureType& _textureType) { return GetInstance().InternCreateTexture(_path, _textureType); }
	/// <summary>
	/// Construct a texture using a vector4, just like in unreal. 
	/// </summary>
	static Texture* CreateTexture(const Vector4f& _textureValue) { return GetInstance().InternCreateTexture(_textureValue); }

	static Texture* GetTexture(const std::string& _key) { return GetInstance().GetTexture(_key); }

	/// <summary>
	/// Add a texture if it's not already in the texture manager
	/// </summary>
	static void AddUniqueTexture(Texture* _textureToAdd) { GetInstance().InternalAddUniqueTexture(_textureToAdd); }

	/// <summary>
	/// Return if the texture is registered in the manager
	/// </summary>
	static bool Exists(Texture* _texture) { return GetInstance().InternalExists(_texture); }
	/// <summary>
	/// Return if the texture is registered in the manager
	/// </summary>
	static bool Exists(const std::string& _key) { return GetInstance().InternalExists(_key); }

	/// <summary>
	/// Deletes the texture
	/// </summary>
	static void Delete(Texture* _texture) { GetInstance().InternalDelete(_texture); }
	/// <summary>
	/// Deletes the texture
	/// </summary>
	static void Delete(const std::string& _key) { GetInstance().InternalDelete(_key); }
	/// <summary>
	/// Deletes all textures registered in the manager
	/// </summary>
	static void DeleteAll() { GetInstance().InternalDeleteAll(); }

	/// <summary>
	/// This methods removes the item from the map without destroying it, if you wish to destroy the item aswell, use Delete instead.
	/// </summary>
	/// <param name="_texture">The texture to delete and remove from map</param>
	static void Remove(Texture* _texture) { GetInstance().InternalRemove(_texture); }
	/// <summary>
	/// This methods removes the item from the map without destroying it, if you wish to destroy the item aswell, use Delete instead.
	/// </summary>
	/// <param name="_texture">The key of the texture to delete and remove from map</param>
	static void Remove(const std::string& _key) { GetInstance().InternalRemove(_key); }


private:
	Texture* InternCreateTexture(const char* _path, const aiTextureType& _textureType);

	Texture* InternCreateTexture(const std::string& _path, const aiTextureType& _textureType);

	Texture* InternCreateTexture(const Vector4f& _textureValue);
	/// <summary>
	/// Retrieve the texture, the key is either the relative path from the Texture folder, or the Vector4f.ToString()
	/// </summary>
	/// <param name="_key">The string key described above</param>
	/// <returns></returns>
	Texture* InternalGetTexture(const std::string& _key);

	/// <summary>
	/// Add a texture if it's not already in the texture manager
	/// </summary>
	void InternalAddUniqueTexture(Texture* _textureToAdd);

	/// <summary>
	/// Return if the texture is registered in the manager
	/// </summary>
	bool InternalExists(Texture* _texture);
	/// <summary>
	/// Return if the texture is registered in the manager
	/// </summary>
	bool InternalExists(const std::string& _key);

	/// <summary>
	/// Deletes the texture
	/// </summary>
	void InternalDelete(Texture* _texture);
	/// <summary>
	/// Deletes the texture
	/// </summary>
	void InternalDelete(const std::string& _key);
	/// <summary>
	/// Deletes all textures registered in the manager
	/// </summary>
	void InternalDeleteAll();

	/// <summary>
	/// This methods removes the item from the map without destroying it, if you wish to destroy the item aswell, use Delete instead.
	/// </summary>
	/// <param name="_texture">The texture to delete and remove from map</param>
	void InternalRemove(Texture* _texture);
	/// <summary>
	/// This methods removes the item from the map without destroying it, if you wish to destroy the item aswell, use Delete instead.
	/// </summary>
	/// <param name="_texture">The key of the texture to delete and remove from map</param>
	void InternalRemove(const std::string& _key);


private:
};
