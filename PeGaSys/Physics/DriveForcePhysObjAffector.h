#pragma once
#include "PhysicalObject.h"
#include "PhysicalObjectAffectorBase.h"
#include "RigidBody.h"

class DriveForcePhysObjAffector :
	public PhysicalObjectAffectorBase
{

public:
	static const unsigned sType = 'dfPO';
	explicit DriveForcePhysObjAffector();
	~DriveForcePhysObjAffector();
	virtual void operator()(PhysicalObject * physObj);
	static DriveForcePhysObjAffector * ReinterpretCastPtr(void * voidPtr);

	Math3D::Vector4 mv3Force;
	Math3D::Vector4 mv3ForcePosition;
};

