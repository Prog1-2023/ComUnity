#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* _owner) : Component(_owner)
{
	localLocation = Vector3f();
	location = Vector3f();
	rotation = Vector3f();
	scale = Vector3f();

	physics = false;

	vectorTest = Vector3f(1.0f, 2.0f,3.0f);
	vectorTest.SetSerializeValue();
	SERIALIZE(owner, TransformComponent, READ, bool, physics);
	SERIALIZE(owner, TransformComponent, READ, int, moveSpeed);
	SERIALIZE(owner, TransformComponent, WRITE, float, rotateSpeed);
	SERIALIZE(owner, TransformComponent, READ, Vector3f, vectorTest);
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
