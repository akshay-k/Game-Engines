#include "stdafx.h"
#include "SpringPhysObjAffector.h"


SpringPhysObjAffector::SpringPhysObjAffector(float stiffness, const Math3D::Vector4 * v3anchor) : PhysicalObjectAffectorBase(sType), mStiffness(stiffness), mv3Anchor(v3anchor) { }



SpringPhysObjAffector::~SpringPhysObjAffector()
{
}

void SpringPhysObjAffector::operator()(PhysicalObject * physObj)
{
	RigidBody * rigidBody = physObj->GetRigidBody();
	const Math3D::Vector4 v3displacement = rigidBody->GetV3Position() - *mv3Anchor;
	const float dist = v3displacement.Magnitudev3();
	const float springForceMag = dist * mStiffness;
	const Math3D::Vector4 v3displacementDir = v3displacement.GetDir();
	const Math3D::Vector4 v3springForce = -springForceMag * v3displacementDir;
	rigidBody->ApplyBodyForce(v3springForce);
}
