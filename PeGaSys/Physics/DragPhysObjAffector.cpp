#include "stdafx.h"
#include "DragPhysObjAffector.h"


DragPhysObjAffector::DragPhysObjAffector(float drag) : PhysicalObjectAffectorBase(sType), mDrag(drag) { }



DragPhysObjAffector::~DragPhysObjAffector()
{
}

void DragPhysObjAffector::operator()(PhysicalObject * physObj)
{
	RigidBody * rigidBody = physObj->GetRigidBody();
	const float speed = rigidBody->GetVelocity().Magnitude();
	const float dragForceMag = speed * speed * mDrag;
	const Math3D::Vector4 v3velocityDir = rigidBody->GetVelocity().GetDir();
	// Technically drag force depends on the density of medium (~1.2 kg/m^3 for air) and the cross-sectional area of the projectile,
	// but all of that can be incorporated into mDrag.
	const Math3D::Vector4 v3dragForce = -dragForceMag * v3velocityDir;
	rigidBody->ApplyBodyForce(v3dragForce);
}
