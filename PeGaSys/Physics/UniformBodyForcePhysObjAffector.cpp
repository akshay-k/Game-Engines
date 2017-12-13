#include "stdafx.h"
#include "UniformBodyForcePhysObjAffector.h"


UniformBodyForcePhysObjAffector::UniformBodyForcePhysObjAffector(const Math3D::Vector4 & v3force) : PhysicalObjectAffectorBase(sType), mv3Force(v3force) { }


UniformBodyForcePhysObjAffector::~UniformBodyForcePhysObjAffector()
{
}

void UniformBodyForcePhysObjAffector::operator()(PhysicalObject * physObj)
{
	RigidBody * rigidBody = physObj->GetRigidBody();
	rigidBody->ApplyBodyForce(mv3Force);
}
