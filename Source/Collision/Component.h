#pragma once
#include "../Actors/Core.h"
#include "../Utils/CoreMinimal.h"

class CComponent : public Core
{
protected:
	class Actor* owner;

public:
	FORCEINLINE Actor* GetOwner() const
	{
		return owner;
	}

public:
	CComponent(Actor* _owner);
	CComponent(Actor* _owner, const CComponent& _other);
	virtual ~CComponent() = default;

public:
	//TODO 
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void BeginPlay() override {};
	virtual void Tick(const float _deltaTime) override {};
	virtual void BeginDestroy() override {};

	virtual CComponent* Clone(Actor* _owner) const = 0;
};