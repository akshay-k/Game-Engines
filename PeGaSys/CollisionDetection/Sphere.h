#pragma once
#include "Vector4.h"
class Sphere
{
public:
	Sphere();
	~Sphere();
	Sphere(const Math3D::Vector4 & v3Position, const float radius);
	const Math3D::Vector4 & GetV3Position() const;
	void SetPosition(const Math3D::Vector4 & v3Position);
	const float & GetRadius() const;
	void SetRadius(const float radius);
	float Distance(const Math3D::Vector4 & v3Point) const;
	
	float Distance(const Sphere & otherSphere) const;
private:
	Math3D::Vector4 mPositionRadius; // v3Position (x,y,z) and radius (w) of this sphere.
};

