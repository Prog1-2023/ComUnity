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

	float viewRadius;
	float theta;
	float phi;
	float speed;
	float zoomSpeed;

public:
	FORCEINLINE virtual Component* Clone(Actor* _owner) const override
	{
		return new CameraComponent(_owner, *this);
	}
	FORCEINLINE float GetViewRadius() const { return viewRadius; }
	FORCEINLINE float GetTheta() const { return theta; }
	FORCEINLINE float GetPhi() const { return phi; }
	FORCEINLINE float GetSpeed() const { return speed; }
	FORCEINLINE float GetZoomSpeed() const { return zoomSpeed; }
	FORCEINLINE void ZoomIn() { viewRadius += zoomSpeed; }
	FORCEINLINE void ZoomOut() { viewRadius -= zoomSpeed; }
	FORCEINLINE void MoveViewUp() { phi += speed; }
	FORCEINLINE void MoveViewDown() { phi -= speed; }
	FORCEINLINE void MoveViewLeft() { theta -= speed; }
	FORCEINLINE void MoveViewRight() { theta += speed; }
public:
	CameraComponent(Actor* _owner);
	CameraComponent(Actor* _owner, const CameraComponent& _other);
	~CameraComponent() = default;

public:
	FORCEINLINE mat4 ComputeView(Window* _window)
	{
		const float _pitch = viewRadius * sin(phi);
		const float _yaw = viewRadius * cos(phi) * sin(theta);
		const float _roll = viewRadius * cos(phi) * cos(theta);
		const vec3 _cameraPosition = vec3(_roll, _pitch, _yaw) + targetPos;
		vec3 _up = vec3(0.0f, 1.0f, 0.0f);
		return lookAt(_cameraPosition, targetPos, _up);
	}

	virtual void Construct() override;
	virtual void Deconstruct() override;

};