#include "Object.h"


//Object::Object(PhysicsWorld* _world,   PhysicsCommon& _common , const ShapeType& _shapeType , ...)
//{
//	 rb = _world->createRigidBody(Transform(Vector3f(0.0f), QuaternionF(0.0f)));
//	 rb = GetShape(_shapeType, _common , ...);
//
//	//shape = _common.createBoxShape(Vector3f(10.0f));
//	//if(_shape->getType() == SphereShape::getType)
//	collider = rb->addCollider(shape, rb->getTransform());
//
//
//}

//RigidBody* Object::GetShape(const ShapeType& _shapeType,  PhysicsCommon& _common , ...)
//{
//
//}

void Object::Update()
{
//	collider->
}

void Object::LinkRBAndShape()
{
	//ConvexShape* _mesh;


	//_mesh->computeTransformedAABB().
	//shape->getCentroid() = rb->getTransform().getPosition();
}

void Object::Material()
{
	//mat->getBounciness();

	/*mat->setMassDensity();
	mat->setBounciness();
	mat->setFrictionCoefficient();*/

}


void Object::SetMassDensity(const float _massDensity)
{
	//mat->setMassDensity(_massDensity);
}

void Object::SetBounciness(const float _bounciness)
{
	//TODO  NORMALIZE _BOUNCINESS
	//mat->setBounciness(_bounciness);
}

void Object::SetFrictionCoefficient(const float _frictionCoefficient)
{
	// mat->setFrictionCoefficient(_frictionCoefficient);
}
