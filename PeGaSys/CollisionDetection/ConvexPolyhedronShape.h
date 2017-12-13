#pragma once
#include <iostream>
#include <vector>
#include "ShapeBase.h"
class ConvexPolyhedronShape : public ShapeBase
{
public:
	const static ShapeType ConvexPolyhedronShape::sShapeType;
	ConvexPolyhedronShape(ShapeType shapeType);
	virtual ~ConvexPolyhedronShape() {}
	void SetAsBox(const Math3D::Vector4 & v3minCorner, const Math3D::Vector4 & v3maxCorner);
	void AssignVertices(const Math3D::Vector4 * v3vertices, size_t numVertices, size_t strideInBytes);
	void SetVertexData(const Math3D::Vector4 * vertices, size_t numVertices, size_t numBytesBetweenVertices);
	void GetWorldSpaceVertex(Math3D::Vector4 & v3worldVertex, size_t vertexIndex) const;
	const Math3D::Vector4 & GetModelSpacePlane(size_t planeIndex) const;
	void GetWorldSpacePlane(Math3D::Vector4 & worldPlane, size_t planeIndex) const;
	float ContactDistanceWorldPoint(const Math3D::Vector4 & v3worldSpaceQueryPoint, size_t & idxPlaneLeastPenetration) const;
	float ContactDistanceRelativePoint(const Math3D::Vector4 & v3modelSpaceQueryPoint, size_t & idxPlaneLeastPenetration) const;
	size_t GetNumVertices() const;
	void AllocateVerticesOwned(size_t numVerticesOwned);
    size_t GetNumPlanes() const { return _planes.size(); }
	void AssignPlanesFromTriangles(unsigned short triangleIndices[], size_t numTriangles);
	void AssignPlanesFromTriangles(unsigned int triangleIndices[], size_t numTriangles);
	void AssignPlanesFromVertexBufferTriangles();
	void ReservePlanes(size_t numPlanes);
	void AppendPlane(const Math3D::Vector4 & plane);
	void Clear();
private:
	const Math3D::Vector4 & Getv3Vertex(size_t index) const;
	size_t FindMostSimilarPlane(const Math3D::Vector4 & testPlane, float & minNormalDiff, float & minDistDiff) const;
	void AssignPlanesForAxisAlignedBoundingBox();
	template <typename IndexType> 
	void AssignPlanesFromIndexBufferTriangles_Template(IndexType triangleIndices[], size_t numTriangles);



	// Members

	typedef std::vector<Math3D::Vector4> PlaneContainer; 
	// plane is represented as a Vector4. xyz components are the plane normal,
	// which this routine assumes is normalized.
	// w component is the distance of the plane from the origin, along
	// the direction of the normal.This is Hessian normal form.
	const Math3D::Vector4 * _v3vertices; /// (non-owning) array of vertices of polyhedron
	size_t _numVertices; /// number of vertices in polyhedron
	size_t _stride; /// number of bytes between vertices
	std::vector<Math3D::Vector4> _v3verticesOwned; /// Dynamic array of vertices owned by this object. Can be empty.
	PlaneContainer _planes; /// Planes defining half-space representation of convex polytope
};

template<typename IndexType>
inline void ConvexPolyhedronShape::AssignPlanesFromIndexBufferTriangles_Template(IndexType triangleIndices[], size_t numTriangles)
{
}
