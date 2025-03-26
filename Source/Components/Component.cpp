#include "Component.h"
#include "../Actors/Actor.h"

Component::Component(Actor* _actor)
{
	owner = _actor;
}
