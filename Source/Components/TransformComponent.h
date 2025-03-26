#pragma once
#include "Component.h"

class TransformComponent : public Component
{
	Vector3f position;
	Vector3f LocalPosition;
	Vector3f rotation;
	Vector3f scale;
	
public:
	Vector3f GetPosition() const
	{
		return position;
	}
	Vector3f GetLocalPosition() const
	{
		return LocalPosition;
	}
	Vector3f GetRotation() const
	{
		return rotation;
	}
	Vector3f GetScale() const
	{
		return scale;
	}
	void SetPosition(Vector3f _position)
	{
		position = _position;
	}
	void SetLocalPosition(Vector3f _position)
	{
		LocalPosition = _position;
	}
	void SetRotation(Vector3f _rotation)
	{
		rotation = _rotation;
	}
	void SetScale(Vector3f _scale)
	{
		scale = _scale;
	}

public:
	TransformComponent(Actor* _owner);


};

