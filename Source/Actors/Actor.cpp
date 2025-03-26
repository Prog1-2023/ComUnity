/*
#include "Actor.h"
#include "../Editor/World.h"
#include"../Components/StaticMeshComponent.h"

Actor::Actor(World* _world)
{
	allComponents = vector<Component*>();

	transform = new  TransformComponent(this);
	allComponents.push_back(transform);
	world = _world;
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
		_component->BeginPlay() ;
	}
}

void Actor::Tick(const float _deltaTime)
{
	for (Component* _component : allComponents)
	{
		_component->Tick(_deltaTime);
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
	const string& _fullPath = GetPath(CONTENT) + _path;
	const aiScene* _scene = _importer.ReadFile(_fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);
	const string& _errorMessage = "Error => " + string(_importer.GetErrorString());
	Assert(_scene && _scene->mRootNode && !(_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE), _errorMessage.c_str());

	//const string& _directory = _path.substr(0, _path.find_last_of('/'));

	//StaticMeshComponent* _meshComponent = new StaticMeshComponent(this);
	//ComputeMesh(_meshComponent, _scene, _scene->mRootNode);
	//allComponents.push_back(_meshComponent);

	ComputeMesh(_scene, _scene->mRootNode);

}

void Actor::ComputeMesh(const aiScene* _scene, const aiNode* _node)
{
	for (GLuint _index = 0; _index < _node->mNumMeshes; _index++)
	{
		aiMesh* _mesh = _scene->mMeshes[_node->mMeshes[_index]];

		StaticMeshComponent* _meshComponent = new StaticMeshComponent(this);
		_meshComponent->GenerateShapeFromModel(_mesh, _scene);
		allComponents.push_back(_meshComponent);
	}

	for (GLuint i = 0; i < _node->mNumChildren; i++)
	{
		ComputeMesh(_scene, _node->mChildren[i]);
	}

}
*/
#include "Actor.h"
#include "../Manager/ActorManager.h"
#include"../Manager/Level.h"
//#include "TimerManager.h"


Actor::Actor(Level* _world, const string& _name, const Transform& _transform):Core(_world)
{
	

	isToDelete = false;
	id = 0;
	lifeSpan = 0.0f;
	name = _name;
	
	displayName = "Unknown";
	components = set<Component*>();
	root = CreateComponent<TransformComponent>(_transform);
	parent = nullptr;
	attachment = AT_NONE;
	children = set<Actor*>();
}

Actor::Actor(const Actor& _other):Core(_other.world)
{
	isToDelete = _other.isToDelete;
	id = _other.id;
	lifeSpan = _other.lifeSpan;
	name = _other.name;
	displayName = _other.displayName;
	
	for (Component* _component : _other.components)
	{
		//AddComponent(_component->Clone(this));
	}

	root = GetComponent<TransformComponent>();
	parent = _other.parent;
	attachment = _other.attachment;
	for (Actor* _child : _other.children)
	{
		children.insert(new Actor(*_child));
	}
	
}

Actor::~Actor()
{
	for (Component* _component : components)
	{
		delete _component;
	}
}


void Actor::Construct()
{
	
	Assert(world, "ERROR Construct => Level of Actor is nullptr");

		

	//id = GetUniqueID();
	displayName = world->GetActorManager().GetAvailableName(name);
	SetActive(true);

	for (Component* _component : components)
	{
		//_component->Construct();
	}
}

void Actor::Deconstruct()
{
	for (Component* _component : components)
	{
		//_component->Deconstruct();
	}

	SetActive(false);
	Unregister();
}

void Actor::BeginPlay()
{
	if (lifeSpan > 0.0f)
	{
		//new Timer(bind(&Actor::Destroy, this), seconds(lifeSpan), true);
	}

	for (Component* _component : components)
	{
		_component->BeginPlay();
	}
}

void Actor::Tick(const float _deltaTime)
{
	for (Component* _component : components)
	{
		_component->Tick(_deltaTime);
	}
}

void Actor::BeginDestroy()
{
	for (Component* _component : components)
	{
		_component->BeginDestroy();
	}
}


void Actor::Register()
{
	world->GetActorManager().AddActor(this);
}

void Actor::Unregister()
{
	world->GetActorManager().RemoveActor(this);
}

void Actor::SetName(const string& _name)
{
	if (name == _name) return;

	name = _name;
	displayName = world->GetActorManager().GetDisplayName(this);
}

void Actor::CreateSocket(const string& _name, const Transform& _transform, const AttachmentType& _type)
{
	Actor* _socket = world->SpawnActor<Actor>(_name, _transform);
	AddChild(_socket, _type);
}

void Actor::Destroy()
{
	SetToDelete();
}

void Actor::AddComponent(Component* _component)
{
	components.insert(_component);
}

void Actor::RemoveComponent(Component* _component)
{
	components.erase(components.find(_component));
}