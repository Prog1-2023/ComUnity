#pragma once

#include "../Utils/CoreMinimal.h"
#include "Component.h"
#include "../Editor/Windows/Window.h"

class CameraComponent : public Component
{
	float fov;
	float nearDistance;
	float farDistance;
	Window* window;
	vec3 targetPosition;

public:
	FORCEINLINE mat4 ComputeProjection()
	{
		const Vector2i& _size = window->GetSize();
		return perspective(radians(fov), (float)_size.x / (float)_size.y, nearDistance, farDistance);
	}
	FORCEINLINE mat4 ComputeView()
	{
		Controller* _controller = window->GetController();
		const float& _theta = _controller->theta;
		const float& _phi = _controller->phi;
		const float& _viewRadius = _controller->viewRadius;
		const float& _pitch = cos(_phi) * cos(_theta) * _viewRadius;
		const float& _yaw = sin(_phi) * _viewRadius;
		const float& _roll = cos(_phi) * sin(_theta) * _viewRadius;
		const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + targetPosition;
		vec3 _up = normalize(vec3(0.0f, cos(_phi), 0.0f));
		return lookAt(_cameraPosition, targetPosition, _up);
	}

public:
	CameraComponent(Actor* _owner);
	~CameraComponent() = default;
};
