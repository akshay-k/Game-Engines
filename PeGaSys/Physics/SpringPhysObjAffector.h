#pragma once
#include "PhysicalObject.h"
#include "PhysicalObjectAffectorBase.h"
#include "RigidBody.h"

class SpringPhysObjAffector :
	public PhysicalObjectAffectorBase
{
public:
	static const unsigned sType = 'sPOA';
	SpringPhysObjAffector(float stiffness, const Math3D::Vector4 * v3anchor = nullptr);
	~SpringPhysObjAffector();
	virtual void operator()(PhysicalObject * physObj);
	float mStiffness;
	const Math3D::Vector4 * mv3Anchor;
};

