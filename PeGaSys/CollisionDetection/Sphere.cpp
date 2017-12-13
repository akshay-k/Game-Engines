
#include "Sphere.h"

Sphere::Sphere(): mPositionRadius(Math3D::Vector4(0.0f,0.0f,0.0f,-1.0f)) {}
Sphere::~Sphere(){}

Sphere::Sphere(const Math3D::Vector4 & v3Position, const float radius):mPositionRadius(v3Position.getX(), v3Position.getY(), v3Position.getZ(), radius){}

const Math3D::Vector4 & Sphere::GetV3Position() const
{
	Math3D::Vector4 v3Pos(mPositionRadius.getX(), mPositionRadius.getY(), mPositionRadius.getZ());
	return v3Pos;
}

void Sphere::SetPosition(const Math3D::Vector4 & v3Position)
{
	mPositionRadius.setX(v3Position.getX());
	mPositionRadius.setY(v3Position.getY());
	mPositionRadius.setZ(v3Position.getZ());
}

const float & Sphere::GetRadius() const
{
	return mPositionRadius.getW(); // local variable??
}

void Sphere::SetRadius(const float radius)
{
	mPositionRadius.setW(radius);
}

float Sphere::Distance(const Math3D::Vector4 & v3Point) const
{
	const Math3D::Vector4 v3Separation = GetV3Position() - v3Point;
	const float distanceFromCenter = v3Separation.Magnitudev3();
	const float distance = distanceFromCenter - GetRadius();
	return distance;
}

float Sphere::Distance(const Sphere & otherSphere) const
{
	const Math3D::Vector4 v3Separation = GetV3Position() - otherSphere.GetV3Position();
	const float distanceBetweenCenters = v3Separation.Magnitudev3();
	const float distance = distanceBetweenCenters - GetRadius() - otherSphere.GetRadius();
	return distance;
}
