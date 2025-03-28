#pragma once
#include"../Utils/CoreMinimal.h"

struct Transform
{
	Vector3f location;
	Vector3f rotation;
	Vector3f scale;
	
	Transform()
	{
		location = Vector3f(0);
		rotation = Vector3f(0);
		scale = Vector3f(0);
	}
	Transform(Vector3f _location, Vector3f _rotation, Vector3f _scale)
	{
		location = _location;
		rotation = _rotation;
		scale = _scale;
	}

};