#pragma once
#include <vector>
#include "ShapeBase.h"
#include "RigidBody.h"
#include "PhysicalObjectAffectorBase.h"
#include "CollisionWorld.h"
//#include "Entity.h"
//#include "RTTI.h"
/** Friction properties of a physical object.
Technically, friction is a property of pairs of objects in contact, not of
individual objects. This is a simplification.
*/

void PhysicalObject_UpdateSystem(const std::vector< PhysicalObject * > & physicalObjects, double virtualTime, float timeStep, unsigned /* uFrame */);
void PhysicalObject_ComputeConservedQuantities(Math3D::Vector4 & v3totalLinearMomentum, Math3D::Vector4 & v3totalAngularMomentum, float & totalKineticEnergy, const std::vector< PhysicalObject * > & physicalObjects);

struct FrictionProperties
{
	FrictionProperties()
		: mSlidingFriction(0.0f)
		, mStaticFriction(0.0f)
		, mRollingFriction(0.0f)
		, mRestitution(1.0f)
	{}
	float mSlidingFriction;
	float mStaticFriction;
	float mRollingFriction;
	float mRestitution;
};

class PhysicalObject /*: public Entity*/
	//RTTI_INTERFACE_WITH_PARENT(Entity);
{

public:
	typedef IPhysicalObjectAffector* AffectorPtr;
	typedef std::vector< AffectorPtr > AffectorContainer;
	typedef AffectorContainer::iterator AffectorIterator;
	static const unsigned sType = 'PhOb';
	static const float sAmbientTemperature;
	PhysicalObject(RigidBody * rigidBody, ShapeBase * collisionShape);
	PhysicalObject(RigidBody * rigidBody, ShapeBase * collisionShape, const FrictionProperties & FrictionProperties);
		~PhysicalObject();
	void Clear();
	RigidBody * GetRigidBody() { return mRigidBody; }
	const RigidBody * GetRigidBody() const { return mRigidBody; }
	ShapeBase * GetCollisionShape() { return mCollisionShape; }
	const ShapeBase * GetCollisionShape() const { return mCollisionShape; }
	void SetCollisionShape(ShapeBase * collisionShape) { mCollisionShape = collisionShape; }
	FrictionProperties & GetFrictionProperties() { return mFrictionProperties; }
	const FrictionProperties & GetFrictionProperties() const { return mFrictionProperties; }
	void PushBackAffector(AffectorPtr affector) { mAffectors.push_back(affector); }
	const AffectorContainer & GetAffectors() const { return mAffectors; }
	AffectorPtr GetAffector(size_t index) { return mAffectors[index]; }
	void * GetClientData() const { return mClientData; }
	void SetClientData(void * clientData) { mClientData = clientData; }
	void Update(double virtualTime, float timeStep);
	void Separate(PhysicalObject * other, const ContactInfo & contact);
	const bool IsPhysicalObject() const { return sType == mType; }
protected:
	unsigned mType; /// Type information
	RigidBody * mRigidBody; /// (owning) Address of rigid body object associated with this physical object.
	ShapeBase * mCollisionShape; /// (non-owning) Address of shape used for collision detection. CollisionWorld owns.
	FrictionProperties mFrictionProperties; /// Properties used to resolve collisions with a tangential component
	void * mClientData; /// Opaque pointer to owner, used for callbacks.
	AffectorContainer mAffectors;
};


