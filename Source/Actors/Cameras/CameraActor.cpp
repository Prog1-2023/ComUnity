#include "CameraActor.h"

CameraActor::CameraActor(World* _world) : Actor(_world)
{
	camera = new CameraComponent(this);
	allComponents.push_back(camera);
}
