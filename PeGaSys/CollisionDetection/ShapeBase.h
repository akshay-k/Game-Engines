#pragma 

#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include "Matrix44.h"
#include "Sphere.h"

enum ShapeType {
	BASESHAPE,
	SPHERE_SHAPE,
	CONVEX_POLYHEDRON_SHAPE,
	TERRAIN_SHAPE,
};

class ShapeBase
{
public:
	static const ShapeType sBaseShapeType;
	explicit ShapeBase(ShapeType shapeType, bool isHole = false);
	ShapeBase(ShapeType shapeType, float boundingSphereRadius);
	virtual ~ShapeBase() {}
	void UpdateWorldSpace(const Math3D::Matrix44 & mat33Rotation, const Math3D::Vector4 & vec3Translation);
	bool IsHole() const;
	bool IsCollidable() const;
	void SetCollidable(bool collidable);
	Sphere GetBoundingSphere() const;
	float GetBoundingSphereDistance(ShapeBase shape) const;
	Math3D::Matrix44 GetLocalToWorld() const;
	ShapeType GetShapeType() const;
	void* GetClientData() const;
	void SetClientData(void* clientDataPtr);

	static Math3D::Vector4 GetPlaneFromTriangleVertices(Math3D::Vector4  v3Va, Math3D::Vector4  v3Vb, Math3D::Vector4  v3Vc);
	static Math3D::Vector4 GetNormal(Math3D::Vector4 plane);
	static float DistanceFromPlaneToPoint(Math3D::Vector4 plane, Math3D::Vector4 v3Position);

private:
	ShapeType mShapeType; /// Type identifier for this shape. Crude form of RTTI
	Sphere mBoundingSphere; /// (World-space) Sphere entirely containing object
	Math3D::Matrix44 mLocalToWorld; /// Local-to-world transform
	float mParity; /// Sign to apply to distances and normals. +1 for solid, -1 for hole
	void * mClientData; /// (non-owning) Data opaque to this class used during callbacks to identify object associated with this shape


};

#endif // !SHAPEBASE_H