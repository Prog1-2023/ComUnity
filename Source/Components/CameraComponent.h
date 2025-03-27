#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Components/Component.h"
#include "../Editor/Windows/Window.h"

class CameraComponent : public Component
{
	vec3 targetPos;
	float fov;
	float nearDistance;
	float farDistance;
	Window* window;

public:
	FORCEINLINE mat4 ComputeView()
	{
		Controller* _controller = window->GetController();
		const float& _theta = _controller->theta;
		const float& _phi = _controller->phi;
		const float& _viewRadius = _controller->viewRadius;
		const float& _pitch = cos(_phi) * cos(_theta) * _viewRadius;
		const float& _yaw = sin(_phi) * _viewRadius;
		const float& _roll = cos(_phi) * sin(_theta) * _viewRadius;
		const vec3& _cameraPosition = vec3(_pitch, _yaw, _roll) + targetPos;
		vec3 _up = normalize(vec3(0.0f, cos(_phi), 0.0f));
		return lookAt(_cameraPosition, targetPos, _up);
	}
	/*FORCEINLINE mat4 ComputeView()
	{
		const float _pitch = cosf(window->GetController()->phi) * cosf(window->GetController()->theta) * window->GetController()->viewRadius;
		const float _yaw = sinf(window->GetController()->phi) * window->GetController()->viewRadius;
		const float _roll = cosf(window->GetController()->phi) * sinf(window->GetController()->theta) * window->GetController()->viewRadius;
		const vec3& _cameraPos = vec3(_pitch, _yaw, _roll) + targetPos;
		vec3 _up = vec3(0, 1.0f, 0);
		if (window->GetController()->phi > half_pi<float>() || window->GetController()->phi < -half_pi<float>())
		{
			_up.y *= -1;
		}
		return lookAt(_cameraPos, targetPos, _up);
	}*/
	FORCEINLINE mat4 ComputeProjection()
	{
		const Vector2i& _windowSize = window->GetSize();
		return perspective(radians(fov), (float)_windowSize.x / (float)_windowSize.y, nearDistance, farDistance);
	}
public:
	CameraComponent(Actor* _owner);
	~CameraComponent() =default;
};

