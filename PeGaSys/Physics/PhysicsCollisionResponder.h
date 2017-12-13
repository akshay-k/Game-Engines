#pragma once
#include "CollisionWorld.h"
#include "PhysicalObject.h"

class PhysicsCollisionResponder :
	public ICollisionResponder
{
public:
	PhysicsCollisionResponder();
	~PhysicsCollisionResponder();

	virtual bool operator()(const ContactInfoVector & contactInfoVector, double virtualTime, float timeStep);
};

