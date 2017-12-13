#include "stdafx.h"
#include "DriveForcePhysObjAffector.h"


DriveForcePhysObjAffector::DriveForcePhysObjAffector() : PhysicalObjectAffectorBase(sType),
mv3Force(Math3D::Vector4(0.0f, 0.0f, 0.0f)),
mv3ForcePosition(Math3D::Vector4(0.0f, 0.0f, 0.0f)) { }


DriveForcePhysObjAffector::~DriveForcePhysObjAffector()
{
}

void DriveForcePhysObjAffector::operator()(PhysicalObject * physObj)
{
	RigidBody * rigidBody = physObj->GetRigidBody();
	rigidBody->ApplyForceAt(mv3Force, mv3ForcePosition);
}

DriveForcePhysObjAffector * DriveForcePhysObjAffector::ReinterpretCastPtr(void * voidPtr)
{
	DriveForcePhysObjAffector * obj = ReinterpretCastPtrHelper<DriveForcePhysObjAffector>(voidPtr);
	return obj;
}
