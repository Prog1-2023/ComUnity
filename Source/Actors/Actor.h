#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Components/Component.h"
#include "../Components/TransformComponent.h"

class StaticMeshComponent;

class Actor
{
	class World* world;
protected:
	vector<Component*> allComponents;
	TransformComponent* transform;

public:
	FORCEINLINE World* GetWorld() const { return world; }
	FORCEINLINE Vector3f GetActorLocalLocation() { return transform->GetLocalLocation(); }
	FORCEINLINE Vector3f GetActorLocation() { return transform->GetLocation(); }
	FORCEINLINE Vector3f GetActorRotation() { return transform->GetRotation(); }
	FORCEINLINE Vector3f GetActorScale() { return transform->GetScale(); }

	FORCEINLINE void SetActorLocalLocation(const Vector3f& _location) { transform->SetLocalLocation(_location); }


public:
	Actor(World* _world);
	virtual ~Actor();

public:
	virtual void BeginPlay();
	virtual void BeginDestroy();
	virtual void Tick(const float _deltatime);

	void LoadModel(const string& _path);

	template <typename Type>
	Type* GetComponent()
	{
		for (Component* _component : allComponents)
		{
			if (Type* _type = dynamic_cast<Type*>(_component))
			{
				return _type;
			}
		}
		return nullptr;
	}
	
	template <typename Type = Component>
	void AddComponent()
	{
		Type* _newComponent = new Type(this);
		allComponents.push_back(_newComponent);
	}

	void SetActorLocation(const Vector3f& _location);
	void SetActorRotation(const Vector3f& _rotation);
	void SetActorScale(const Vector3f& _scale);

private:
	void ComputeMeshes(const aiScene* _scene, const aiNode* _node, StaticMeshComponent* _meshComponent);
	void ComputeMeshes(const aiScene* _scene, const aiNode* _node);

};

