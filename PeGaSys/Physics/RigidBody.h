#pragma once
#include "Vector4.h"
#include "Matrix44.h"
class RigidBody
{
public:
	RigidBody();
	RigidBody(const Math3D::Vector4 & v3position, const Math3D::Vector4 & v3velocity, const float mass);
	~RigidBody();
	bool operator==(const RigidBody & that) const;

	void SetPosition(const Math3D::Vector4 & v3pos) { mv3Position = v3pos; }
	const Math3D::Vector4 & GetV3Position() const { return mv3Position; }
	void Move(const Math3D::Vector4 v3distance) { mv3Position += v3distance; }
	void SetOrientation(const Math3D::Matrix44 & m33orientation) { mM33Orientation = m33orientation; }
	const Math3D::Matrix44 & GetOrientation() const { return mM33Orientation; }
	
	void SetPositionAndOrientation(const Math3D::Vector4 & v3pos, const Math3D::Matrix44 & m33orientation)
	{ 
		mv3Position = v3pos; 
		mM33Orientation = m33orientation; 
	}

	void SetMomentum(const Math3D::Vector4 & v3momentum)
	{ 
		mv3Momentum = v3momentum;
		mv3LinearVelocity = mReciprocalMass * mv3Momentum; 
	}

	const Math3D::Vector4 & GetMomentum() const { return mv3Momentum; }
	
	void SetAngularMomentum(const Math3D::Vector4 & v3angularMomentum)
	{
		mv3AngularMomentum = v3angularMomentum;
		mv3AngularVelocity = GetInvInertiaTensor_WorldFrame() * GetAngularMomentum();
	}

	const Math3D::Vector4 & GetAngularMomentum() const { 
		return mv3AngularMomentum; 
	}

	float GetReciprocalMass() const { return mReciprocalMass; }
	float GetMass() const { return 1.0f / mReciprocalMass; }
	void SetMassAndInertiaTensorInfinite();
	void SetMassAndInertiaTensorSphericalShell(float mass, const float radius);
	/*
		v3dimensions in order width, height, depth
	*/
	void SetMassAndInertiaTensorSolidBox(float mass, const Math3D::Vector4 & v3dimensions);
	void SetMassAndInertiaTensor_BodyFrame(float mass, const Math3D::Matrix44 & m33inertiaTensor);
	void SetInverseInertiaTensor_BodyFrame(const Math3D::Matrix44 & m33inverseInertiaTensorBodyFrame)
	{ 
		mM33InvInertiaTensor_BodyFrame = m33inverseInertiaTensorBodyFrame;
	}

	Math3D::Matrix44 GetInertiaTensorInv_BodyFrame() const { return mM33InvInertiaTensor_BodyFrame; }
	void GetInvInertiaTensor_WorldFrame(Math3D::Matrix44 & m33invInertiaTensorWorldFrame) const
	{

		m33invInertiaTensorWorldFrame = (mM33Orientation*mM33InvInertiaTensor_BodyFrame.GetTranspose()) * mM33Orientation;
	}
	Math3D::Matrix44 GetInvInertiaTensor_WorldFrame() const
	{
		Math3D::Matrix44 m33invInertiaTensorWorldFrame; GetInvInertiaTensor_WorldFrame(m33invInertiaTensorWorldFrame); return m33invInertiaTensorWorldFrame;
	}
	void ApplyBodyForce(const Math3D::Vector4 & v3force) { mv3NetForces += v3force; }
	void ApplyTorque(const Math3D::Vector4 & v3torque) { mv3NetTorque += v3torque; }
	Math3D::Vector4 TorqueOfForceAt(const Math3D::Vector4 & v3force, const Math3D::Vector4 & v3position) const;
	void ApplyForceAt(const Math3D::Vector4 & v3force, const Math3D::Vector4 & v3position) { ApplyBodyForce(v3force); ApplyTorque(TorqueOfForceAt(v3force, v3position)); }
	void ApplyImpulse(const Math3D::Vector4 & v3impulse) { mv3Momentum += v3impulse; mv3LinearVelocity = mReciprocalMass * GetMomentum(); }
	void ApplyImpulsiveTorque(const Math3D::Vector4 & v3impulsiveTorque);
	void ApplyImpulseAt(const Math3D::Vector4 & v3impulse, const Math3D::Vector4 & v3position) { ApplyImpulse(v3impulse); ApplyImpulsiveTorque(TorqueOfForceAt(v3impulse, v3position)); }
	void SetVelocity(const Math3D::Vector4 & v3velocity) { mv3LinearVelocity = v3velocity; mv3Momentum = v3velocity * GetMass(); }
	const Math3D::Vector4 & GetVelocity() const { return mv3LinearVelocity; }
	const Math3D::Vector4 GetVelocityAtPoint(const Math3D::Vector4 & v3point) const { const Math3D::Vector4 v3rotVel = mv3AngularVelocity ^ (v3point - mv3Position); const Math3D::Vector4 v3vel = mv3LinearVelocity + v3rotVel; return v3vel; }
	void SetAngularVelocity(const Math3D::Vector4 & v3angularVelocity) { mv3AngularVelocity = v3angularVelocity; mv3AngularMomentum = GetInertiaTensor_WorldFrame().TransformNormal(v3angularVelocity); }
	const Math3D::Vector4 & GetAngularVelocity() const { return mv3AngularVelocity; }
	float KineticEnergy() const;
	void Update(double virtualTime, float timeStep);
protected:
	Math3D::Vector4 mv3Position; /// Position in world-space of center-of-mass.
	Math3D::Matrix44 mM33Orientation; /// Orientation in world-space. Transforms directional vector from body-frame to world-frame.
	Math3D::Vector4 mv3Momentum; /// Linear momentum in world units and in world frame.
	Math3D::Vector4 mv3AngularMomentum; /// Angular momentum in world units and in world frame.
	float mReciprocalMass; /// One over mass. Converts momentum to linear velocity.
	Math3D::Matrix44 mM33InvInertiaTensor_BodyFrame; /// Inverse of inertia tensor IN BODY FRAME. Converts angular momentum to angular velocity.
	Math3D::Vector4 mv3NetForces; /// Net forces to apply during Update. Accumulator. In world units and world frame.
	Math3D::Vector4 mv3NetTorque; /// Net torque to apply during Update. Accumulator. In world units and world frame.
	Math3D::Vector4 mv3LinearVelocity; /// Linear velocity in world units and world frame, auxiliary variable subordinate to momentum.
	Math3D::Vector4 mv3AngularVelocity; /// Angular velocity in world units and world frame, auxiliary variable subordinate to angular momentum.
private:
	Math3D::Matrix44 GetInertiaTensor_BodyFrame() const { return mM33InvInertiaTensor_BodyFrame.Inverse(); }
	void GetInertiaTensor_WorldFrame(Math3D::Matrix44 & m33invInertiaTensorWorldFrame) const
	{
		m33invInertiaTensorWorldFrame = (mM33Orientation*GetInertiaTensor_BodyFrame().GetTranspose()) * mM33Orientation;
	}
	Math3D::Matrix44 GetInertiaTensor_WorldFrame() const
	{
		Math3D::Matrix44 m33inertiaTensorWorldFrame; GetInertiaTensor_WorldFrame(m33inertiaTensorWorldFrame); return m33inertiaTensorWorldFrame;
	}

};

