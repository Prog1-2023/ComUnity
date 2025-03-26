#include "Actor.h"

#include "..\Components\TransformComponent.h"
#include "..\Components\StaticMeshComponent.h"

Actor::Actor(World* _world)
{
	allComponents = vector<Component*>();

	transform = new TransformComponent(this);
	allComponents.push_back(transform);

	world = _world;
}

Actor::~Actor()
{
	const int& _size = static_cast<const int>(allComponents.size());
	for (unsigned int _index = 0; _index < _size; _index++)
		delete allComponents[_index];
}

void Actor::BeginPlay()
{
	const int& _size = static_cast<const int>(allComponents.size());
	for (unsigned int _index = 0; _index < _size; _index++)
		allComponents[_index]->BeginPlay();
}
void Actor::Tick(const float& _deltaTime)
{
	const int& _size = static_cast<const int>(allComponents.size());
	for (unsigned int _index = 0; _index < _size; _index++)
		allComponents[_index]->Tick(_deltaTime);
}

void Actor::BeginDestroy()
{
	const int& _size = static_cast<const int>(allComponents.size());
	for (unsigned int _index = 0; _index < _size; _index++)
		allComponents[_index]->BeginDestroy();
		
}

void Actor::LoadModel(const string& _path)
{
	Importer _importer = Importer();
	const string& _fullPath = GetPath(CONTENT) + _path;
	const aiScene* _scene = _importer.ReadFile(_fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);
	const string& _errorMessage = "Error => " + string(_importer.GetErrorString());
	Assert(_scene && _scene->mRootNode && !(_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE), _errorMessage.c_str());
	
	//const string& _directory = _path.substr(0, _path.find_last_of('/'));

	/*StaticMeshComponent* _meshComponent = new StaticMeshComponent(this);
	ComputeMesh(_meshComponent, _scene, _scene->mRootNode);
	allComponents.push_back(_meshComponent);*/

	ComputeMeshes(_scene, _scene->mRootNode);
}

void Actor::ComputeMeshes(const aiScene* _scene, const aiNode* _node)
{
	const unsigned int& _amount = _node->mNumMeshes;
	for (GLuint _index = 0; _index < _amount; _index++)
	{
		StaticMeshComponent* _meshComponent = new StaticMeshComponent(this);
		aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[_index]];
		_meshComponent->GenerateShapeFromModel(_mesh, _scene);
		allComponents.push_back(_meshComponent);
	}

	const unsigned int& _childrenAmount = _node->mNumChildren;
	for (GLuint _index = 0; _index < _childrenAmount; _index++)
	{
		ComputeMeshes(_scene, _node->mChildren[_index]);
	}
}

void Actor::ComputeMesh(StaticMeshComponent* _meshComponent, const aiScene* _scene, const aiNode* _node)
{
	const unsigned int& _amount = _node->mNumMeshes;
	for (GLuint _index = 0; _index < _amount; _index++)
	{
		aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[_index]];
		_meshComponent->GenerateShapeFromModel(_mesh, _scene);
	}

	const unsigned int& _childrenAmount = _node->mNumChildren;
	for (GLuint _index = 0; _index < _childrenAmount; _index++)
	{
		ComputeMesh(_meshComponent, _scene, _node->mChildren[_index]);
	}
}
