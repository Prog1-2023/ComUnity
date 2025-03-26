#include "StaticMeshComponent.h"
#include "../Actors/Actor.h"

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
	fragmentShaderPath = "FragmentShader.frag";

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

	allTextures =
	{
		{ "Container.png", 0 },
		{ "ContainerSpecular.png", 0 },
		//{ "Cthulhu.png", 0 },
		//{ "Face.png", 0 },
	};
}

void StaticMeshComponent::BeginPlay()
{
	SUPER::BeginPlay();
	Init();
}

void StaticMeshComponent::Tick(const float& _deltaTime)
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
	InitShaders();

	InitShape();
	InitBuffers();

	InitTextures();
}

void StaticMeshComponent::InitShaders()
{
	glEnable(GL_DEPTH_TEST);

	// VertexShader
	unsigned int _vertexShader = CreateShader(vertexShaderPath, true);
	Assert(CheckShaderForErrors(_vertexShader, "VertexShader"), "Init of VertexShader failed!");

	// FragmentShader
	unsigned int _fragmentShader = CreateShader(fragmentShaderPath, false);
	Assert(CheckShaderForErrors(_fragmentShader, "FragmentShader"), "Init of FragmentShader failed!");

	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, _vertexShader);
	glAttachShader(shaderProgram, _fragmentShader);
	glLinkProgram(shaderProgram);
	Assert(CheckShaderForErrors(shaderProgram, "ShaderProgram"), "Init of ShaderProgram failed!");

	modelID = glGetUniformLocation(shaderProgram, "uniformModel");
	viewID = glGetUniformLocation(shaderProgram, "uniformView");
	projectionID = glGetUniformLocation(shaderProgram, "uniformProjection");

	// Clear shaders
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

void StaticMeshComponent::InitShape()
{
	if (dimension == 2) Generate2DShape({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }); // ===== DOESN'T WORK ANYMORE
	else Generate3DShape({ 1.0f, 1.0f, 1.0f });
}

bool StaticMeshComponent::Generate2DShape(const vector<float> _outerColor, const vector<float> _innerColor)
{
	//if (verticesCount <= 0)
	//	return false;

	//const int& _coordsByVertex = 5 + (useTextures ? 2 : 0);
	//const int& _allVerticesCount = verticesCount + 2;
	//const int& _coordsCount = _allVerticesCount * _coordsByVertex;
	//const float& _angleStep = 2.0f * M_PI / verticesCount;
	//vertices = vector<GLfloat>(_coordsCount);

	//for (unsigned int _coordIndex = 0; _coordIndex < 2; _coordIndex++)
	//{
	//	vertices[_coordIndex] = 0.0f;
	//}

	//vertices[2] = _innerColor[0];
	//vertices[3] = _innerColor[1];
	//vertices[4] = _innerColor[2];

	//for (unsigned int _index = 1; _index < _allVerticesCount; _index++)
	//{
	//	const float& _angle = _angleStep * _index;

	//	// Position
	//	vertices[_index * _coordsByVertex] = cos(_angle);
	//	vertices[_index * _coordsByVertex + 1] = sin(_angle);

	//	// Colors
	//	vertices[_index * _coordsByVertex + 2] = _outerColor[0];
	//	vertices[_index * _coordsByVertex + 3] = _outerColor[1];
	//	vertices[_index * _coordsByVertex + 4] = _outerColor[2];

	//	// Textures
	//	if (useTextures)
	//	{
	//		vertices[_index * _coordsByVertex + 2 + 3] = cos(_angle);
	//		vertices[_index * _coordsByVertex + 2 + 3 + 1] = sin(_angle);
	//	}
	//}

	//for (unsigned int _index = 0; _index < _allVerticesCount - 2; _index++)
	//{
	//	edges.push_back(0);
	//	edges.push_back(_index + 1);
	//	edges.push_back(_index + 2);
	//}

	return true;
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
		const Vector2f& _textureCoords = _hasTextures ? _mesh->mTextureCoords[0][_index] : Vector2f(0.0f);
		if (!_hasTextures)continue; //TODO remove maybe

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

		vector<DeprTexture> _ambientTextures = LoadTextures(_material, aiTextureType_AMBIENT);
		textures.insert(textures.begin(), _ambientTextures.begin(), _ambientTextures.end());
		
		vector<DeprTexture> _diffuseTextures = LoadTextures(_material, aiTextureType_DIFFUSE);
		textures.insert(textures.begin(), _diffuseTextures.begin(), _diffuseTextures.end());

		vector<DeprTexture> _specularTextures = LoadTextures(_material, aiTextureType_SPECULAR);
		textures.insert(textures.begin(), _specularTextures.begin(), _specularTextures.end());

		vector<DeprTexture> _heightTextures = LoadTextures(_material, aiTextureType_HEIGHT);
		textures.insert(textures.begin(), _heightTextures.begin(), _heightTextures.end());
	}
}

vector<DeprTexture> StaticMeshComponent::LoadTextures(aiMaterial* _material, const aiTextureType& _type) //Create A Static util method
{
	vector<DeprTexture> _textures;
	std::vector<DeprTexture>& _texturesAlreadyLoaded = owner->GetTextureAlreadyLoadedRef();

	const unsigned int _amount = _material->GetTextureCount(_type);
	for (GLuint _textureIndex = 0; _textureIndex < _amount; _textureIndex++)
	{
		aiString _path;
		_material->GetTexture(_type, _textureIndex, &_path);

		bool _skip = false;
		for (unsigned int j = 0; j < _texturesAlreadyLoaded.size(); j++)
		{
			if (std::strcmp(_texturesAlreadyLoaded[j].path.data(), _path.C_Str()) == 0)
			{
				_textures.push_back(_texturesAlreadyLoaded[j]);
				_skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!_skip)
		{   // if texture hasn't been loaded already, load it
			const GLuint& _id = LoadTexture(_path.C_Str());
			const DeprTexture& _texture = DeprTexture(_id, _path.C_Str(), _type);
			_texturesAlreadyLoaded.push_back(_texture);
			textures.push_back(_texture);
			// store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
		}
	}
	 return _textures;
}

bool StaticMeshComponent::Generate3DShape(const vector<float> _color)
{
	/*// Position + Color + Normal + Texture
	vertices = {
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	};*/

	/*if (verticesCount <= 0)
		return false;*/

	//const vector<vec3>& _offsets = {
	//	{ 0.0f, 0.0f, 0.75f },
	//	{ 0.0f, 0.0f, -0.75f },
	//};
	//const unsigned int _offsetCount = static_cast<const unsigned int>(_offsets.size());
	//const float _angleStep = 2.0f * M_PI / verticesCount;
	//unsigned int _vertexOffset = 0;  // Décomptage du décalage pour les indices de sommets
	//for (unsigned int _offsetIndex = 1; _offsetIndex <= _offsetCount; _offsetIndex++)
	//{
	//	const vec3& _offset = _offsets[_offsetIndex - 1];
	//	for (unsigned int _index = 1; _index <= verticesCount; _index++)
	//	{
	//		const float _angle = _angleStep * _index;
	//		// Position
	//		vertices.push_back(RoundFloat(cosf(_angle) + _offset.x));
	//		vertices.push_back(RoundFloat(sinf(_angle) + _offset.y));
	//		vertices.push_back(_offset.z);
	//		// Colors
	//		if (useColor)
	//		{
	//			vertices.push_back(_color[0]);
	//			vertices.push_back(_color[1]);
	//			vertices.push_back(_color[2]);
	//		}
	//		// Textures
	//		if (useTextures)
	//		{
	//			vertices.push_back(RoundFloat(cosf(_angle) + _offset.x));
	//			vertices.push_back(RoundFloat(sinf(_angle) + _offset.y));
	//		}
	//		vertices.push_back(0);  vertices.push_back(0);  vertices.push_back(0);
	//	}
	//	if (_offsetIndex == 1) // Z = -0.5f
	//	{
	//		// Face inférieure (2 triangles)
	//		edges.push_back(0);  edges.push_back(1);  edges.push_back(2);
	//		edges.push_back(0);  edges.push_back(2);  edges.push_back(3);
	//	}
	//	else if (_offsetIndex == 2) // Z = +0.5f
	//	{
	//		// Face supérieure (2 triangles)
	//		edges.push_back(4);  edges.push_back(5);  edges.push_back(6);
	//		edges.push_back(4);  edges.push_back(6);  edges.push_back(7);
	//	}
	//	// Faces latérales
	//	if (_offsetIndex == 1)
	//	{
	//		// Face avant
	//		edges.push_back(0);  edges.push_back(1);  edges.push_back(5);
	//		edges.push_back(0);  edges.push_back(5);  edges.push_back(4);
	//	}
	//	else if (_offsetIndex == 2)
	//	{
	//		// Face arrière
	//		edges.push_back(2);  edges.push_back(3);  edges.push_back(7);
	//		edges.push_back(2);  edges.push_back(7);  edges.push_back(6);
	//	}
	//	// Faces latérales restantes
	//	if (_offsetIndex == 1)
	//	{
	//		// Face gauche
	//		edges.push_back(0);  edges.push_back(4);  edges.push_back(7);
	//		edges.push_back(0);  edges.push_back(7);  edges.push_back(3);
	//	}
	//	else if (_offsetIndex == 2)
	//	{
	//		// Face droite
	//		edges.push_back(1);  edges.push_back(2);  edges.push_back(6);
	//		edges.push_back(1);  edges.push_back(6);  edges.push_back(5);
	//	}
	//}

	//const int& _latitudeSteps = verticesCount / 2;
	//const int& _longitudeSteps = verticesCount;
	//const float& _radius = 10.0f;
	//const int& _dataSize = ((_latitudeSteps + 1) * _longitudeSteps) * vertexDataSize;
	//verticesData.resize(_dataSize);
	//for (unsigned int _firstIndex = 0; _firstIndex < _latitudeSteps + 1; _firstIndex++)
	//{
	//	const float& _sphereTheta = M_PI * (float(_firstIndex) / _latitudeSteps);
	//	for (unsigned int _secondIndex = 0; _secondIndex < _longitudeSteps; _secondIndex++)
	//	{
	//		const float& _spherePhi = 2.0f * M_PI * (float(_secondIndex) / _longitudeSteps);
	//		const float& _x = _radius * sin(_sphereTheta) * cos(_spherePhi);
	//		const float& _y = _radius * sin(_sphereTheta) * sin(_spherePhi);
	//		const float& _z = _radius * cos(_sphereTheta);
	//		// Position
	//		const int& _vertexIndex = _firstIndex * _longitudeSteps + _secondIndex;
	//		verticesData[_vertexIndex * vertexDataSize + 0] = _x;
	//		verticesData[_vertexIndex * vertexDataSize + 1] = _y;
	//		verticesData[_vertexIndex * vertexDataSize + 2] = _z;
	//		// Colors
	//		verticesData[_vertexIndex * vertexDataSize + 3] = _color[0];
	//		verticesData[_vertexIndex * vertexDataSize + 4] = _color[1];
	//		verticesData[_vertexIndex * vertexDataSize + 5] = _color[2];
	//		// Textures
	//		if (useTextures)
	//		{
	//			verticesData[_vertexIndex * vertexDataSize + 6] = 0.0f;
	//			verticesData[_vertexIndex * vertexDataSize + 7] = 0.0f;
	//		}
	//	}
	//}
	//for (unsigned int _firstIndex = 0; _firstIndex < _latitudeSteps + 1; _firstIndex++)
	//{
	//	for (unsigned int _secondIndex = 0; _secondIndex < _longitudeSteps; _secondIndex++)
	//	{
	//		// Points
	//		// Points
	//		const unsigned int& _pointA = _firstIndex * _longitudeSteps + _secondIndex;
	//		const unsigned int& _pointB = (_firstIndex + 1) * _longitudeSteps + _secondIndex;
	//		const unsigned int& _pointC = (_firstIndex + 1) * _longitudeSteps + (_secondIndex + 1) % _longitudeSteps;
	//		const unsigned int& _pointD = _firstIndex * _longitudeSteps + (_secondIndex + 1) % _longitudeSteps;
	//		// First triangle in rectangle
	//		edges.push_back(_pointA);
	//		edges.push_back(_pointB);
	//		edges.push_back(_pointC);
	//		// Second triangle in rectangle
	//		edges.push_back(_pointA);
	//		edges.push_back(_pointC);
	//		edges.push_back(_pointD);
	//	}
	//}
	//
	return true;
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeOf<GLsizei>(indices.size()), indices.data(), GL_STATIC_DRAW);

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

	/*
	//// Inits
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	//// Bindings
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//// Setup vertices
	//glBufferData(GL_ARRAY_BUFFER, SizeOf<GLsizei>(vertices.size()), vertices.data(), GL_STATIC_DRAW);

	//// Setup edges
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeOf<GLsizei>(edges.size()), edges.data(), GL_STATIC_DRAW);

	//// Position attributes
	//const GLsizei& _sizeAttrib0 = SizeOf<GLsizei>(vertexDataSize);
	//glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, _sizeAttrib0, SizeOf(0));
	//glEnableVertexAttribArray(0);

	//// Color attributes
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _sizeAttrib0, SizeOf(dimension));
	//glEnableVertexAttribArray(1);

	//// Normal attributes
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, _sizeAttrib0, SizeOf(dimension + 3));
	//glEnableVertexAttribArray(3);

	//// Texture attributes
	//if (useTextures)
	//{
	//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _sizeAttrib0, SizeOf(dimension + 3 + 3));
	//	glEnableVertexAttribArray(2);
	//}

	//// Applying VBO and VAO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindVertexArray(VAO);
	*/
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
	const string& _texturePath = GetPath(TEXTURES) + "Survival_BackPack/";
	string _filePath = _texturePath + _textureName;

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
	glTexImage2D(GL_TEXTURE_2D, 0, _format, _textureWidth, _textureHeight, 0, _format, GL_UNSIGNED_BYTE, _data);

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
			glUseProgram(shaderProgram);
			//for (const pair<string, GLuint>& _pair : allTextures)
			//	allTextures[_pair.first] = LoadTexture(_pair.first);

	/*		const GLuint& _uniformMaterialDiffuse = glGetUniformLocation(shaderProgram, "uniformMaterial.diffuse");
			glUniform1i(_uniformMaterialDiffuse, 0);
			const GLuint& _uniformMaterialSpecular = glGetUniformLocation(shaderProgram, "uniformMaterial.specular");
			glUniform1i(_uniformMaterialSpecular, 1);
			const GLuint& _uniformMaterialShininess = glGetUniformLocation(shaderProgram, "uniformMaterial.shininess");
			glUniform1f(_uniformMaterialShininess, 64.0f);*/
		}
		catch (const exception& _error)
		{
			cerr << _error.what() << endl;
		}
	}
}

void StaticMeshComponent::Update()
{
	//UpdateColors();
	//UpdateTextures(); // TODO update
	Draw();
	UpdateTextures();
	UpdateColors();
	
	//glActiveTexture(GL_TEXTURE0);
}

void StaticMeshComponent::UpdateColors()
{
	if (vertices.size() == 0)
		return;
	const double _elapsedTime = glfwGetTime();
	if (rainbowColor)
	{
		const unsigned int& _amount = vertices.size() / vertexDataSize;
		for (unsigned int _index = 0; _index < _amount; _index++)
		{
			/*vertices[_index * vertexDataSize + dimension] = (sin(_elapsedTime + _index) + 1.0f) / 2.0f;
			vertices[_index * vertexDataSize + dimension + 1] = (cos(_elapsedTime + _index * 0.5f) + 1.0f) / 2.0f;
			vertices[_index * vertexDataSize + dimension + 2] = (sin(_elapsedTime * 0.5f + _index) + 1.0f) / 2.0f;*/
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, SizeOf<GLsizei>(vertices.size()), vertices.data(), GL_STATIC_DRAW);
	}

	const GLuint& _viewPositionLocation = glGetUniformLocation(shaderProgram, "uniformViewPosition");
	glUniform3f(_viewPositionLocation, cameraLocation.x, cameraLocation.y, cameraLocation.z);

	const GLuint& _lightPositionLocation = glGetUniformLocation(shaderProgram, "uniformLight.position");
	glUniform3f(_lightPositionLocation, sinf(_elapsedTime), 0.0f, cosf(_elapsedTime));
	//glUniform3f(_lightPositionLocation, 0.0f, 0.0f, 1.0f);

	const GLuint& _lightColorLocation = glGetUniformLocation(shaderProgram, "uniformLight.ambient");
	if (rainbowLight)
	{
		lightColor[0] = (sin(_elapsedTime) + 1.0f) / 2.0f;
		lightColor[1] = (cos(_elapsedTime * 0.5f) + 1.0f) / 2.0f;
		lightColor[2] = (sin(_elapsedTime * 1.5f) + 1.0f) / 2.0f;
	}
	glUniform3f(_lightColorLocation, 1, 1, 1);

	const GLuint& _lightDiffuseLocation = glGetUniformLocation(shaderProgram, "uniformLight.diffuse");
	glUniform3f(_lightDiffuseLocation, 0.5f, 0.5f, 0.5f);

	const GLuint& _lightSpecularLocation = glGetUniformLocation(shaderProgram, "uniformLight.specular");
	glUniform3f(_lightSpecularLocation, 1.0f, 1.0f, 1.0f);
}

void StaticMeshComponent::UpdateTextures()
{
	/*if (useTextures)
	{
		int _textureIndex = 0;
		for (const pair<string, GLuint>& _pair : allTextures)
		{
			glActiveTexture(GL_TEXTURE0 + _textureIndex);
			glBindTexture(GL_TEXTURE_2D, _pair.second);
			_textureIndex++;
		}
	}*/

	GLuint _diffuseNr = 1;
	GLuint _specularNr = 1;
	GLuint _normalNr = 1;
	GLuint _heightNr = 1;

	const unsigned int& _texturesAmount = static_cast<const unsigned int>(textures.size());
	for (GLuint _index = 0; _index < _texturesAmount; _index++)
	{
		glActiveTexture(GL_TEXTURE0 + _index);

		string _numberText;
		aiTextureType _type = textures[_index].type;
		
		if (_type == aiTextureType_AMBIENT)
		{
			_numberText = to_string(_normalNr++);
		}
		else if (_type == aiTextureType_DIFFUSE)
		{
			_numberText = to_string(_diffuseNr++);
		}
		else if (_type == aiTextureType_SPECULAR)
		{
			_numberText = to_string(_specularNr++);
		}
		else if (_type == aiTextureType_HEIGHT)
		{
			_numberText = to_string(_heightNr++);
		}

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

		const GLuint& _uniformTextureID = glGetUniformLocation(shaderProgram, (_textureName + _numberText).c_str());
		glUniform1i(_uniformTextureID, _index);
		glBindTexture(GL_TEXTURE_2D, textures[_index].id);
	}
}

void StaticMeshComponent::Draw()
{
	// === Drawing shapes as Elements ===
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	//glBindVertexArray(0);

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