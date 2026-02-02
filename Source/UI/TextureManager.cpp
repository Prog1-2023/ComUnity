#include "TextureManager.h"

#include "Log.h"

TextureManager::TextureManager()
{
	allLoadedTextures = map<string, TextureData>();
}

bool TextureManager::LoadTextureFromFile(const char* _fileName, GLuint* _outTexture, int* _outWidth, int* _outHeight)
{
	FILE* _file = fopen(_fileName, "rb");
	if (_file == NULL)
		return false;
	fseek(_file, 0, SEEK_END);
	size_t _fileSize = (size_t)ftell(_file);
	if (_fileSize == -1)
		return false;
	fseek(_file, 0, SEEK_SET);
	void* _fileData = IM_ALLOC(_fileSize);
	fread(_fileData, 1, _fileSize, _file);
	fclose(_file);
	bool _ret = LoadTextureFromMemory(_fileData, _fileSize, _outTexture, _outWidth, _outHeight);
	IM_FREE(_fileData);
	return true;
}

bool TextureManager::LoadTextureFromMemory(const void* _data, size_t _dataSize, GLuint* _outTexture, int* _outWidth, int* _outHeight)
{
	int _imageWidth = 0;
	int _imageHeight = 0;
	unsigned char* _imageData = stbi_load_from_memory((const unsigned char*)_data, (int)_dataSize, &_imageWidth, &_imageHeight, NULL, 4);
	if (_imageData == NULL)
		return false;

	GLuint _imageTexture;
	glGenTextures(1, &_imageTexture);
	glBindTexture(GL_TEXTURE_2D, _imageTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _imageWidth, _imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, _imageData);
	stbi_image_free(_imageData);

	*_outTexture = _imageTexture;
	*_outWidth = _imageWidth;
	*_outHeight = _imageHeight;

	return true;
}

void TextureManager::LoadTexture(const string& _path, TextureData& _texture)
{
	if (allLoadedTextures.contains(_path))
	{
		const TextureData& _data = allLoadedTextures[_path];
		_texture.textureSize = _data.textureSize;
		_texture.textureID = _data.textureID;
		return;
	}
	int _textureWidth = 0;
	int _textureHeight = 0;
	GLuint _textureTexture = 0;
	bool _ret = LoadTextureFromFile(_path.c_str(), &_textureTexture, &_textureWidth, &_textureHeight);
	if (!_ret)
	{
		LOG_ERROR("Couldn't load texture");
		return;
	}
	_texture.textureSize = ImVec2(_textureWidth, _textureHeight);
	_texture.textureID = (ImTextureID)(intptr_t)_textureTexture;
	allLoadedTextures[_path] = TextureData(_texture.textureSize, _texture.textureID);
}
