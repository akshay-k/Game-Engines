#pragma once
#include "ShapeBase.h"
class TerrainShape :
	public ShapeBase
{


public:
	const static ShapeType TerrainShape::sShapeType;
	TerrainShape(ShapeType shapeType);
	~TerrainShape();

	void SetHeightData(const Math3D::Vector4 * v3vertices, const Math3D::Vector4 & v2minPos, const Math3D::Vector4 & v2extents, size_t numX, size_t numY, size_t strideX, size_t strideY);
	bool GetSurfaceInfo(float & outHeightAboveTerrain, Math3D::Vector4 & outPlane, const Math3D::Vector4 & v3probePosition) const;
private:
	const Math3D::Vector4 * _v3vertices; // (non-owning) 2D array of vertices that define heightfield
	Math3D::Vector4 _v2minPos; // World coordinate of minimal corner
	Math3D::Vector4 _v2extents; // Size, in world units, of terrain region
	Math3D::Vector4 _v2deltaInv; // 1/dx and 1/dy where dx,dy are x,y spacing between points in grid.
	size_t _numX; // number of points along X direction
	size_t _numY; // number of points along Y direction
	size_t _strideX; // number of bytes between heights adjacent along X direction
	size_t _strideY; // number of bytes between heights adjacent along Y direction

	size_t GetOffset(size_t ix, size_t iy) const;
	const Math3D::Vector4 & Getv3Vertex(size_t ix, size_t iy) const;
	const Math3D::Vector4 & Getv3Vertex(size_t index) const;
};

