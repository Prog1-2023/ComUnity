#include "StaticMeshComponent.h"

string GetShaderPath()
{
	const path& _currentPath = current_path();
	const path& _shaderPath = _currentPath.parent_path() / "Source/Shaders/";
	return _shaderPath.string();
}

StaticMeshComponent::StaticMeshComponent(Actor* _owner) : Component(_owner)
{
	// Shader
	shaderProgram = 0;
	vertexShaderPath = "VertexShader.vert";
	fragmentShaderPath = "FragmentShader.frag";

	// Shape
	useColor = false;
	verticesCount = 4;
	dimension = 3;
	//vertices = vector<Vertex>();
	indices = vector<GLuint>();
	textures = vector<Texture>();
	coordsCount = 0;

	// Buffers
	VBO = 0;
	VAO = 0;
	EBO = 0;

	// Textures
	allTextures =
	{
		{ "container.png", 0 },
		{ "container_specular.png", 0 }
		//{ "Chad_Squid_Face.jpg", 0 },
		//{ "Patrick_Texture.jpg", 0 },
	};

	//move plus tard
	elapsedTime = 0.0f;
}

StaticMeshComponent::~StaticMeshComponent()
{

}

void StaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void StaticMeshComponent::Tick(const float _deltatime)
{
	Super::Tick(_deltatime);

	//UpdateColors();
	UpdateTextures(); //TODO update
	Draw();

	//glActiveTexture(GL_TEXTURE0);
}

void StaticMeshComponent::BeginDestroy()
{
	Super::BeginDestroy();
	Clear();
}

void StaticMeshComponent::Init()
{
	InitShaders();
	InitShape();
	InitBuffers();
	InitTextures();
	InitLighting();
}

void StaticMeshComponent::InitShaders()
{
	glEnable(GL_DEPTH_TEST);
	const string& _shaderPath = GetShaderPath();

	// VertexShader
	unsigned int _vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const string& _vertexShaderCode = TShader::ReadShader(_shaderPath + vertexShaderPath);
	const char* _vertexShaderData = _vertexShaderCode.c_str();
	glShaderSource(_vertexShader, 1, &_vertexShaderData, NULL);
	glCompileShader(_vertexShader);
	Assert(CheckShaderForErrors(_vertexShader, "VertexShader"), "Init of Vertexshader failed !");

	// FragmentShader
	unsigned int _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const string& _fragmentShaderCode = TShader::ReadShader(_shaderPath + fragmentShaderPath);
	const char* _fragmentShaderData = _fragmentShaderCode.c_str();
	glShaderSource(_fragmentShader, 1, &_fragmentShaderData, NULL);
	glCompileShader(_fragmentShader);
	Assert(CheckShaderForErrors(_fragmentShader, "FragmentShader"), "Init of FragmentShader failed !");

	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, _vertexShader);
	glAttachShader(shaderProgram, _fragmentShader);
	glLinkProgram(shaderProgram);
	Assert(CheckShaderForErrors(shaderProgram, "ShaderProgram"), "Init of ShaderProgram failed !");

	modelID = glGetUniformLocation(shaderProgram, "uniformModel");
	viewID = glGetUniformLocation(shaderProgram, "uniformView");
	projectionID = glGetUniformLocation(shaderProgram, "uniformProjection");

	// Clear shaders
	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

bool StaticMeshComponent::CheckShaderForErrors(const GLuint& _shader, const string& _shaderName)
{
	int _success;
	char _logs[512];

	glGetShaderiv(_shader, GL_COMPILE_STATUS, &_success);

	if (!_success)
	{
		glGetShaderInfoLog(_shader, 512, NULL, _logs);
		cerr << "Error => Init " << _shaderName << " failed !\n" << _logs;
	}

	return _success;
}

void StaticMeshComponent::InitShape()
{
	switch (dimension)
	{
	case 2:
		Generate2DShape();
		break;

	case 3:
		Generate3DShape();
		break;

	default:
		break;
	}
}

bool StaticMeshComponent::IsNearlyEqual(float _a, float _b, float _tolerance)
{
	float _diff = abs(_a - _b);
	float _maxAB = std::max(abs(_a), abs(_b));

	return _diff <= _tolerance || _diff <= _maxAB * _tolerance;
}

float StaticMeshComponent::RoundFloat(const float _value)
{
	return IsNearlyEqual(_value, 0.0f) ? 0.0f : _value;
}

bool StaticMeshComponent::Generate2DShape()
{
	/*if (verticesCount <= 0) return false;

	const int _coordsByVertex = 2 + (useColor ? 3 : 0) + 2;
	const int _allVerticesCount = verticesCount + 2;
	const int _coordsCount = _allVerticesCount * _coordsByVertex;
	const float _angleStep = 2.0f * M_PI / verticesCount;
	vertices = vector<GLfloat>(_coordsCount);

	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

	if (useColor)
	{
		// Colors
		vertices[2] = 1.0f;
		vertices[2 + 1] = 0.0f;
		vertices[2 + 2] = 0.5f;
	}

	// Textures
	vertices[2 + (useColor ? 3 : 0)] = 0.5f;
	vertices[2 + (useColor ? 3 : 0) + 1] = 0.5f;

	for (unsigned int _index = 1; _index < _allVerticesCount; _index++)
	{
		const float _angle = _angleStep * _index;

		// Position
		vertices[_index * _coordsByVertex] = cosf(_angle);
		vertices[_index * _coordsByVertex + 1] = sinf(_angle);

		// Colors
		if (useColor)
		{
			vertices[_index * _coordsByVertex + 2] = 1.0f;
			vertices[_index * _coordsByVertex + 2 + 1] = 0.0f;
			vertices[_index * _coordsByVertex + 2 + 2] = 0.0f;
		}

		// Textures
		vertices[_index * _coordsByVertex + 2 + (useColor ? 3 : 0)] = cosf(_angle);
		vertices[_index * _coordsByVertex + 2 + (useColor ? 3 : 0) + 1] = sinf(_angle);
	}

	for (unsigned int _index = 0; _index < _allVerticesCount - 2; _index++)
	{
		edges.push_back(0);
		edges.push_back(_index + 1);
		edges.push_back(_index + 2);
	}*/

	return true;
}

void StaticMeshComponent::AddEdge(std::set<std::pair<GLuint, GLuint>>& indices, GLuint vertex1, GLuint vertex2)
{
	// Tri des indices pour éviter (0,1) et (1,0) comme doublons
	if (vertex1 > vertex2) std::swap(vertex1, vertex2);

	// Ajouter l'arête triée dans le set
	indices.insert({ vertex1, vertex2 });
}

bool StaticMeshComponent::Generate3DShape()
{

	//TODO move into Actor Class
	//Importer _importer = Importer();
	//const string& _path = "";
	//const aiScene* _scene = _importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	//const string& _errorString = string("Error => ") + string(_importer.GetErrorString());
	//Assert(_scene && _scene->mRootNode && (_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE), _errorString.c_str());
	//const string& _directory = _path.substr(0, _path.find_last_of('/'));


	//vector<Mesh> _meshes;
	//aiNode* _node = _scene->mRootNode;
	//GLuint _size = _node->mNumMeshes;
	//for (GLuint _i = 0; _i < _size; _i++)
	//{
	//	aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[_i]];
	//	_meshes.push_back(_mesh);
	//}

	/*if (verticesCount <= 0) return false;

	const vector<vec3>& _offsets = {
		{ 0.0f, 0.0f, 0.75f },
		{ 0.0f, 0.0f, -0.75f },
	};
	const unsigned int _offsetCount = static_cast<const unsigned int>(_offsets.size());
	const float _angleStep = 2.0f * M_PI / verticesCount;
	unsigned int _vertexOffset = 0;  // Décomptage du décalage pour les indices de sommets

	for (unsigned int _offsetIndex = 1; _offsetIndex <= _offsetCount; _offsetIndex++)
	{
		const vec3& _offset = _offsets[_offsetIndex - 1];

		for (unsigned int _index = 1; _index <= verticesCount; _index++)
		{
			const float _angle = _angleStep * _index + radians(45.0f);

			// Position
			vertices.push_back(RoundFloat(cosf(_angle) + _offset.x));
			vertices.push_back(RoundFloat(sinf(_angle) + _offset.y));
			vertices.push_back(_offset.z);

			// Colors
			if (useColor)
			{
				vertices.push_back(1.0f);
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);
			}

			// Textures
			vertices.push_back(RoundFloat(cosf(_angle) + _offset.x));
			vertices.push_back(RoundFloat(sinf(_angle) + _offset.y));
		}

		if (_offsetIndex == 1) // Z = -0.5f
		{
			// Face inférieure (2 triangles)
			edges.push_back(0);  edges.push_back(1);  edges.push_back(2);
			edges.push_back(0);  edges.push_back(2);  edges.push_back(3);
		}
		else if (_offsetIndex == 2) // Z = +0.5f
		{
			// Face supérieure (2 triangles)
			edges.push_back(4);  edges.push_back(5);  edges.push_back(6);
			edges.push_back(4);  edges.push_back(6);  edges.push_back(7);
		}

		// Faces latérales
		if (_offsetIndex == 1)
		{
			// Face avant
			edges.push_back(0);  edges.push_back(1);  edges.push_back(5);
			edges.push_back(0);  edges.push_back(5);  edges.push_back(4);
		}
		else if (_offsetIndex == 2)
		{
			// Face arrière
			edges.push_back(2);  edges.push_back(3);  edges.push_back(7);
			edges.push_back(2);  edges.push_back(7);  edges.push_back(6);
		}

		// Faces latérales restantes
		if (_offsetIndex == 1)
		{
			// Face gauche
			edges.push_back(0);  edges.push_back(4);  edges.push_back(7);
			edges.push_back(0);  edges.push_back(7);  edges.push_back(3);
		}
		else if (_offsetIndex == 2)
		{
			// Face droite
			edges.push_back(1);  edges.push_back(2);  edges.push_back(6);
			edges.push_back(1);  edges.push_back(6);  edges.push_back(5);
		}
	}*/


	vertices = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	return true;
}

void StaticMeshComponent::GenerateShapeFromModel(aiMesh* _mesh, const aiScene* _scene)
{
	// Vertices
	//const GLuint& _verticesSize = _mesh->mNumVertices;
	//for (GLuint _i = 0; _i < _verticesSize; _i++)
	//{
	//	const Vector3f& _position = _mesh->mVertices[_i];

	//	Vector3f _normal;
	//	if (_mesh->HasNormals())
	//	{
	//		_normal = _mesh->mNormals[_i];
	//	}

	//	const bool _hasTexture = _mesh->mTextureCoords[0];
	//	const Vector2f& _textureCoords = _hasTexture ? _mesh->mTextureCoords[0][_i] : Vector2f(0.0f);

	//	Vector3f _tangents, _biTangents;
	//	if (_mesh->HasTangentsAndBitangents())
	//	{
	//		_tangents = _mesh->mTangents[_i];
	//		_biTangents = _mesh->mBitangents[_i];
	//	}

	//	// Construct and add a new vertex
	//	const Vertex& _vertex = Vertex(_position, _normal, _textureCoords, _tangents, _biTangents);
	//	vertices.push_back(_vertex);
	//}

	//// Edges
	//const GLuint& _facesSize = _mesh->mNumFaces;
	//for (GLuint _facesIndex = 0; _facesIndex < _facesSize; _facesIndex++)
	//{
	//	const aiFace& _face = _mesh->mFaces[_facesIndex];

	//	const GLuint& _indesSize = _face.mNumIndices;
	//	for (GLuint _edgesIndex = 0; _edgesIndex < _indesSize; _edgesIndex++)
	//	{
	//		indices.push_back(_face.mIndices[_edgesIndex]);
	//	}
	//}

	//// Textures
	//if (_scene->HasMaterials())
	//{
	//	aiMaterial* _material = _scene->mMaterials[_mesh->mMaterialIndex];

	//	vector<Texture> _ambiantTextures = LoadTextures(_material, aiTextureType_AMBIENT);
	//	textures.insert(textures.begin(), _ambiantTextures.begin(), _ambiantTextures.end());

	//	vector<Texture> _diffuseTextures = LoadTextures(_material, aiTextureType_DIFFUSE);
	//	textures.insert(textures.begin(), _diffuseTextures.begin(), _diffuseTextures.end());

	//	vector<Texture> _specularTextures = LoadTextures(_material, aiTextureType_SPECULAR);
	//	textures.insert(textures.begin(), _specularTextures.begin(), _specularTextures.end());

	//	vector<Texture> _heightTextures = LoadTextures(_material, aiTextureType_HEIGHT);
	//	textures.insert(textures.begin(), _heightTextures.begin(), _heightTextures.end());
	//}

}

vector<Texture> StaticMeshComponent::LoadTextures(aiMaterial* _material, const aiTextureType& _type)
{
	vector<Texture> _textures;

	const GLuint& _textureCount = _material->GetTextureCount(_type);
	for (GLuint _textureIndex = 0; _textureIndex < _textureCount; _textureIndex++)
	{
		aiString _path;
		_material->GetTexture(_type, _textureIndex, &_path);

		const GLuint& _id = LoadTexture(_path.C_Str()); //OhMerde;
		const Texture& _texture = Texture(_id, _path.C_Str(), _type);
		_textures.push_back(_texture);
	}

	return _textures;
}

void StaticMeshComponent::InitBuffers()
{
	glGenVertexArrays(1, &VAO); // Init 1 VAO
	glGenBuffers(1, &VBO); // Init 1 VBO
	glGenBuffers(1, &EBO); // Init 1 EBO

	glBindVertexArray(VAO); // Bind VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // BIND VBO
	glBufferData(GL_ARRAY_BUFFER, SizeOf<GLsizeiptr>(vertices.size()), vertices.data(), GL_STATIC_DRAW); // Setup vertices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // BIND EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeOf<GLsizeiptr>(indices.size()), indices.data(), GL_STATIC_DRAW); // Setup edges


	//const GLsizei& _vertexSize = SizeOf<GLsizei, Vertex>();
	//// Positions
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(0));
	//glEnableVertexAttribArray(0);

	//// Normals
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(3));
	//glEnableVertexAttribArray(1);

	//// Textures
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(6));
	//glEnableVertexAttribArray(2);

	//// Tangents
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(8));
	//glEnableVertexAttribArray(3);

	//// BiTangents
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(11));
	//glEnableVertexAttribArray(4);

	//// IDs
	//glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(14));
	//glEnableVertexAttribArray(5);

	//// Weights
	//glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, _vertexSize, SizeOf(18));
	//glEnableVertexAttribArray(6);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO); // Apply VBO
	//glBindVertexArray(VAO); // Apply VAO  

	
	// Position attributes
	//coordsCount = dimension + (useColor ? 3 : 0) + 2;
	coordsCount = 3 + 3 + 2;
	const GLsizei& _sizeAttrib = SizeOf<GLsizei>(coordsCount);
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, _sizeAttrib, SizeOf(0));
	glEnableVertexAttribArray(0);

	// Color attributes
	if (useColor)
	{
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _sizeAttrib, SizeOf(dimension));
		//glEnableVertexAttribArray(1);
	}

	// Texture attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, _sizeAttrib, SizeOf(6));
	glEnableVertexAttribArray(2);


	// Normals attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _sizeAttrib, SizeOf(3));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Apply VBO
	glBindVertexArray(VAO); // Apply VAO

	
}

void StaticMeshComponent::InitTextures()
{
	try
	{
		glUseProgram(shaderProgram);
		int _index = 0;
		for (const pair<string, unsigned int>& _pair : allTextures)
		{
			allTextures[_pair.first] = LoadTexture(_pair.first);
		}

		// Diffuse
		const GLuint& _uniformMaterialDiffuse = glGetUniformLocation(shaderProgram, "uniformMaterial.diffuse");
		glUniform1i(_uniformMaterialDiffuse, 0);


		// Specular
		const GLuint& _uniformMaterialSpecular = glGetUniformLocation(shaderProgram, "uniformMaterial.specular");
		glUniform1i(_uniformMaterialSpecular, 1);


		// Shininess
		const GLuint& _uniformMaterialShininess = glGetUniformLocation(shaderProgram, "uniformMaterial.shininess");
		glUniform1f(_uniformMaterialShininess, 64.0f);

	}
	catch (const exception& _error)
	{
		cerr << _error.what() << endl;
	}
}

GLuint StaticMeshComponent::LoadTexture(const string& _filePath)
{
	GLuint _texture;

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Filtrering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLint _textureWidth, _textureHeight, _channelsCount;
	const string& _texturesPath = "D:/Damien/Engine/Content/Textures/";
	const string& _fullPath = _texturesPath + _filePath;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* _data = stbi_load(_fullPath.c_str(), &_textureWidth, &_textureHeight, &_channelsCount, 0);
	if (!_data)
	{
		throw exception(("Error => Failed to load texture at : " + _fullPath + " !").c_str());
	}

	map<GLint, GLint> _formats =
	{
		{1, GL_RED},
		{3, GL_RGB},
		{4, GL_RGBA},
	};

	const GLint& _format = _formats[_channelsCount];

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _textureWidth, _textureHeight, 0, _format, GL_UNSIGNED_BYTE, _data);

	// Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(_data);

	return _texture;
}

void StaticMeshComponent::InitLighting()
{
	unsigned int _uniformLightPos = glGetUniformLocation(shaderProgram, "uniformLightPos");
	glUniform3f(_uniformLightPos, 0.0f, 0.0f, 0.0f);
}

void StaticMeshComponent::UpdateColors()
{
	if (useColor)
	{
		//g 1 out of range aled 

		/*for (unsigned int _index = 0; _index < verticesCount + dimension; _index++)
		{
			vertices[_index * coordsCount + dimension] = (sin(elapsedTime + _index) + 1.0f) / 2.0f;
			vertices[_index * coordsCount + dimension + 1] = (cos(elapsedTime + _index * 0.5f) + 1.0f) / 2.0f;
			vertices[_index * coordsCount + dimension + 2] = (sin(elapsedTime * 0.5f + _index) + 1.0f) / 2.0f;
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, SizeOf<GLsizei>(vertices.size()), vertices.data(), GL_STATIC_DRAW);*/
	}
	else
	{
		GLuint _uniformViewPos = glGetUniformLocation(shaderProgram, "uniformViewPos");
		glUniform3f(_uniformViewPos, camPos.x, camPos.y, camPos.z);


		GLuint _uniformLightPosition = glGetUniformLocation(shaderProgram, "uniformLight.position");
		glUniform3f(_uniformLightPosition, sinf(glfwGetTime()), 0.0f, cosf(glfwGetTime()));

		GLuint _uniformLightAmbient = glGetUniformLocation(shaderProgram, "uniformLight.ambient");
		glUniform3f(_uniformLightAmbient, 1.0f, 1.0f, 1.0f);

		GLuint _uniformLightDiffuse = glGetUniformLocation(shaderProgram, "uniformLight.diffuse");
		glUniform3f(_uniformLightDiffuse, 0.5f, 0.5f, 0.5f);

		GLuint _uniformLightSpecular = glGetUniformLocation(shaderProgram, "uniformLight.specular");
		glUniform3f(_uniformLightSpecular, 1.0f, 1.0f, 1.0f);
	}
}

void StaticMeshComponent::UpdateTextures()
{
	/*int _textureIndex = 0;
	for (const pair<string, unsigned int>& _pair : allTextures)
	{
		glActiveTexture(GL_TEXTURE0 + _textureIndex);
		glBindTexture(GL_TEXTURE_2D, _pair.second);
		_textureIndex++;
	}
	glUseProgram(shaderProgram);*/

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, allTextures["container.png"]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, allTextures["container_specular.png"]);*/


	GLuint _diffuseNr = 1;
	GLuint _specularNr = 1;
	GLuint _normalNr = 1;
	GLuint _heightNr = 1;

	for (GLuint _index = 0; _index < textures.size(); _index++)
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

		// now set the sampler to the correct texture unit

		string _textureName = "uniform";

		switch (_type)
		{
		case aiTextureType_NONE:
			_textureName += "Unknown";
			break;
		case aiTextureType_DIFFUSE:
			_textureName += "Diffuse";
			break;
		case aiTextureType_SPECULAR:
			_textureName += "Specular";
			break;
		case aiTextureType_AMBIENT:
			_textureName += "Ambient";
			break;
		case aiTextureType_EMISSIVE:
			_textureName += "Emissive";
			break;
		case aiTextureType_HEIGHT:
			_textureName += "Height";
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
			break;
		case aiTextureType_NORMAL_CAMERA:
			break;
		case aiTextureType_EMISSION_COLOR:
			break;
		case aiTextureType_METALNESS:
			break;
		case aiTextureType_DIFFUSE_ROUGHNESS:
			break;
		case aiTextureType_AMBIENT_OCCLUSION:
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

		_textureName += "Texture";
		const GLuint& _uniformTextureID = glGetUniformLocation(shaderProgram, (_textureName + _numberText).c_str());
		glUniform1i(_uniformTextureID, _index);

		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[_index].id);
	}

}

void StaticMeshComponent::Draw()
{
	// Un objet
	//glBindVertexArray(VAO);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
	//glBindVertexArray(0);

	// Des triangles
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}

void StaticMeshComponent::SetModel(const mat4& _model)
{
	glUseProgram(shaderProgram);
	SetUniformModel(_model);
}

void StaticMeshComponent::SetView(const mat4& _view)
{
	glUseProgram(shaderProgram);
	SetUniformView(_view);
}

void StaticMeshComponent::SetProjection(const mat4& _projection)
{
	glUseProgram(shaderProgram);
	SetUniformProjection(_projection);
}

void StaticMeshComponent::Clear()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
}
