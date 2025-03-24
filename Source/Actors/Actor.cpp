#include "Actor.h"
#include "../Components/StaticMeshComponent.h"

Actor::Actor(World* _world)
{
	world = _world;

	allComponents = vector<Component*>();
	transform = new TransformComponent(this);
	allComponents.push_back(transform);
}

Actor::~Actor()
{
	for (Component* _component : allComponents)
	{
		delete _component;
	}
}

void Actor::BeginPlay()
{
	for (Component* _component : allComponents)
	{
		_component->BeginPlay();
	}
}

void Actor::Tick(const float _deltatime)
{
	for (Component* _component : allComponents)
	{
		_component->Tick(_deltatime);
	}
}

void Actor::BeginDestroy()
{
	for (Component* _component : allComponents)
	{
		_component->BeginDestroy();
	}
}

void Actor::LoadModel(const string& _path)
{
	Importer _importer = Importer();
	const aiScene* _scene = _importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!_scene) return;

	const string& _errorString = string("Error => ") + string(_importer.GetErrorString());
	const aiNode* _node = _scene->mRootNode;
	Assert(_scene && _scene->mRootNode && !(_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE), _errorString.c_str());

	StaticMeshComponent* _meshComponent = new StaticMeshComponent(this);
	ComputeMeshes(_scene,_node, _meshComponent);
	allComponents.push_back(_meshComponent);
	//ComputeMeshes(_scene,_node);
}

void Actor::SetActorLocation(const Vector3f& _location)
{
	transform->SetLocation(_location);

	StaticMeshComponent* _mesh = GetComponent<StaticMeshComponent>();
	if (!_mesh) return;

	mat4 _matrix = mat4(1.0f);
	vec3 _newLocation = Vector3f::CreateVecFromVector(_location);
	_matrix = translate(_matrix, _newLocation);
	_mesh->SetModel(_matrix);
}

void Actor::SetActorRotation(const Vector3f& _rotation)
{
	transform->SetRotation(_rotation);
}

void Actor::SetActorScale(const Vector3f& _scale)
{
	transform->SetScale(_scale);
}

void Actor::ComputeMeshes(const aiScene* _scene, const aiNode* _node, StaticMeshComponent* _meshComponent)
{
	GLuint _meshesSize = _node->mNumMeshes;
	for (GLuint _i = 0; _i < _meshesSize; _i++)
	{
		aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[_i]];
		_meshComponent->GenerateShapeFromModel(_mesh,_scene);
	}

	GLuint _childrenSize = _node->mNumChildren;
	for (GLuint _i = 0; _i < _childrenSize; _i++)
	{
		// Recursive
		ComputeMeshes(_scene,_node->mChildren[_i], _meshComponent);
	}

}

void Actor::ComputeMeshes(const aiScene* _scene, const aiNode* _node)
{
	GLuint _meshesSize = _node->mNumMeshes;
	for (GLuint _i = 0; _i < _meshesSize; _i++)
	{
		aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[_i]];
		StaticMeshComponent* _meshComponent = new StaticMeshComponent(this);
		_meshComponent->GenerateShapeFromModel(_mesh, _scene);
		allComponents.push_back(_meshComponent);
	}

	GLuint _childrenSize = _node->mNumChildren;
	for (GLuint _i = 0; _i < _childrenSize; _i++)
	{
		// Recursive
		ComputeMeshes(_scene, _node->mChildren[_i]);
	}
}
