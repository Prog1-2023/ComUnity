#include "TransformComponent.h"
#include "../Serialization/SerializationValue.h"

TransformComponent::TransformComponent(Actor* _owner) : Component(_owner)
{
	localLocation = Vector3f();
	location = Vector3f();
	rotation = Vector3f();
	scale = Vector3f();

	SERIALIZE(this,TransformComponent,READ,bool,physics);
	SERIALIZE(this,TransformComponent,READ,int, moveSpeed);
	SERIALIZE(this,TransformComponent,READ,float, rotateSpeed);
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
