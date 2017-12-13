#pragma once
#include "PhysicalObject.h"
#include "PhysicalObjectAffectorBase.h"
#include "RigidBody.h"
class DragPhysObjAffector :
	public PhysicalObjectAffectorBase
{

public:
	static const unsigned sType = 'dPOA';
	explicit DragPhysObjAffector(float drag);
	~DragPhysObjAffector();
	virtual void operator()(PhysicalObject * physObj);

	float mDrag;

};

