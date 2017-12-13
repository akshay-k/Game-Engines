#include "stdafx.h"
#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(size_t numCollisionResponders)
{
	mCollisionWorld.ReserveCollisionResponders(numCollisionResponders);
	mCollisionWorld.AppendCollisionResponder(&mCollisionResponder);
}

PhysicsWorld::~PhysicsWorld()
{
	Clear();
}

PhysicalObject * PhysicsWorld::NewPhysicalObject(ShapeType collisionShapeType)
{
	{
		RigidBody * rigidBody = new RigidBody; // TODO: Support composite objects, articulated objects, deformable bodies
		ShapeBase * shape = mCollisionWorld.AddNewShape(collisionShapeType);
		PhysicalObject * physObj = new PhysicalObject(rigidBody, shape);
		AddPhysicalObject(physObj);
		return physObj;
	}
}

void PhysicsWorld::UpdateBodies(double virtualTime, float timeStep)
{
	static int numPartialSteps = 4;
	const float partialTimeStep = timeStep / float(numPartialSteps);
	for (int i = 0; i < numPartialSteps; ++i)
	{
		PhysicalObject_UpdateSystem(mPhysicalObjects, virtualTime, partialTimeStep, 0);
		// Detect and respond to collisions
		int numCollisions = mCollisionWorld.CollideShapes(virtualTime, partialTimeStep);
		(void)numCollisions;
	}
}

void PhysicsWorld::Clear()
{
	for (unsigned idxPhysObj = 0; idxPhysObj < mPhysicalObjects.size(); ++idxPhysObj)
	{ // For each body in the simulation...
		PhysicalObject * physObj = mPhysicalObjects[idxPhysObj];
		delete physObj;
		physObj = nullptr;
	}
	mPhysicalObjects.clear();
}

void PhysicsWorld::AddPhysicalObject(PhysicalObject * physObj)
{
	mPhysicalObjects.push_back(physObj);
}
