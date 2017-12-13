#include "stdafx.h"
#include "PhysicalObject.h"

//RTTI_DEFINITIONS(PhysicalObject);

PhysicalObject::PhysicalObject(RigidBody * rigidBody, ShapeBase * collisionShape)
	:mType(sType), mRigidBody(rigidBody), mCollisionShape(collisionShape), mClientData(nullptr) {
	mCollisionShape->SetClientData(this); 
}

PhysicalObject::PhysicalObject(RigidBody * rigidBody, ShapeBase * collisionShape, const FrictionProperties & FrictionProperties)
	: mType(sType), mRigidBody(rigidBody), mCollisionShape(collisionShape), mClientData(nullptr), mFrictionProperties(FrictionProperties) {
	mCollisionShape->SetClientData(this);
}


PhysicalObject::~PhysicalObject()
{
	Clear();
}

void PhysicalObject::Clear()
{
	delete mRigidBody;
	mRigidBody = nullptr;
	if (mCollisionShape) {
		//mCollisionShape->Clear(); ///ask about this
		// Do NOT delete mCollisionShape ; CollisionWorld owns it.
		mCollisionShape = nullptr;
	}
	const size_t numAffectors = GetAffectors().size();
	for (size_t iAffector = 0; iAffector < numAffectors; ++iAffector) { // For each affector on this object...
		delete mAffectors[iAffector];
		mAffectors[iAffector] = nullptr;
	}
	mAffectors.clear();
}

void PhysicalObject::Update(double virtualTime, float timeStep)
{/// Apply forces and torques, then update the rigid body of this object.
	const size_t numAffectors = GetAffectors().size();
	for (size_t iAffector = 0; iAffector < numAffectors; ++iAffector)
	{ // For each affector on this object...
		mAffectors[iAffector]->operator()(this);
	}
	GetRigidBody()->Update(virtualTime, timeStep);
	// Update collision shape world-space info.
	GetCollisionShape()->UpdateWorldSpace(GetRigidBody()->GetOrientation(), GetRigidBody()->GetV3Position());
}

void PhysicalObject::Separate(PhysicalObject * other, const ContactInfo & contact)
{ // Separate two colliding physical object according to the given contact info.
	RigidBody * body1 = GetRigidBody();
	RigidBody * body2 = other->GetRigidBody();
	float dist1;
	float dist2;
	if (body1->GetReciprocalMass() == 0.0f) { // body1 has infinite mass so does not move.
		dist1 = 0.0f;
		dist2 = body2->GetReciprocalMass() > 0.0f ? contact.mPenetrationDepth : 0.0f;
	}
	else if (body2->GetReciprocalMass() == 0.0f) { // body2 has infinite mass so does not move.
		dist1 = contact.mPenetrationDepth;
		dist2 = 0.0f;
	}
	else { // Both bodies have finite mass so both move.
		const float massSum = body1->GetMass() + body2->GetMass();
		dist1 = contact.mPenetrationDepth * body1->GetMass() / massSum;
		dist2 = contact.mPenetrationDepth - dist1;
	}
	const Math3D::Vector4 v3move1 = -contact.mv3Normal * dist1;
	const Math3D::Vector4 v3move2 = contact.mv3Normal * dist2;
	body1->Move(v3move1);
	body2->Move(v3move2);
}

void PhysicalObject_UpdateSystem(const std::vector< PhysicalObject * > & physicalObjects, double virtualTime, float timeStep, unsigned /* uFrame */)
{
	const size_t numPhysObjs = physicalObjects.size();
	for (unsigned idxPhysObj = 0; idxPhysObj < numPhysObjs; ++idxPhysObj) { // For each body in the simulation...
		PhysicalObject * physObj = physicalObjects[idxPhysObj];
		physObj->Update(virtualTime, timeStep);
	}
}

void PhysicalObject_ComputeConservedQuantities(Math3D::Vector4 & v3totalLinearMomentum, Math3D::Vector4 & v3totalAngularMomentum, float & totalKineticEnergy, const std::vector< PhysicalObject * > & physicalObjects)
{
	v3totalLinearMomentum = Math3D::Vector4(0.0f, 0.0f, 0.0f);
	v3totalAngularMomentum = Math3D::Vector4(0.0f, 0.0f, 0.0f);
	totalKineticEnergy = 0.0f;
	const size_t numPhysObjs = physicalObjects.size();
	for (unsigned idxPhysObj = 0; idxPhysObj < numPhysObjs; ++idxPhysObj)
	{ // For each body in the simulation...
		const RigidBody & rBody = *physicalObjects[idxPhysObj]->GetRigidBody();
		// Update body physical state
		v3totalLinearMomentum += rBody.GetMomentum();
		v3totalAngularMomentum += rBody.GetAngularMomentum();
		totalKineticEnergy += rBody.KineticEnergy();
	}
}

