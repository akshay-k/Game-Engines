#include "stdafx.h"
#include <limits>
#include "ConvexPolyhedronShape.h"

const ShapeType ConvexPolyhedronShape::sShapeType = CONVEX_POLYHEDRON_SHAPE;


void ConvexPolyhedronShape::SetAsBox(const Math3D::Vector4 & v3minCorner, const Math3D::Vector4 & v3maxCorner)
{
	AllocateVerticesOwned(8); // 8 corners of box.
	_v3verticesOwned[0] = Math3D::Vector4(v3minCorner.getX(), v3minCorner.getY(), v3minCorner.getZ());
	_v3verticesOwned[1] = Math3D::Vector4(v3maxCorner.getX(), v3minCorner.getY(), v3minCorner.getZ());
	_v3verticesOwned[2] = Math3D::Vector4(v3minCorner.getX(), v3maxCorner.getY(), v3minCorner.getZ());
	_v3verticesOwned[3] = Math3D::Vector4(v3maxCorner.getX(), v3maxCorner.getY(), v3minCorner.getZ());
	_v3verticesOwned[4] = Math3D::Vector4(v3minCorner.getX(), v3minCorner.getY(), v3maxCorner.getZ());
	_v3verticesOwned[5] = Math3D::Vector4(v3maxCorner.getX(), v3minCorner.getY(), v3maxCorner.getZ());
	_v3verticesOwned[6] = Math3D::Vector4(v3minCorner.getX(), v3maxCorner.getY(), v3maxCorner.getZ());
	_v3verticesOwned[7] = Math3D::Vector4(v3maxCorner.getX(), v3maxCorner.getY(), v3maxCorner.getZ());
	// It's possible that the farthest vertex is inside (not one of the corners of) the provided box.
	// In that case the initial estimate for bounding sphere lies inside the box. But the box is hereby
	// the collision shape, and the bounding sphere must contain the collision shape.
	// So update bounding sphere to contain box.
	const float maxDist2 = std::fmax(v3minCorner.Magnitude2v3(), v3maxCorner.Magnitude2v3());
	const float boundingSphereRadius = sqrtf(maxDist2);
	GetBoundingSphere().SetRadius(boundingSphereRadius);
	AssignPlanesForAxisAlignedBoundingBox();
}

void ConvexPolyhedronShape::AssignVertices(const Math3D::Vector4 * v3vertices, size_t numVertices, size_t strideInBytes)
{
	const unsigned char * vertBytes = reinterpret_cast< const unsigned char * >(v3vertices);
	AllocateVerticesOwned(numVertices);
	for (size_t iVert = 0; iVert < numVertices; ++iVert)
	{
		const  Math3D::Vector4 * vert = reinterpret_cast< const  Math3D::Vector4 * >(vertBytes + strideInBytes * iVert);
		_v3verticesOwned[iVert] = *vert;
	}
}

void ConvexPolyhedronShape::SetVertexData(const Math3D::Vector4 * vertices, size_t numVertices, size_t numBytesBetweenVertices)
{
	_v3vertices = vertices;
	_numVertices = numVertices;
	_stride = numBytesBetweenVertices;
}

void ConvexPolyhedronShape::GetWorldSpaceVertex(Math3D::Vector4 & v3worldVertex, size_t vertexIndex) const
{
	const Math3D::Vector4 * v3modelVert = & Getv3Vertex(vertexIndex);
	GetLocalToWorld().TransformNormalByUpper3x3Transpose(v3worldVertex, *v3modelVert);
	
}

const Math3D::Vector4 & ConvexPolyhedronShape::GetModelSpacePlane(size_t planeIndex) const
{
	return _planes[planeIndex];
}

void ConvexPolyhedronShape::GetWorldSpacePlane(Math3D::Vector4 & worldPlane, size_t planeIndex) const
{
	const Math3D::Vector4 & modelPlane = GetModelSpacePlane(planeIndex);
	worldPlane = GetLocalToWorld().TransformPlane(modelPlane);
}

float ConvexPolyhedronShape::ContactDistanceWorldPoint(const Math3D::Vector4 & v3worldSpaceQueryPoint, size_t & idxPlaneLeastPenetration) const
{
	float maxDist = -std::numeric_limits<float>::max();
	idxPlaneLeastPenetration = ~size_t(0);
	const size_t numPlanes = GetNumPlanes();
	for (size_t iPlane = 0; iPlane < numPlanes; ++iPlane)
	{ // For each plane in convex hull (using half-space representation)...
	  // Compute sphere-to-plane distance
		Math3D::Vector4 worldSpacePlane;
		GetWorldSpacePlane(worldSpacePlane, iPlane);
		const float sphereToPlaneDist = v3worldSpaceQueryPoint*worldSpacePlane + worldSpacePlane.getW(); // D = n*x + p where p is the distance of plane from origin.
		if (sphereToPlaneDist > maxDist)
		{ // Sphere is farther from this plane than from any other visited so far.
		  // Keep track of plane with largest positive distance (a.k.a. least negative distance, a.ka. shalowest penetration)
			maxDist = sphereToPlaneDist;
			idxPlaneLeastPenetration = iPlane;
		}
	}
	return maxDist;
}

float ConvexPolyhedronShape::ContactDistanceRelativePoint(const Math3D::Vector4 & v3modelSpaceQueryPoint, size_t & idxPlaneLeastPenetration) const
{
	float maxDist = -std::numeric_limits<float>::max();
	idxPlaneLeastPenetration = ~size_t(0); // Initialize to invalid value so caller can tell if contact was detected.
	const size_t numPlanes = GetNumPlanes();
	for (size_t iPlane = 0; iPlane < numPlanes; ++iPlane)
	{ // For each plane in convex hull (using half-space representation)...
	  // Compute sphere-to-plane distance
		const Math3D::Vector4 & modelSpacePlane = GetModelSpacePlane(iPlane);
		const float sphereToPlaneDist = v3modelSpaceQueryPoint*modelSpacePlane + modelSpacePlane.getW(); // D = n*x + p where p is the distance of plane from origin.
		if (sphereToPlaneDist > maxDist)
		{ // Sphere is farther from this plane than from any other visited so far.
		  // Keep track of plane with largest positive distance (a.k.a. least negative distance, a.ka. shalowest penetration)
			maxDist = sphereToPlaneDist;
			idxPlaneLeastPenetration = iPlane;
		}
	}
	return maxDist;
}

size_t ConvexPolyhedronShape::GetNumVertices() const
{
	return _numVertices;
}

void ConvexPolyhedronShape::AllocateVerticesOwned(size_t numVerticesOwned)
{
	_v3verticesOwned.reserve(numVerticesOwned);
}

void ConvexPolyhedronShape::AssignPlanesFromTriangles(unsigned short triangleIndices[], size_t numTriangles)
{
	AssignPlanesFromIndexBufferTriangles_Template<unsigned short>(triangleIndices, numTriangles);
}

void ConvexPolyhedronShape::AssignPlanesFromTriangles(unsigned int triangleIndices[], size_t numTriangles)
{
	AssignPlanesFromIndexBufferTriangles_Template<unsigned int>(triangleIndices, numTriangles);
}

void ConvexPolyhedronShape::AssignPlanesFromVertexBufferTriangles()
{
	const size_t numTriangles = _numVertices / 3;
	_planes.reserve(numTriangles);
	for (size_t iTri = 0; iTri < numTriangles; ++iTri)
	{ // For each triangle...
	  // Look up vertex positions.
		const Math3D::Vector4 & v3V0 = Getv3Vertex(iTri);
		const Math3D::Vector4 & v3V1 = Getv3Vertex(iTri + 1);
		const Math3D::Vector4 & v3V2 = Getv3Vertex(iTri + 2);
		// Initialize plane from triangle.
		Math3D::Vector4 planeFromTriangle = GetPlaneFromTriangleVertices(v3V0, v3V1, v3V2);
		float minNormalDiff, minDistDiff;
		FindMostSimilarPlane(planeFromTriangle, minNormalDiff, minDistDiff);
		const float sumDiff = minNormalDiff + minDistDiff;
		if (sumDiff > /* similarity tolerance */ 1.0e-4f)
		{ // Plane from triangle differs significantly from any other plane in shape.
		  // Store plane.
			_planes.push_back(planeFromTriangle);
		}
		else
		{ // Plane from triangle resembles some other plane in this shape.
		  //DEBUG_BREAK() ; // Let programmer know. TOOD: Tune tolerance and comment this out.
		}
	}
}

void ConvexPolyhedronShape::ReservePlanes(size_t numPlanes)
{
	_planes.reserve(numPlanes);
}

void ConvexPolyhedronShape::AppendPlane(const Math3D::Vector4 & plane)
{
	_planes.push_back(plane);
}

void ConvexPolyhedronShape::Clear()
{
	_numVertices = 0;
	_v3verticesOwned.clear();
	_planes.clear();
}

const Math3D::Vector4 & ConvexPolyhedronShape::Getv3Vertex(size_t index) const
{
	return _v3verticesOwned[index];
}

size_t ConvexPolyhedronShape::FindMostSimilarPlane(const Math3D::Vector4 & testPlane, float & minNormalDiff, float & minDistDiff) const
{
	minNormalDiff = std::numeric_limits<float>::max();
	minDistDiff = std::numeric_limits<float>::max();
	float minSumDiff = std::numeric_limits<float>::max();
	size_t minPlaneIdx = ~size_t(0); // Used in debugger only
	const size_t numPlanes = _planes.size();
	size_t iPlane;
	for (iPlane = 0; iPlane < numPlanes; ++iPlane)
	{
		const Math3D::Vector4 & plane = _planes[iPlane];
		const float normalDiff = 1.0f - GetNormal(plane) * GetNormal(testPlane);
		const float distDiff = fabsf(plane.getW() - testPlane.getW());
		const float sumDiff = normalDiff + distDiff;
		if (sumDiff < minSumDiff)
		{
			minNormalDiff = normalDiff;
			minDistDiff = distDiff;
			minSumDiff = sumDiff;
			minPlaneIdx = iPlane; (void)minPlaneIdx; // Used in debugger only
		}
	}
	return iPlane;
}

void ConvexPolyhedronShape::AssignPlanesForAxisAlignedBoundingBox()
{
	const Math3D::Vector4 & v3minCorner = _v3verticesOwned.front();
	const Math3D::Vector4 & v3maxCorner = _v3verticesOwned.back();
	_planes.reserve(6); // A box has 6 faces.
	Math3D::Vector4 plane;
	
	// Set -X plane passing through min
	// set normal
	plane.setX(-1.0f);
	plane.setY(0.0f);
	plane.setZ(0.0f);
	// set distance to plane
	plane.setW(v3minCorner.getX());
	_planes.push_back(plane);

	// Set -Y plane passing through min
	// set normal
	plane.setX(0.0f);
	plane.setY(-1.0f);
	plane.setZ(0.0f);
	// set distance to plane
	plane.setW(v3minCorner.getY());
	_planes.push_back(plane);

	// Set -Z plane passing through min
	// set normal
	plane.setX(0.0f);
	plane.setY(0.0f);
	plane.setZ(-1.0f);
	// set distance to plane
	plane.setW(v3minCorner.getZ());
	_planes.push_back(plane);

	// Set +X plane passing through max
	// set normal
	plane.setX(1.0f);
	plane.setY(0.0f);
	plane.setZ(0.0f);
	// set distance to plane
	plane.setW(-v3maxCorner.getX());
	_planes.push_back(plane);

	// Set +Y plane passing through max
	// set normal
	plane.setX(0.0f);
	plane.setY(1.0f);
	plane.setZ(0.0f);
	// set distance to plane
	plane.setW(-v3maxCorner.getY());
	_planes.push_back(plane);

	// Set +Z plane passing through max
	// set normal
	plane.setX(0.0f);
	plane.setY(0.0f);
	plane.setZ(1.0f);
	// set distance to plane
	plane.setW(-v3maxCorner.getZ());
	_planes.push_back(plane);
}

template <typename IndexType>
void AssignPlanesFromIndexBufferTriangles_Template(IndexType triangleIndices[], size_t numTriangles)
{
	_planes.reserve(numTriangles);
	for (size_t iTri = 0; iTri < numTriangles; ++iTri)
	{ // For each triangle...
		const size_t offset = iTri * 3;
		// Look up vertex positions for triangle via index buffer.
		const Math3D::Vector4 & v3V0 = GetVertex(triangleIndices[offset]);
		const Math3D::Vector4 & v3V1 = GetVertex(triangleIndices[offset + 1]);
		const Math3D::Vector4 & v3V2 = GetVertex(triangleIndices[offset + 2]);
		// Initialize plane from triangle.
		Math3D::Vector4 planeFromTriangle = GetPlaneFromTriangleVertices(v3V0, v3V1, v3V2);
		float minNormalDiff, minDistDiff;
		FindMostSimilarPlane(planeFromTriangle, minNormalDiff, minDistDiff);
		const float sumDiff = minNormalDiff + minDistDiff;
		if (sumDiff > /* similarity tolerance */ 1.0e-4f)
		{ // Plane from triangle differs significantly from any other plane in shape.
		  // Store plane.
			mPlanes.PushBack(planeFromTriangle);
		}
		else
		{ // Plane from triangle resembles some other plane in this shape.
		}
	}
}

ConvexPolyhedronShape::ConvexPolyhedronShape(ShapeType shapeType):ShapeBase(shapeType)
{
}


