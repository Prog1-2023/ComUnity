#pragma once
#include"../Utils/CoreMinimal.h"
#include "Core.h"
#include "../Components/TransformComponent.h"
#include"../Components/ITransformableModifier.h"
#include"../Components/ITransformableViewer.h"
#include "../Components/StaticMeshComponent.h"

//#include "TransformableModifier.h"
//#include "TransformableViewer.h"
//#include "Component.h"
//#include "RootComponent.h"
//#include "Layer.h"


struct CollisionData;

enum AttachmentType
{
	AT_KEEP_RELATIVE,
	AT_KEEP_WORLD,
	AT_SNAP_TO_TARGET,
	AT_NONE,
};

enum LayerType
{
	WORLD_STATIC,
	WORLD_DYNAMIC,
	PLAYER,
	PROJECTILE,
	BREAKABLE,
	RETRIEVABLE,
	COUNT
};

//using namespace Layer;

class Actor : public Core, public ITransformableModifier, public ITransformableViewer
{
	bool isToDelete;
	u_int id;
protected:
	
	float lifeSpan;
	LayerType layer;
private:
	string name;
	string displayName;
	set<Component*> components;
	TransformComponent* root;
	Actor* parent;
	AttachmentType attachment;
	set<Actor*> children;
	Transform oldTransform;

protected:
	

public:
#pragma region Delete
	FORCEINLINE void SetToDelete()
	{
		isToDelete = true;
	}
	FORCEINLINE bool IsToDelete() const
	{
		return isToDelete;
	}
#pragma endregion

#pragma region ID/Name
	FORCEINLINE u_int GetID() const
	{
		return id;
	}
	FORCEINLINE string GetName() const
	{
		return name;
	}
	FORCEINLINE string GetDisplayName() const
	{
		return displayName;
	}
#pragma endregion

#pragma region Layer
	FORCEINLINE void SetLayerType(const LayerType& _layer)
	{
		layer = _layer;
	}
	FORCEINLINE LayerType GetLayerType() const
	{
		return layer;
	}
#pragma endregion

#pragma region Level

	/*template<typename Type = Level, IS_BASE_OF(Level, Type)>
	FORCEINLINE Type* GetLevel()
	{
		if (InstanceOf<Type>(level))
		{
			return level;
		}

		return Cast<Type>(level);
	}*/
	

#pragma endregion

#pragma region Children

private:
	FORCEINLINE void SetParent(Actor* _parent)
	{
		parent = _parent;
	}
	FORCEINLINE void UpdateChildTransform(Actor* _child)
	{
		UpdateChildPosition(_child);
		UpdateChildRotation(_child);
		UpdateChildScale(_child);
		
	}
	FORCEINLINE void UpdateChildPosition(Actor* _child)
	{
		const vector<function<Vector3f()>>& _computePosition =
		{
			// Keep the child’s relative position to the parent.
			[&]() { return _child->GetPosition() + GetPosition() - oldTransform.location; },
			// Keep the child’s world position.
			[&]() { return _child->GetPosition(); },
			// Snap the child to the parent's position.
			[&]() { return GetPosition(); },
		};

		const AttachmentType& _type = _child->GetAttachmentType();
		_child->SetPosition(_computePosition[_type]());
	}
	FORCEINLINE void UpdateChildRotation(Actor* _child)
	{
		const vector<function<Vector3f()>>& _computeRotation =
		{
			// Keep the child’s relative rotation to the parent.
			[&]() { return _child->GetRotation() + GetRotation() - oldTransform.location; },
			// Keep the child’s world rotation.
			[&]() { return _child->GetRotation(); },
			// Snap the child to the parent's rotation.
			[&]() { return GetRotation(); },
		};

		const AttachmentType& _type = _child->GetAttachmentType();
		_child->SetRotation(_computeRotation[_type]());
	}
	FORCEINLINE void UpdateChildScale(Actor* _child)
	{
		const vector<function<Vector3f()>>& _computeScale =
		{
			// Keep the child’s relative scale to the parent.
			[&]()
			{
				return Vector3f(_child->GetScale().x * GetScale().x, _child->GetScale().y * GetScale().y, _child->GetScale().z * GetScale().z);
			},
			// Keep the child’s world scale.
			[&]() { return _child->GetScale(); },
			// Snap the child to the parent's scale.
			[&]() { return GetScale(); },
		};

		const AttachmentType& _type = _child->GetAttachmentType();
		_child->SetScale(_computeScale[_type]());
	}
	

public:
	FORCEINLINE void AddChild(Actor* _child, const AttachmentType& _type)
	{
		_child->SetAttachmentType(_type);
		_child->SetParent(this);
		//UpdateChildTransform(_child);
		children.insert(_child);
	}
	FORCEINLINE void RemoveChild(Actor* _child)
	{
		if (!_child || !children.contains(_child)) return;

		_child->SetParent(nullptr);
		children.erase(_child);
	}
	FORCEINLINE void SetAttachmentType(const AttachmentType& _attachment)
	{
		attachment = _attachment;
	}
	FORCEINLINE AttachmentType GetAttachmentType() const
	{
		return attachment;
	}
	FORCEINLINE Actor* GetParent() const
	{
		return parent;
	}
	FORCEINLINE set<Actor*> GetChildren() const
	{
		return children;
	}
	FORCEINLINE Actor* GetChildrenAtIndex(const int _index) const
	{
		set<Actor*>::const_iterator _it = children.begin();
		advance(_it, _index);
		return *_it;
	}

#pragma endregion

#pragma region Transformable

#pragma region Viewer

	
	FORCEINLINE virtual Vector3f GetPosition() const override
	{
		return root->GetLocation();
	}
	FORCEINLINE virtual Vector3f GetRotation() const override
	{
		return root->GetRotation();
	}
	FORCEINLINE virtual Vector3f GetScale() const override
	{
		return root->GetScale();
	}
	FORCEINLINE virtual Transform GetTransform() const override
	{
		return root->GetTransform();
	}
	FORCEINLINE Vector3f GetForwardVector() const
	{
		/** Yaw (degrees) around Z axis */
		Vector3f _rotation = GetRotation();
		float _yaw = _rotation.z;
		float _pitch = _rotation.y;

		float _cosYaw = cos(Angle(_yaw, false).GetRadiant());
		float _cosPitch = cos(Angle(_pitch, false).GetRadiant());
		
		float _sinYaw = sin(Angle(_yaw, false).GetRadiant());
		float _sinPitch = sin(Angle(_pitch, false).GetRadiant());
		//Todo Normalize

		return Vector3f(_cosPitch * _cosYaw, _sinPitch, _cosPitch * _sinYaw);
	}
	FORCEINLINE Vector3f GetUpVector() const
	{
		Vector3f _rotation = GetRotation();
		float _yaw = _rotation.z;
		float _pitch = _rotation.y;

		float _cosYaw = cos(Angle(_yaw, false).GetRadiant());
		float _cosPitch = cos(Angle(_pitch, false).GetRadiant());

		float _sinYaw = sin(Angle(_yaw, false).GetRadiant());
		float _sinPitch = sin(Angle(_pitch, false).GetRadiant());
		return Vector3f(_sinPitch * _sinYaw, -_cosPitch, _cosPitch * _cosYaw);
	}
	FORCEINLINE Vector3f GetRightVector() const
	{
		Vector3f _rotation = GetRotation();
		float _yaw = _rotation.z;
		float _pitch = _rotation.y;

		float _cosYaw = cos(Angle(_yaw, false).GetRadiant());
		float _cosPitch = cos(Angle(_pitch, false).GetRadiant());

		float _sinYaw = sin(Angle(_yaw, false).GetRadiant());
		float _sinPitch = sin(Angle(_pitch, false).GetRadiant());
		return Vector3f(_sinYaw*_cosPitch,0,-_cosYaw*_cosPitch);
	}
	
	

#pragma endregion

#pragma region Modifier

	FORCEINLINE virtual void SetPosition(const Vector3f& _position) override
	{
		oldTransform.location = GetPosition();
		root->SetLocation(_position);

		for (Actor* _child : children)
		{
			UpdateChildPosition(_child);
		}
	}
	FORCEINLINE virtual void SetRotation(const Vector3f& _rotation) override
	{
		oldTransform.rotation = GetRotation();
		root->SetRotation(_rotation);

		for (Actor* _child : children)
		{
			UpdateChildRotation(_child);
		}
	}
	FORCEINLINE virtual void SetScale(const Vector3f& _scale) override
	{
		oldTransform.scale = GetScale();
		root->SetScale(_scale);

		for (Actor* _child : children)
		{
			UpdateChildScale(_child);
		}
	}
	
	FORCEINLINE virtual void Move(const Vector3f& _offset) override
	{
		root->Move(_offset);

		for (Actor* _child : children)
		{
			_child->Move(_offset);
		}
	}
	FORCEINLINE virtual void Rotate(const Vector3f& _offset) override
	{
		root->Rotate(_offset);

		for (Actor* _child : children)
		{
			_child->Rotate(_offset);
		}
	}
	FORCEINLINE virtual void Scale(const Vector3f& _factor) override
	{
		root->Scale(_factor);

		for (Actor* _child : children)
		{
			_child->Scale(_factor);
		}
	}

#pragma endregion

#pragma endregion

#pragma region Component
public: //TODO protected
	template <typename Type, typename ...Args, IS_BASE_OF(Component, Type)>
	FORCEINLINE Type* CreateComponent(Args&&... _args)
	{
		Type* _component = new Type(this, forward<Args>(_args)...);
		AddComponent(_component);
		return _component;
	}

public:
	FORCEINLINE virtual void SetActive(const bool _status) override
	{
		SUPER::SetActive(_status);

		for (Component* _component : components)
		{
			//_component->SetActive(_status);
		}
	}
#pragma endregion

public:
	Actor(Level* _world, const string& _name = "Actor", const Transform& _transform = Transform());
	Actor(const Actor& _other);
	virtual ~Actor();

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

	void Register();
	void Unregister();
	void SetName(const string& _name);
	void CreateSocket(const string& _name, const Transform& _transform = Transform(), const AttachmentType& _type = AT_SNAP_TO_TARGET);
	void Destroy();



#pragma region TODO MOVE INTO STATICMESH OR OTHER CLASS IDK
private:
	void ComputeMesh(StaticMeshComponent* _meshComponent, const aiScene* _scene, const aiNode* _node);
public:
	void LoadModel(const string& _path);
	void ComputeMeshes(const aiScene* _scene, const aiNode* _node);
#pragma endregion



#pragma region Components

	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);

	template <typename Type, IS_BASE_OF(Component, Type)>
	Type* GetComponent() const
	{
		for (Component* _component : components)
		{
			if (Type* _result = dynamic_cast<Type*>(_component)) return _result;
		}

		return nullptr;
	}

#pragma endregion

#pragma region Collision

	virtual void CollisionEnter(const CollisionData& _data) {}
	virtual void CollisionUpdate(const CollisionData& _data) {}
	virtual void CollisionExit(const CollisionData& _data) {}

#pragma endregion
};
