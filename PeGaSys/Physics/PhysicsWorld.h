#pragma once
#include "CollisionWorld.h"
#include "PhysicalObject.h"
#include "PhysicsCollisionResponder.h"

class PhysicsWorld
{
public:
	typedef std::vector< PhysicalObject * > PhysicalObjectContainer;
	typedef PhysicalObjectContainer::iterator PhysicalObjectIterator;
	explicit PhysicsWorld(size_t numCollisionResponders);
	~PhysicsWorld();
	PhysicalObject * NewPhysicalObject(ShapeType collisionShapeType);
	void UpdateBodies(double virtualTime, float timeStep);
	CollisionWorld & GetCollisionWorld()
	{
		return mCollisionWorld;
	}
	PhysicalObjectContainer & GetPhysicalObjects()
	{
		return mPhysicalObjects;
	}
private:
	void Clear();
	void AddPhysicalObject(PhysicalObject * physObj);
	CollisionWorld mCollisionWorld; /// Collision detection subsystem, which also contains collidable shapes
	PhysicsCollisionResponder mCollisionResponder; /// Callback to handle a batch of collisions
	PhysicalObjectContainer mPhysicalObjects; /// Physical objects that belong to this world
};

