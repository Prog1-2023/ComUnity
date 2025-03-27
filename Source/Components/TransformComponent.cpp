#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* _owner) : Component(_owner)
{
	localLocation = Vector3f();
	location = Vector3f();
	rotation = Vector3f();
	scale = Vector3f();

	physics = false;

	SERIALIZE(owner,TransformComponent,READ,bool,physics);
	SERIALIZE(owner,TransformComponent,READ,int, moveSpeed);
	SERIALIZE(owner,TransformComponent,WRITE,float, rotateSpeed);
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::BeginPlay()
{
	Super::BeginPlay();
}

void TransformComponent::Tick(const float _deltatime)
{
	Super::Tick(_deltatime);
}

void TransformComponent::BeginDestroy()
{
	Super::BeginDestroy();
}
