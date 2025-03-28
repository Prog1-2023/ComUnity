#include "StaticMeshComponent.h"
#include "../Managers/LightManager.h"

static vector<Texture> texturesLoaded;

unsigned int CreateShader(const string& _shaderPath, const bool& _isVertex)
{
	unsigned int _shader = glCreateShader(_isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	const string& _shaderCode = Shader::ReadShader(GetPath(SHADERS) + _shaderPath);
	const char* _shaderData = _shaderCode.c_str();
	glShaderSource(_shader, 1, &_shaderData, NULL);
	glCompileShader(_shader);
	return _shader;
}

bool StaticMeshComponent::CheckShaderForErrors(const GLuint& _shader, const string& _shaderName)
{
	int _success;
	char _logs[512];

	glGetShaderiv(_shader, GL_COMPILE_STATUS, &_success);

	if (!_success)
	{
		glGetShaderInfoLog(_shader, 512, NULL, _logs);
		cerr << "Error => Init " + _shaderName + " failed!\n" << _logs << endl;
	}
	return _success;
}

StaticMeshComponent::StaticMeshComponent(Actor* _owner) : Component(_owner)
{
	shaderProgram = 0;
	vertexShaderPath = "VertexShader.vert";
	fragmentShaderPath = "FragmentLightShaderV2.frag";

	lightColor = { 1.0f, 1.0f, 1.0f };
	rainbowColor = false;
	rainbowLight = false;
	useTextures = true;
	verticesCount = 4;
	dimension = 3;

	vertexDataSize = 0;
	vertices = vector<Vertex>();
	indices = vector<GLuint>();

	VBO = 0;
	VAO = 0;
	EBO = 0;

	material = new Material("VertexShader.vert", "FragmentLightShaderV2.frag");

	allTextures =
	{
		/*{ "diffuse.jpg", 0 },
		{ "diffuse.jpg", 0 },
		{ "normal.png", 0 },
		{ "roughness.jpg", 0 },
		{ "specular.jpg", 0 },*/
	};
}
StaticMeshComponent::StaticMeshComponent(Actor* _owner, const StaticMeshComponent& _other) : Component(_owner)
{
	shaderProgram = _other.shaderProgram;
	vertexShaderPath = _other.vertexShaderPath;
	fragmentShaderPath = _other.fragmentShaderPath;

	lightColor = _other.lightColor;
	rainbowColor = _other.rainbowColor;
	rainbowLight = _other.rainbowLight;
	useTextures = _other.useTextures;
	verticesCount = _other.verticesCount;
	dimension = _other.dimension;

	vertexDataSize = _other.vertexDataSize;
	vertices = _other.vertices;
	indices = _other.indices;

	VBO = _other.VBO;
	VAO = _other.VAO;
	EBO = _other.EBO;

	allTextures = _other.allTextures;
}

void StaticMeshComponent::BeginPlay()
{
	SUPER::BeginPlay();
	Init();
	//Init(); TODO see if keep the one in construct or this one
}

void StaticMeshComponent::Construct()
{
	SUPER::Construct();
	
}

void StaticMeshComponent::Deconstruct()
{
	SUPER::Deconstruct();

}

void StaticMeshComponent::Tick(const float _deltaTime)
{
	SUPER::Tick(_deltaTime);
	Update();
}

void StaticMeshComponent::BeginDestroy()
{
	SUPER::BeginDestroy();
	Clear();
}

void StaticMeshComponent::Init()
{
	//vertexDataSize = dimension + 3 + 3 + (useTextures ? 2 : 0);
	vertexDataSize = dimension + 3 + 3 + (useTextures ? 2 : 0);
	//InitShaders();
	
	//material->InitAlbedo(Vector4f(1.0f,1.0f,1.0f,1.0f));
	material->InitAlbedo("/backpack/diffuse.jpg");

	InitBuffers();
	InitTextures();
}

void StaticMeshComponent::GenerateShapeFromModel(aiMesh* _mesh, const aiScene* _scene)
{
	const unsigned int& _verticesAmount = _mesh->mNumVertices;
	for (GLuint _index = 0; _index < _verticesAmount; _index++)
	{

		Vector3f _position = _mesh->mVertices[_index];

		Vector3f _normal;
		if (_mesh->HasNormals())
			_normal = _mesh->mNormals[_index];

		const bool _hasTextures = _mesh->mTextureCoords[0];
		const Vector2f& _textureCoords = _hasTextures ? _mesh->mTextureCoords[0][_index] : Vector2f(0.0f);;

		Vector3f _tangent;
		Vector3f _bitangent;
		if (_mesh->HasTangentsAndBitangents())
		{
			_tangent = _mesh->mTangents[_index];
			_bitangent = _mesh->mBitangents[_index];
		}

		const Vertex& _vertex = Vertex(_position, _normal, _textureCoords, _tangent, _bitangent);
		vertices.push_back(_vertex);
	}

	const unsigned int& _facesAmount = _mesh->mNumFaces;
	for (GLuint _faceIndex = 0; _faceIndex < _facesAmount; _faceIndex++)
	{
		aiFace _face = _mesh->mFaces[_faceIndex];

		const int& _edgesAmount = _face.mNumIndices;
		for (GLuint _edgeIndex = 0; _edgeIndex < _edgesAmount; _edgeIndex++)
			indices.push_back(_face.mIndices[_edgeIndex]);
	}

	if (_scene->HasMaterials())
	{
		aiMaterial* _material = _scene->mMaterials[_mesh->mMaterialIndex];

		/*vector<Texture> _ambientTextures = LoadTextures(_material, aiTextureType_AMBIENT);
		textures.insert(textures.begin(), _ambientTextures.begin(), _ambientTextures.end());

		vector<Texture> _diffuseTextures = LoadTextures(_material, aiTextureType_DIFFUSE);
		textures.insert(textures.begin(), _diffuseTextures.begin(), _diffuseTextures.end());

		vector<Texture> _specularTextures = LoadTextures(_material, aiTextureType_SPECULAR);
		textures.insert(textures.begin(), _specularTextures.begin(), _specularTextures.end());

		vector<Texture> _heightTextures = LoadTextures(_material, aiTextureType_HEIGHT);
		textures.insert(textures.begin(), _heightTextures.begin(), _heightTextures.end());*/

		/*const aiTextureType _textureTypes[] =
		{
			aiTextureType_AMBIENT,
			aiTextureType_DIFFUSE,
			aiTextureType_SPECULAR,
			aiTextureType_HEIGHT,
		};

		vector<Texture> _loadedTextures;
		for (unsigned int i = 0; i < 4; i++)
		{
			_loadedTextures = LoadTextures(_material, _textureTypes[i]);

			if (!_loadedTextures.empty())
			{
				textures.insert(textures.begin(), _loadedTextures.begin(), _loadedTextures.end());
			}
		}*/
	}
}

vector<Texture> StaticMeshComponent::LoadTextures(aiMaterial* _material, const aiTextureType& _type)
{
	vector<Texture> _textures;

	const  GLuint& _amount = _material->GetTextureCount(_type);

	for (GLuint _textureIndex = 0; _textureIndex < _amount; _textureIndex++)
	{
		aiString _path;
		_material->GetTexture(_type, _textureIndex, &_path);
		bool skip = false;
		for (unsigned int j = 0; j < textures.size(); j++)
		{
			if (std::strcmp(textures[j].GetStringKey().data(), _path.C_Str()) == 0)
			{
				textures.push_back(textures[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{
			const GLuint& _id = LoadTexture(_path.C_Str());
			//const Texture& _texture = Texture(_id, _path.C_Str(), _type);
			Texture* _texture = TextureManager::GetInstance().CreateTexture(_path.C_Str(), _type);
 			_textures.push_back(*_texture);

		}
	}
	return _textures;
}

float StaticMeshComponent::RoundFloat(const float& _value)
{
	return IsNearlyEqual(_value, 0.0f) ? 0.0f : _value;
}

bool StaticMeshComponent::IsNearlyEqual(const float& _a, const float& _b, const float& _tolerance)
{
	const float& _diff = abs(_a - _b);
	const float& _maxAB = std::max(abs(_a), abs(_b));

	return _diff <= _tolerance || _diff <= _maxAB * _tolerance;
}

void StaticMeshComponent::InitBuffers()
{
	// Inits
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bindings
	glBindVertexArray(VAO);

	// Setup vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, SizeOf<GLsizei, Vertex>(vertices.size()), vertices.data(), GL_STATIC_DRAW);

	// Setup edges
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeOf<GLsizei, GLuint>(indices.size()), indices.data(), GL_STATIC_DRAW);

	const GLsizei& _vertexSize = SizeOf<GLsizei, Vertex>();

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(0));
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(3));
	glEnableVertexAttribArray(1);

	// Textures
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(6));
	glEnableVertexAttribArray(2);

	// Tangents
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(8));
	glEnableVertexAttribArray(3);

	// Bitangents
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(11));
	glEnableVertexAttribArray(4);

	// IDs
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(14));
	glEnableVertexAttribArray(5);

	// Weights
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(18));
	glEnableVertexAttribArray(6);

	// Applying VBO and VAO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

}

GLuint StaticMeshComponent::LoadTexture(const string& _textureName)
{
	GLuint _texture;
	glGenTextures(1, &_texture);

	// Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int _textureWidth;
	int _textureHeight;
	int _channelsCount;
	const string& _texturePath = GetPath(CONTENT);
	string _filePath = _texturePath + "backpack/Textures/" + _textureName;

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
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _textureWidth, _textureHeight, 0, _format, GL_UNSIGNED_BYTE, _data);

	// Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(_data);
	return _texture;
}

void StaticMeshComponent::InitTextures()
{
	if (useTextures)
	{
		try
		{
			glUseProgram(material->GetShader()->GetShaderProgram());
			for (const pair<string, GLuint>& _pair : allTextures)
				allTextures[_pair.first] = LoadTexture(_pair.first);

			LightManager::GetInstance().ApplyLighting(material->GetShader()->GetShaderProgram());

			//Manager donne un vector
			//Static Mesh Set le frag
			//glUniform1f(_uniformMaterialShininess, 64.0f);
		
		}
		catch (const exception& _error)
		{
			cerr << _error.what() << endl;
		}
	}
}

void StaticMeshComponent::Update()
{
	material->Update();
	Draw();
}

void StaticMeshComponent::Draw()
{
	// === Drawing shapes as Elements ===
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

	// === Drawing shapes as Vertices ===
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void StaticMeshComponent::Clear()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
}