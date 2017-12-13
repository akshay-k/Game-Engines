#include "stdafx.h"
#include "TerrainShape.h"
#include <math.h>
#include <limits>


const ShapeType TerrainShape::sShapeType = TERRAIN_SHAPE;

TerrainShape::TerrainShape(ShapeType shapeType) : ShapeBase(shapeType)
{
}


TerrainShape::~TerrainShape()
{
}

void TerrainShape::SetHeightData(const Math3D::Vector4 * v3vertices, const Math3D::Vector4 & v2minPos, const Math3D::Vector4 & v2extents, size_t numX, size_t numY, size_t strideX, size_t strideY)
{
	_v3vertices = v3vertices;
	_v2minPos = v2minPos;
	_v2extents = v2extents;
	_numX = numX;
	_numY = numY;
	_v2deltaInv.setX(float(double(_numX - 1) / _v2extents.getX()));
	_v2deltaInv.setY(float(double(_numY - 1) / _v2extents.getY()));
	_strideX = strideX;
	_strideY = strideY; // always numX*_strideX (pass it that way)
}

bool TerrainShape::GetSurfaceInfo(float & outHeightAboveTerrain, Math3D::Vector4 & outPlane, const Math3D::Vector4 & v3probePosition) const
{
	const Math3D::Vector4 v2halfExtents = _v2extents * 0.5f;
	const Math3D::Vector4 v2shiftedPos = Math3D::Vector4(v3probePosition.getX(), v3probePosition.getY(), 0.0f) + v2halfExtents;
	const unsigned int ix = (int)floor(v2shiftedPos.getX() * _v2deltaInv.getX());
	const unsigned int iy = (int)floor(v2shiftedPos.getY() * _v2deltaInv.getY());
	if ((ix < 0) || (ix >= (_numX - 1)) // Note: Check for ix,iy < 0 is redundant since they are unsigned, but leaving it here to indicate intention.
		|| (iy < 0) || (iy >= (_numY - 1)))
	{
		outHeightAboveTerrain = std::numeric_limits<float>::max();
		return false;
	}
	// Find indices of terrain grid cell nearest given position (vPos).
	// Here "i" refers to x coordinate and "j" refers to y coordinate.
	// Note that topology here must match that in Render::MakeHeightField, otherwise collision detection will not match rendering.
	/* di dj di dj
	|/ |/ D 00,+1 E +1,+1
	-D--E- A 00,00 B +1,00
	| /| offset = di + nx * dj
	|/ |/ indexPrime = index + offset
	-A--B-
	*/
	// Use plane of nearest triangle
	const Math3D::Vector4 & v3vB = Getv3Vertex(ix + 1, iy);
	const Math3D::Vector4 & v3vD = Getv3Vertex(ix, iy + 1);
	// Compute horizontal distance from given point to D and B.
	const float ptToBx = v3probePosition.getX() - v3vB.getX();
	const float ptToBy = v3probePosition.getY() - v3vB.getY();
	const float dist2ToB = pow(ptToBx, 2) + pow(ptToBy, 2);
	const float ptToDx = v3probePosition.getX() - v3vD.getX();
	const float ptToDy = v3probePosition.getY() - v3vD.getY();
	const float dist2ToD = pow(ptToDx, 2) + pow(ptToDy, 2);
	const Math3D::Vector4 & v3vE = Getv3Vertex(ix + 1, iy + 1);
	const Math3D::Vector4 & v3v0 = Getv3Vertex(ix, iy);
	const Math3D::Vector4 * v3v1;
	const Math3D::Vector4 * v3v2;
	// Use triangle associated with closer point.
	if (dist2ToB < dist2ToD)
	{ // point is closer to B so use triangle ABE
		v3v1 = &v3vB;
		v3v2 = &v3vE;
	}
	else
	{ // point is closer to D so use triangle AED
		v3v1 = &v3vE;
		v3v2 = &v3vD;
	}
	outPlane = GetPlaneFromTriangleVertices(v3v0, *v3v1, *v3v2);
	outHeightAboveTerrain = DistanceFromPlaneToPoint(outPlane, v3probePosition);
	return true;
}

size_t TerrainShape::GetOffset(size_t ix, size_t iy) const
{
	size_t offset = _strideX * ix + _strideY * iy;
	return offset;
}

const Math3D::Vector4 & TerrainShape::Getv3Vertex(size_t ix, size_t iy) const
{
	size_t offset = GetOffset(ix, iy);
	const unsigned char * bytes = reinterpret_cast< const unsigned char * >(_v3vertices);
	const Math3D::Vector4 * v3vert = reinterpret_cast< const Math3D::Vector4 * >(bytes + offset);
	return *v3vert;
}

const Math3D::Vector4 & TerrainShape::Getv3Vertex(size_t index) const
{
	size_t offset = _strideX * index;
	const unsigned char * bytes = reinterpret_cast< const unsigned char * >(_v3vertices);
	const Math3D::Vector4 * v3vert = reinterpret_cast< const Math3D::Vector4 * >(bytes + offset);
	return *v3vert;
}
