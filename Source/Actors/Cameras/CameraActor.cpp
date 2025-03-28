#include "CameraActor.h"
#include "../../Editor/World.h"
#include "../../Manager/SoundManager.h"
#include "../../Components/TransformComponent.h"
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

void CameraActor::Tick(float _deltatime)
{
	SUPER::Tick(_deltatime);
	//TODO location and rotation never change always at 0,0,0
	//Vector3f _location = GetPosition();
	//Vector3f _rotation = GetRotation();
	//SoundManager::GetInstance().SetListener(_location, _rotation);
}
