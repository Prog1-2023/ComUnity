#include "CameraActor.h"
#include "../../Manager/Level.h"

CameraActor::CameraActor(Level* _level) : Actor(_level)
{
	camera = new CameraComponent(this);
	components.insert(camera);
}
