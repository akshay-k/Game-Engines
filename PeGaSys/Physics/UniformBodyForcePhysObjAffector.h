#pragma once
#include "PhysicalObject.h"
#include "PhysicalObjectAffectorBase.h"
#include "RigidBody.h"
class UniformBodyForcePhysObjAffector: public PhysicalObjectAffectorBase
{
public:
	static const unsigned sType = 'ubfP';
	explicit UniformBodyForcePhysObjAffector(const Math3D::Vector4 & v3force = Math3D::Vector4(0.0f, 0.0f, 0.0f));
	~UniformBodyForcePhysObjAffector();
	virtual void operator()(PhysicalObject * physObj);
	
	Math3D::Vector4 mv3Force;
};

