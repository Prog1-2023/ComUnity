#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Components/Component.h"
#include "../Components/TransformComponent.h"

class World;
class StaticMeshComponent;

class Actor
{
protected:
	vector<Component*> allComponents;
	TransformComponent* transform;
	World* world;

public:
	FORCEINLINE World* GetWorld() const { return world; }
	FORCEINLINE vector<Component*> GetAllComponents() const { return allComponents; }
	FORCEINLINE TransformComponent* GetTransform() const { return transform; }

public:
	Actor(World* _world);
	virtual ~Actor();

	virtual void BeginPlay();
	virtual void Tick(const float& _deltaTime);
	virtual void BeginDestroy();

private:
	void ComputeMesh(StaticMeshComponent* _meshComponent, const aiScene* _scene, const aiNode* _node);

public:
	void LoadModel(const string& _path);

	void ComputeMeshes(const aiScene* _scene, const aiNode* _node);

	template <typename Type>
	Type* GetComponent()
	{
		
		for (int i = 0; i < allComponents.size(); i++)
		{
			if (Type* _type = dynamic_cast<Type*>(allComponents[i]))
				return _type;
		}
		return nullptr;
	}
};

