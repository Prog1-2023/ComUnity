#pragma once
#include"../Utils/CoreMinimal.h"
#include "Component.h"
//#include "../Editor/Window.h"
#include "../Editor/Windows/Window.h"

class CameraComponent: public Component
{
	float fov;
	float nearDistance;
	float farDistance;
	Window* window;
public:
	FORCEINLINE mat4 ComputeProjection()
	{
		const Vector2i& _windowSize = window->GetSize();
		return glm::perspective(radians(fov), (float)_windowSize.x / (float)_windowSize.y, nearDistance, farDistance);
	}
	FORCEINLINE virtual Component* Clone(Actor* _owner) const override
	{
		return new CameraComponent(_owner, *this);
	}
public:
	CameraComponent(Actor* _owner);
	CameraComponent(Actor* _owner, const CameraComponent& _other);
	~CameraComponent() = default;
	
	virtual void Construct() override;
	virtual void Deconstruct() override;
};

