#include "stdafx.h"
#include "PhysicsCollisionResponder.h"


PhysicsCollisionResponder::PhysicsCollisionResponder()
{
}


PhysicsCollisionResponder::~PhysicsCollisionResponder()
{
}

bool PhysicsCollisionResponder::operator()(const ContactInfoVector & contactInfoVector,
	double virtualTime, float timeStep)
{
	bool sApplyCollisionImpulses = true;
	bool sApplyRollingFriction = true;
	bool sSeparateOverlappingBodies = true;
	const size_t numContacts = contactInfoVector.size();
	for (size_t iContact = 0; iContact < numContacts; ++iContact)
	{
		const ContactInfo & contact = contactInfoVector[iContact];
		ShapeBase * shape1 = contact.mShape1;
		ShapeBase * shape2 = contact.mShape2;
		PhysicalObject * physObj1 = reinterpret_cast< PhysicalObject * >(shape1->GetClientData());
		PhysicalObject * physObj2 = reinterpret_cast< PhysicalObject * >(shape2->GetClientData());
		const float countScale = 1.0f / float(contact.mNumContactsForPair); // Reduce impact when pair has multiple contacts.
		if (sApplyCollisionImpulses) { // Compute and apply impulse
			RigidBody * body1 = physObj1->GetRigidBody();
			RigidBody * body2 = physObj2->GetRigidBody();
			// Remember pre-impulse kinetic energy.
			const float tKe0 = body1->KineticEnergy() + body2->KineticEnergy();
			Math3D::Vector4 v3tangentDir;
			float impact = 0.0f;
			{
				const Math3D::Vector4 v3relPos1 = contact.mv3Position - body1->GetV3Position();
				const Math3D::Vector4 v3relPos2 = contact.mv3Position - body2->GetV3Position();
				const Math3D::Vector4 v3velAtPt1 = body1->GetVelocityAtPoint(contact.mv3Position);
				const Math3D::Vector4 v3velAtPt2 = body2->GetVelocityAtPoint(contact.mv3Position);
				const Math3D::Vector4 v3velRel = v3velAtPt2 - v3velAtPt1; // relative velocities of contact point on 2 bodies
				const float sepSpeed = contact.mv3Normal * v3velRel; // speed at which objects are separating
																 // [Equivalent formula, to within numerical machine precision: ( contact.mNormal ^ velRel ) ^ contact.mNormal ;]
				v3tangentDir = v3velRel - (v3velRel * contact.mv3Normal) * contact.mv3Normal; // Component of relative velocity tangential to contact normal.
				v3tangentDir.Normalizev3();
				if (sepSpeed < 0.0f)
				{
					const float staticFallSpeed = 10.0f * 0.01f; // When separation speed is below this, treat collision as static / resting. TODO: Derive from gravity and time step.
					const float restitution = sepSpeed < -staticFallSpeed ? std::fmin(physObj1->GetFrictionProperties().mRestitution, physObj2->GetFrictionProperties().mRestitution) : 0.0f;
					const Math3D::Vector4 v3r1xN = (v3relPos1 ^ contact.mv3Normal);
					const Math3D::Vector4 v3r2xN = (v3relPos2 ^ contact.mv3Normal);
					const Math3D::Vector4 v3den3 = (body1->GetInvInertiaTensor_WorldFrame() * v3r1xN) ^ v3relPos1;
					const Math3D::Vector4 v3den4 = (body2->GetInvInertiaTensor_WorldFrame() * v3r2xN) ^ v3relPos2;
					const float den34 = (v3den3 + v3den4) * contact.mv3Normal;
					const float den = body1->GetReciprocalMass() + body2->GetReciprocalMass() + den34;
					const float bounceFactor = 1.0f + restitution;
					impact = countScale * bounceFactor * sepSpeed / den;
					// Compute normal component of impulse.
					Math3D::Vector4 impulse = impact * contact.mv3Normal;
					body1->ApplyImpulseAt(impulse, contact.mv3Position);
					body2->ApplyImpulseAt(-impulse, contact.mv3Position);
				}
			}
			if (sApplyRollingFriction)
			{ // Apply rolling friction
				body1->SetAngularMomentum(body1->GetAngularMomentum() * (1.0f - physObj1->GetFrictionProperties().mRollingFriction)); // rolling friction
				body2->SetAngularMomentum(body2->GetAngularMomentum() * (1.0f - physObj2->GetFrictionProperties().mRollingFriction)); // rolling friction
			}
			if (sSeparateOverlappingBodies)
			{
				physObj1->Separate(physObj2, contact);
			}
		}
	}
	return true; // Tell caller this callback moved objects so contact list is invalid.
}
