#pragma once 
#include "../Utils/CoreMinimal.h"
#include"Component.h"
//#include "../Actors/Transform.h"
#include "../Math/Transform.h"

class TransformComponent : public Component
{
    Transform transform;

public:

    FORCEINLINE Transform GetTransform()
    {
        return  transform;
    }
    FORCEINLINE Vector3f GetLocation()
    {
        return transform.location;
    }
    FORCEINLINE void SetLocation(Vector3f _newPos)
    {
        transform.location = _newPos;
    }

    FORCEINLINE Vector3f GetRotation()
    {
        return transform.rotation;
    }
    FORCEINLINE void SetRotation(Vector3f _newRot)
    {
        transform.rotation = _newRot;
    }

    FORCEINLINE Vector3f GetScale()
    {
        return transform.scale;
    }
    FORCEINLINE void SetScale(Vector3f _newScale)
    {
        transform.scale = _newScale;
    }
    FORCEINLINE virtual Component* Clone(Actor* _owner) const override
    {
        return new TransformComponent(_owner, *this);
    }
public:
    TransformComponent(Actor* _owner);
    TransformComponent(Actor* _owner, Transform _transform);
    TransformComponent(Actor* _owner, const TransformComponent& _other);
    ~TransformComponent() = default;

    virtual void Construct() override;
    virtual void Deconstruct() override;
};