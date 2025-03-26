#pragma once

#include "../Utils/CoreMinimal.h"
#include "../Components/Component.h"
#include "../Components/TransformComponent.h"

class World;
class StaticMeshComponent;
class DeprTexture;

class Actor
{
protected:
	vector<Component*> allComponents;
	TransformComponent* transform;
	World* world;
	std::vector<DeprTexture> texturesAlreadyLoaded;

public:
	FORCEINLINE World* GetWorld() const { return world; }
	FORCEINLINE std::vector<DeprTexture>& GetTextureAlreadyLoadedRef() { return texturesAlreadyLoaded; }

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
		FOR(allComponents)
			if (Type* _type = dynamic_cast<Type*>(allComponents[_index]))
				return _type;
		return nullptr;
	}
};

