#include "CameraActor.h"
#include "../../Editor/World.h"

CameraActor::CameraActor(Level* _level) : Actor(_level)
{
	camera = nullptr;
	//allComponents.push_back(camera);
}

void CameraActor::Construct()
{
	SUPER::Construct();
	camera = CreateComponent<CameraComponent>();

}
