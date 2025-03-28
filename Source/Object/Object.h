#pragma once
//#include "../Utils/CoreMinimal.h"
// ReactPhysics3D
//#include <reactphysics3d/reactphysics3d.h>
//
//using namespace rp3d;

//template<typename T>

enum ShapeType
{
	NONE,
	BOX,
	CAPSULE,
	SPHERE,
	CONVEX,
	MAX
};

struct ParametersShape
{

};

class Object
{

	//RigidBody* rb;
	//Collider* collider;
	//Material* mat;

	//CollisionShape* shape;

public:
	//template<typename Params> //TODO MOVE _world and physics common ! 
	//Object(PhysicsWorld* _world, PhysicsCommon& _common, const ShapeType& _shapeType, Params  _params)
	//{
	//	{
	//		rb = _world->createRigidBody(Transform(Vector3f(0.0f), QuaternionF(0.0f)));
	//		shape = GetShape(_shapeType, _common , _params);
	//		collider = rb->addCollider(shape, rb->getTransform());


	//	}
	//}

public:
	void Update();

public:
	void SetMassDensity(const float _massDensity);
	void SetBounciness(const float _bounciness);
	void SetFrictionCoefficient(const float _frictionCoefficient);

private:
	void LinkRBAndShape();
	void Material();

	//template<typename Params>
	//CollisionShape* GetShape(const ShapeType& _shapeType, PhysicsCommon& _common, Params _params...)
	//{
	//	switch (_shapeType)
	//	{
	//	case NONE:
	//		return shape = nullptr;
	//		break;
	//	case BOX:
	//		//return shape = nullptr;
	//		return shape = _common.createBoxShape(_params );
	//		break;
	//	case CAPSULE:
	//		//return shape = nullptr;
	//		return shape = _common.createCapsuleShape(_params , _params);
	//			break;
	//	case SPHERE:
	//		return shape = _common.createSphereShape(_params);
	//		break;
	//	case CONVEX:
	//		return shape = nullptr;
	//		
	//		//return shape = _common.createConvexMeshShape(_params);
	//		break;
	//	case MAX:
	//		return shape = nullptr;
	//		break;

	//	default:
	//		break;
	//	}
	//	return shape = nullptr;
	//}

};

// Create a rigid body in the world
// 
// Add the collider to the rigid body
//
// shape centered at the origin of the collider
//
//
