#include "Texture.h"
#include "../Common/stb_image.h"
#include "Managers/TextureManager.h"

Texture::Texture(const char* _path, const aiTextureType& _textureType)
{
	texturePath = std::string(_path);
	type = _textureType;
	LoadTexture(_path);
}

Texture::Texture(const std::string& _path, const aiTextureType& _textureType)
{
	texturePath = _path;
	type = _textureType;
	LoadTexture(_path.c_str());
}

Texture::Texture(const Vector4f& _textureValue)
{
	textureValue = _textureValue;
	LoadTexture(_textureValue);
}

void Texture::LoadTexture(const char* _path)
{
	glGenTextures(1, &textureID);

	// Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int _textureWidth;
	int _textureHeight;
	int _channelsCount;
	string _filePath = GetPath(TEXTURES) + _path;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* _data = stbi_load(_filePath.c_str(), &_textureWidth, &_textureHeight, &_channelsCount, 0);
	if (!_data)
		throw exception(("ERROR => Failed to load texture at: " + _filePath + "!").c_str());

	map<int, GLint> _formats =
	{
		{ 1, GL_RED },
		{ 3, GL_RGB },
		{ 4, GL_RGBA },
	};

	const GLint& _format = _formats[_channelsCount];
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, _format, _textureWidth, _textureHeight, 0, _format, GL_UNSIGNED_BYTE, _data);

	// Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(_data);
}

void Texture::LoadTexture(const Vector4f& _value)
{
	glGenTextures(1, &textureID);

	if (_value.w < 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, textureID);

	const vec4& _uniformColorTransparent = _value;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1, 1, 0, GL_RGBA, GL_FLOAT, &_uniformColorTransparent);

	}

	void Texture::Update(Shader* _shader)
	{
		glActiveTexture(GL_TEXTURE0); //TODO find out about this

		string _numberText;
		aiTextureType _type = type;

		string _textureName = "uniformMaterial.";
		switch (_type)
		{
		case aiTextureType_NONE:
			_textureName += "unknown";
			break;
		case aiTextureType_DIFFUSE:
			_textureName += "diffuse";
			break;
		case aiTextureType_SPECULAR:
			_textureName += "specular";
			break;
		case aiTextureType_AMBIENT:
			_textureName += "ambient";
			break;
		case aiTextureType_EMISSIVE:
			_textureName += "emissive";
			break;
		case aiTextureType_HEIGHT:
			_textureName += "height";
			break;
		case aiTextureType_NORMALS:
			break;
		case aiTextureType_SHININESS:
			break;
		case aiTextureType_OPACITY:
			break;
		case aiTextureType_DISPLACEMENT:
			break;
		case aiTextureType_LIGHTMAP:
			break;
		case aiTextureType_REFLECTION:
			break;
		case aiTextureType_BASE_COLOR:
			_textureName += "baseColor";
			break;
		case aiTextureType_NORMAL_CAMERA:
			_textureName += "normalCamera";
			break;
		case aiTextureType_EMISSION_COLOR:
			break;
		case aiTextureType_METALNESS:
			_textureName += "metallic";
			break;
		case aiTextureType_DIFFUSE_ROUGHNESS:
			break;
		case aiTextureType_AMBIENT_OCCLUSION:
			_textureName += "ambientOcclusion";
			break;
		case aiTextureType_UNKNOWN:
			break;
		case aiTextureType_SHEEN:
			break;
		case aiTextureType_CLEARCOAT:
			break;
		case aiTextureType_TRANSMISSION:
			break;
		case aiTextureType_MAYA_BASE:
			break;
		case aiTextureType_MAYA_SPECULAR:
			break;
		case aiTextureType_MAYA_SPECULAR_COLOR:
			break;
		case aiTextureType_MAYA_SPECULAR_ROUGHNESS:
			break;
		case aiTextureType_ANISOTROPY:
			break;
		case aiTextureType_GLTF_METALLIC_ROUGHNESS:
			break;
		case _aiTextureType_Force32Bit:
			break;
		default:
			break;
		}

		const GLuint& _uniformTextureID = glGetUniformLocation(_shader->GetShaderProgram(), (_textureName + _numberText).c_str());
		//glUniform1i(_uniformTextureID, _index);  //TODO find out about this
		glBindTexture(GL_TEXTURE_2D, textureID);
	}