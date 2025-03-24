#pragma once
#include "../Utils/CoreMinimal.h"
#include "Component.h"
#include "../Editor/Windows/Window.h"

class CameraComponent : public Component
{
	unsigned int shader;
	unsigned int uniformView;

	float fov;
	float nearDistance;
	float farDistance;

	Window* window;

public:
	FORCEINLINE mat4 ComputeProjection() const
	{
		const float _height = (float)window->GetSize().x;
		const float _wigth = (float)window->GetSize().x;

		return perspective(radians(fov), _height / _wigth, nearDistance, farDistance);
	}

public:
	CameraComponent(Actor* _owner);
	~CameraComponent() = default;

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltatime) override;
	virtual void BeginDestroy() override;
};

