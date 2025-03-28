#pragma once

#include "../Utils/CoreMinimal.h"
#include "../Manager/Singleton.h"


struct TextureData
{
	ImVec2 textureSize;
	ImTextureID textureID;

public:
	TextureData()
	{

	}
	TextureData(const ImVec2& _textureSize, const ImTextureID& _textureID)
	{
		textureSize = _textureSize;
		textureID = _textureID;
	}
};

class TextureManager : public Singleton<TextureManager>
{
	map<string, TextureData> allLoadedTextures;

public:
	TextureManager();
	virtual ~TextureManager() = default;

private:
	bool LoadTextureFromFile(const char* _fileName, GLuint* _outTexture, int* _outWidth, int* _outHeight);
	bool LoadTextureFromMemory(const void* _data, size_t _dataSize, GLuint* _outTexture, int* _outWidth, int* _outHeight);

public:
	void LoadTexture(const string& _path, TextureData& _texture);
};