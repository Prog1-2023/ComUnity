#include "CameraActor.h"
#include "../Actor.h"
#include "../../Editor/World.h"
#include "../../Editor/Windows/Window.h"

CameraActor::CameraActor(World* _world) : Actor(_world)
{
	camera = new CameraComponent(this);
	mesh = new StaticMeshComponent(this);
	allComponents.Add(camera);
	allComponents.Add(mesh);

	viewRadius = -3.0f;
	theta = 0.0f;
	phi = 0.0f;
	speed = 0.05f;
	zoomSpeed = 0.1f;

}

CameraActor::~CameraActor()
{

}

void CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void CameraActor::Tick(const float _deltatime)
{
	Super::Tick(_deltatime);
}

void CameraActor::BeginDestroy()
{
	Super::BeginDestroy();
}

mat4 CameraActor::ComputeView()
{
	vec3 _targetPos = vec3(0.0f);
	mat4 _view = mat4(1.0f);

	const float _pitch = cosf(phi) * cosf(theta) * viewRadius;
	const float _yaw = sinf(phi) * viewRadius;
	const float _roll = cosf(phi) * sinf(theta) * viewRadius;

	const vec3& _cameraPos = vec3(_pitch, _yaw, _roll) + _targetPos;
	const vec3& _up = normalize(vec3(0.0f, cosf(phi), 0.0f));

	cout << _cameraPos.x << "/" << _cameraPos.y << "/" << _cameraPos.z << endl;

	_view = lookAt(_cameraPos, _targetPos, _up);

	return _view;
}
