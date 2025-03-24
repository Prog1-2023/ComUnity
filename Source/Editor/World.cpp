#include "World.h"
#include "Controller.h"
#include "../Actors/Cameras/CameraActor.h"

World::World()
{
	allActors = vector<Actor*>();
	window = nullptr;

	currentCamera = nullptr;
}

World::~World()
{
	for (Actor* _actor : allActors)
	{
		delete _actor;
	}
}

void World::Initialize()
{
	window->GetController()->AddInputAction("CloseWindow", {GLFW_KEY_ESCAPE}, [&]() { glfwSetWindowShouldClose(window->GetWindow(), true); });

	const function<void()>& _moveCameraLeft = bind(&CameraActor::MoveViewLeft, currentCamera);
	window->GetController()->AddInputAction("CameraMoveLeft", {GLFW_KEY_A}, _moveCameraLeft);

	const function<void()>& _moveCameraRight = bind(&CameraActor::MoveViewRight, currentCamera);
	window->GetController()->AddInputAction("CameraMoveRight", { GLFW_KEY_D }, _moveCameraRight);

	const function<void()>& _moveCameraUp = bind(&CameraActor::MoveViewUp, currentCamera);
	window->GetController()->AddInputAction("CameraMoveUp", { GLFW_KEY_W }, _moveCameraUp);

	const function<void()>& _moveCameraDown = bind(&CameraActor::MoveViewDown, currentCamera);
	window->GetController()->AddInputAction("CameraMoveDown", { GLFW_KEY_S }, _moveCameraDown);

	const function<void()>& _zoomInCamera = bind(&CameraActor::ZoomIn, currentCamera);
	window->GetController()->AddInputAction("CameraZoomIn", { GLFW_KEY_Q }, _zoomInCamera);

	const function<void()>& _zoomOutCamera = bind(&CameraActor::ZoomOut, currentCamera);
	window->GetController()->AddInputAction("CameraZoomOut", { GLFW_KEY_E }, _zoomOutCamera);
}

void World::SetVM()
{
	for (Actor* _actor : allActors)
	{
		StaticMeshComponent* _mesh = _actor->GetComponent<StaticMeshComponent>();
		if (!_mesh) continue;

		_mesh->SetView(currentCamera->ComputeView());
		_mesh->SetProjection(currentCamera->GetCamera()->ComputeProjection());
	}
}
