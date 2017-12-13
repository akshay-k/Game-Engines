#include "stdafx.h"
#include "RigidBody.h"
#include <limits>

bool Resembles(float x, float otherX, float tolerance) {
	return (std::abs(x - otherX) < std::abs(tolerance));
}

bool Resembles(double x, double otherX, double tolerance) {
	return (std::abs(x - otherX) < std::abs(tolerance));
}

RigidBody::RigidBody()
{
}

RigidBody::RigidBody(const Math3D::Vector4 & v3position, const Math3D::Vector4 & v3velocity, const float mass)
{
	mv3Position = v3position;
	mv3LinearVelocity = v3velocity;
	mReciprocalMass = 1 / mass;
}


RigidBody::~RigidBody()
{
}

bool RigidBody::operator==(const RigidBody & that) const
{
	bool samePosition = mv3Position.Resemblesv3(that.GetV3Position());
	Math3D::Matrix44 thisOrientation = mM33Orientation;
	Math3D::Matrix44 thatOrientation = that.GetOrientation();
	bool sameOrientation = thisOrientation.getVec4X().Resemblesv3(thatOrientation.getVec4X()) &&
		thisOrientation.getVec4Y().Resemblesv3(thatOrientation.getVec4Y()) &&
		thisOrientation.getVec4Z().Resemblesv3(thatOrientation.getVec4Z());
	bool sameRmass = Math3D::Resembles(mReciprocalMass, that.GetReciprocalMass(), 0.00001f);
	return samePosition && sameOrientation && sameRmass;
}

void RigidBody::SetMassAndInertiaTensorInfinite()
{
	mReciprocalMass = 0.0f;
	float infinity = std::numeric_limits<float>::infinity();
	Math3D::Vector4 row1(infinity, 0.0f, 0.0f);
	Math3D::Vector4 row2(0.0f, infinity, 0.0f);
	Math3D::Vector4 row3(0.0f, 0.0f, infinity);
	mM33InvInertiaTensor_BodyFrame = Math3D::Matrix44(row1, row2, row3);
}

void RigidBody::SetMassAndInertiaTensorSphericalShell(float mass, const float radius)
{
	mReciprocalMass = 1.0f / mass;
	float valueOfMI = (2.0f / 5)*mass*radius*radius;
	Math3D::Vector4 row1(valueOfMI, 0.0f,0.0f);
	Math3D::Vector4 row2(0.0f, valueOfMI, 0.0f);
	Math3D::Vector4 row3(0.0f, 0.0f, valueOfMI);
	Math3D::Matrix44 m33InertiaTensor(row1, row2, row3);
	mM33InvInertiaTensor_BodyFrame = m33InertiaTensor.Inverse();
}


void RigidBody::SetMassAndInertiaTensorSolidBox(float mass, const Math3D::Vector4 & v3dimensions)
{
	mReciprocalMass = 1.0f / mass;
	float w = v3dimensions.getX(); //width
	float h = v3dimensions.getY(); //height
	float d = v3dimensions.getZ(); //depth
	float massDividedBy12 = mass / 12;
	Math3D::Vector4 row1(massDividedBy12*(h*h + d*d),0.0f,0.0f);
	Math3D::Vector4 row2( 0.0f, massDividedBy12*(w*w + d*d), 0.0f);
	Math3D::Vector4 row3(0.0f, 0.0f, massDividedBy12*(w*w + h*h));
	Math3D::Matrix44 m33InertiaTensor(row1, row2, row3);
	mM33InvInertiaTensor_BodyFrame = m33InertiaTensor.Inverse();
}

void RigidBody::SetMassAndInertiaTensor_BodyFrame(float mass, const Math3D::Matrix44 & m33inertiaTensor)
{
	mReciprocalMass = 1.0f / mass;
	SetInverseInertiaTensor_BodyFrame(m33inertiaTensor.Inverse());
}

Math3D::Vector4 RigidBody::TorqueOfForceAt(const Math3D::Vector4 & v3force, const Math3D::Vector4 & v3position) const
{
	return v3position^v3force;
}

void RigidBody::ApplyImpulsiveTorque(const Math3D::Vector4 & v3impulsiveTorque)
{
	mv3AngularMomentum += v3impulsiveTorque;
	mv3AngularVelocity = GetInvInertiaTensor_WorldFrame() * GetAngularMomentum();
}

float RigidBody::KineticEnergy() const
{
	float KE = 0.5*(1.0f/mReciprocalMass)*(mv3LinearVelocity.Magnitude2v3() + mv3AngularVelocity.Magnitude2v3());
	return KE;
}

void RigidBody::Update(double virtualTime, float timeStep)
{
	// Update linear quantities.
	const Math3D::Vector4 v3momentumBefore = GetMomentum();
	mv3Momentum += mv3NetForces * timeStep;
	const Math3D::Vector4 v3velocityAvg = 0.5f * (v3momentumBefore + GetMomentum()) * mReciprocalMass;
	mv3Position += timeStep * v3velocityAvg;
	// Update angular quantities.
	const Math3D::Vector4 v3angMomBefore = GetAngularMomentum();
	mv3AngularMomentum += mv3NetTorque * timeStep;
	const Math3D::Vector4 v3angVelAverage = GetInvInertiaTensor_WorldFrame() * (0.5f * (GetAngularMomentum() + v3angMomBefore));
	const Math3D::Matrix44 m33rodriguesSkew = Math3D::Matrix44::CrossProductMatrix(v3angVelAverage);
	const Math3D::Matrix44 m33angVelOperator = GetOrientation() * m33rodriguesSkew;
	mM33Orientation = mM33Orientation + timeStep * m33angVelOperator;
	mM33Orientation.OrthonormalizeM33();
	// Update auxiliary values.
	mv3LinearVelocity = mReciprocalMass * GetMomentum();
	mv3AngularVelocity = GetInvInertiaTensor_WorldFrame() * GetAngularMomentum();
	// Zero out forces and torques.
	mv3NetForces = mv3NetTorque = Math3D::Vector4(0.0f, 0.0f, 0.0f);
}
