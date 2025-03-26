#pragma once 
#include "../Utils/CoreMinimal.h"
#include"Component.h"
#include "../Actors/Transform.h"

class TransformComponent : public Component
{ 
	Transform transform;

public:

	FORCEINLINE Transform GetTransform()
	{
		return  transform;
	}
	FORCEINLINE Vector3f GetLocation()
	{
		return transform.location;
	}
	FORCEINLINE void SetLocation(const Vector3f& _newPos)
	{
		transform.location=_newPos;
	}

	FORCEINLINE Vector3f GetRotation()
	{
		return transform.rotation;
	}
	FORCEINLINE void SetRotation(const Vector3f& _newRot)
	{
		transform.rotation = _newRot;
	}
	
	FORCEINLINE Vector3f GetScale()
	{
		return transform.scale;
	}
	FORCEINLINE void SetScale(const Vector3f& _newScale)
	{
		transform.scale= _newScale;
	}
	FORCEINLINE void Move(const Vector3f& _offset)
	{
		transform.location += _offset;
	}
	
	FORCEINLINE void Rotate(const Vector3f& _offset)
	{
		transform.rotation += _offset;
	}
	
	FORCEINLINE void Scale(const Vector3f& _offset)
	{
		transform.scale += _offset;
	}
	
public:
	TransformComponent (Actor* _owner);
	TransformComponent (Actor* _owner,Transform _transform);
	~TransformComponent();

public:
	virtual Component* Clone(Actor* _owner) const override { return nullptr; }
};