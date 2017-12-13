#include "ShapeBase.h"

const ShapeType ShapeBase::sBaseShapeType = BASESHAPE;

ShapeBase::ShapeBase(ShapeType shapeType, bool isHole) : mShapeType(shapeType), mBoundingSphere(), mLocalToWorld(Math3D::Matrix44()), mParity(isHole ? -1.0f : 1.0f)
, mClientData(nullptr) { }

ShapeBase::ShapeBase(ShapeType shapeType, float boundingSphereRadius) : mShapeType(shapeType), mBoundingSphere(Sphere(Math3D::Vector4(0.0f, 0.0f, 0.0f),boundingSphereRadius)), mLocalToWorld(Math3D::Matrix44()), mParity(1.0f), mClientData(nullptr) { }

void ShapeBase::UpdateWorldSpace(const Math3D::Matrix44 & mat33Rotation, const Math3D::Vector4 & vec3Translation)
{
	mLocalToWorld.SetRotation(mat33Rotation);
	mLocalToWorld.SetTranslation(vec3Translation);
	GetBoundingSphere().SetPosition(vec3Translation);
}

bool ShapeBase::IsHole() const
{
	return mParity < 0.0f;
}

bool ShapeBase::IsCollidable() const
 { return GetBoundingSphere().GetRadius() > 0.0f; }

void ShapeBase::SetCollidable(bool collidable)
{
	// To avoid wasting space on storing a separate bool, reuse bounding sphere radius sign bit.
	float & boundingSphereRadius = const_cast< float & >(GetBoundingSphere().GetRadius());
	boundingSphereRadius = (collidable ? 1.0f : -1.0f) * (boundingSphereRadius);
}

Sphere ShapeBase::GetBoundingSphere() const
{
	return mBoundingSphere;
}

float ShapeBase::GetBoundingSphereDistance(ShapeBase shape) const
{
	Sphere thisSphere = GetBoundingSphere();
	Sphere thatSphere = shape.GetBoundingSphere();
	float distanceBetweenCentres = (thisSphere.GetV3Position() - thatSphere.GetV3Position()).Magnitudev3();
	float distanceBetweenSpheres = distanceBetweenCentres - thisSphere.GetRadius() -thatSphere.GetRadius();
	return distanceBetweenSpheres;
}

Math3D::Matrix44 ShapeBase::GetLocalToWorld() const
{
	return mLocalToWorld;
}

ShapeType ShapeBase::GetShapeType() const
{
	return mShapeType;
}

void * ShapeBase::GetClientData() const
{
	return mClientData;
}

void ShapeBase::SetClientData(void * clientDataPtr)
{
	mClientData = clientDataPtr;
}

Math3D::Vector4 ShapeBase::GetPlaneFromTriangleVertices(Math3D::Vector4 v3Va, Math3D::Vector4 v3Vb, Math3D::Vector4 v3Vc)
{
	Math3D::Vector4 v3Vab = v3Vb - v3Va;
	Math3D::Vector4 v3Vac = v3Vc - v3Va;
	Math3D::Vector4 v3NormalVectorOfPlane = v3Vab^v3Vac;
	float coefficientD = -(v3Va*v3NormalVectorOfPlane);
	float magnitudeOfNormal = v3NormalVectorOfPlane.Magnitudev3();
	Math3D::Vector4 planeEquation = Math3D::Vector4(v3NormalVectorOfPlane.getX(), v3NormalVectorOfPlane.getY(), v3NormalVectorOfPlane.getZ(), coefficientD);
	Math3D::Vector4 hessianFormPlane = planeEquation / magnitudeOfNormal;
	return hessianFormPlane;
}

Math3D::Vector4 ShapeBase::GetNormal(Math3D::Vector4 plane)
{
	return Math3D::Vector4(plane.getX(), plane.getY(), plane.getZ());
}

float ShapeBase::DistanceFromPlaneToPoint(Math3D::Vector4 plane, Math3D::Vector4 v3Position)
{
	float distance = plane * v3Position + plane.getW();
	return distance;
}

