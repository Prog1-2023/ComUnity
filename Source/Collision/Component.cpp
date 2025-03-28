#include "Component.h"
//#include "Actor.h"
class Actor;

CComponent::CComponent(Actor* _owner)
{
	owner = _owner;
}

CComponent::CComponent(Actor* _owner, const CComponent& _other)
{
	owner = _owner;
}


void CComponent::Construct()
{
	SetActive(true);
}

void CComponent::Deconstruct()
{
	SetActive(false);
}