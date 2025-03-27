#include "TextureManager.h"
#include "../Texture.h"

TextureManager::~TextureManager()
{
	InternalDeleteAll();

}

void TextureManager::InternalAddUniqueTexture(Texture* _textureToAdd)
{
	if (InternalExists(_textureToAdd))return;
	allTextures.emplace(_textureToAdd->GetStringKey(), _textureToAdd);
}

bool TextureManager::InternalExists(Texture* _texture)
{
	return _texture ? InternalExists(_texture->GetStringKey()) : false;
}

bool TextureManager::InternalExists(const std::string& _key)
{
	return allTextures.find(_key) != allTextures.end();
}

void TextureManager::InternalDelete(Texture* _texture)
{
	if (!_texture)return;
	InternalDelete(_texture->GetStringKey());
}

void TextureManager::InternalDelete(const std::string& _key)
{
	if (!InternalExists(_key))return;
	Texture* _toRemove = InternalGetTexture(_key);
	delete _toRemove;
	_toRemove = nullptr;
	InternalRemove(_key);
}

void TextureManager::InternalDeleteAll()
{
	for (std::pair<std::string, Texture*> _texture : allTextures)
	{
		delete _texture.second;
		_texture.second = nullptr;
	}
	allTextures.clear();
}

void TextureManager::InternalRemove(Texture* _texture)
{
	if (!_texture)return;
	InternalRemove(_texture->GetStringKey());
}

void TextureManager::InternalRemove(const std::string& _key)
{
	if (!InternalExists(_key))return;
	allTextures.erase(_key);
}

Texture* TextureManager::InternalGetTexture(const std::string& _key)
{
	return Exists(_key) ? allTextures[_key] : nullptr;
}


Texture* TextureManager::InternCreateTexture(const char* _path, const aiTextureType& _textureType)
{
	return InternCreateTexture(std::string(_path), _textureType);
}

Texture* TextureManager::InternCreateTexture(const std::string& _path, const aiTextureType& _textureType)
{
	if (Exists(_path)) return InternalGetTexture(_path);
	Texture* _toReturn = new Texture(_path, _textureType);
	AddUniqueTexture(_toReturn);
	return _toReturn;
}

Texture* TextureManager::InternCreateTexture(const Vector4f& _textureValue)
{
	const std::string& _key = _textureValue.ToString();
	if (Exists(_key)) return InternalGetTexture(_key);
	Texture* _toReturn = new Texture(_textureValue);
	AddUniqueTexture(_toReturn);
	return _toReturn;
}

