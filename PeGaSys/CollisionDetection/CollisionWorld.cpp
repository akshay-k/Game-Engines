#include "stdafx.h"
#include "CollisionWorld.h"
#include "SphereShape.h"
#include "TerrainShape.h"
#include <limits>

CollisionWorld::CollisionWorld()
{
}


CollisionWorld::~CollisionWorld()
{
}

ShapeBase * CollisionWorld::AddNewShape(ShapeType shapeType)
{
	ShapeBase * shape = NewShape(shapeType);
	AddShape(shape);
	return shape;
}

ShapeBase * CollisionWorld::NewShape(ShapeType shapeType)
{
	ShapeBase * shape = nullptr;
	if (shapeType == SPHERE_SHAPE) shape = new SphereShape(shapeType);
	if (shapeType == CONVEX_POLYHEDRON_SHAPE) shape = new ConvexPolyhedronShape(shapeType);
	if (shapeType == TERRAIN_SHAPE) shape = new TerrainShape(shapeType);
	return shape;
}

void CollisionWorld::ReserveCollisionResponders(size_t numCollisionResponders)
{
	_collisionResponders.reserve(numCollisionResponders);
}

void CollisionWorld::AppendCollisionResponder(ICollisionResponder * collisionResponder)
{
	_collisionResponders.push_back(collisionResponder);
}

int CollisionWorld::CollideShapes(double virtualTime, float timeStep)
{
	int totalNumContacts = 0;
	// O(N^2) brute-force collision detection.
	int numShapes = static_cast< int >(_shapes.size()); // Potentially reduce value width
	for (int index1 = 0; index1 < numShapes - 1; ++index1) {
		ShapeBase * shape1 = _shapes[index1];
		while (shape1 == nullptr) { //shape1->Empty() TODO: ask about this
			delete shape1;
			shape1 = _shapes[index1] = _shapes[numShapes - 1]; // TODO: Instead of reordering, use separate read and write indices and shift all elements left one.
		}
		if (!shape1->IsCollidable()) { // Shape is not collidable so skip it.
			continue;
		}
		for (int index2 = index1 + 1; index2 < numShapes; ++index2) {
			ShapeBase * shape2 = _shapes[index2];
			if (!shape2->IsCollidable()) { // Shape is not collidable so skip it.
				continue;
			}
			const float boundingSphereDistance = shape1->GetBoundingSphereDistance(*shape2);
			if (boundingSphereDistance <= 0.0f) { // Broad phase test indicates possible collision.
				const size_t startContactIndex = _contactInfos.size();
				const int numContactsForPair = DetectNarrowPhase(shape1, shape2);
				const size_t endContactIndex = _contactInfos.size();
				if (numContactsForPair > 0) {
					totalNumContacts += numContactsForPair;
					for (size_t idxContact = startContactIndex; idxContact < endContactIndex; idxContact++) { // For each contact between current pair of shapes...
						ContactInfo & contactInfo = _contactInfos[idxContact];
						contactInfo.mNumContactsForPair = numContactsForPair;
					}
					if (_contactInfos.size() >= _contactInfos.capacity()) { // Contacts array has no room for another contact.
						RespondToCollisions(virtualTime, timeStep);
						ClearContactInfos();
					}
				}
			}
		}
	}
	if (_contactInfos.size() > 0) {
		RespondToCollisions(virtualTime, timeStep);
		ClearContactInfos();
	}
	return totalNumContacts;

}

ContactInfo & CollisionWorld::NewContactInfo()
{
	// TODO: insert return statement here
	ContactInfo* ci = new ContactInfo();
	return *ci;

}

void CollisionWorld::ClearContactInfos()
{
	_contactInfos.clear();
}

void CollisionWorld::AddShape(ShapeBase * shape)
{
	_shapes.push_back(shape);
}

void CollisionWorld::RespondToCollisions(double virtualTime, float timeNow)
{
	CollisionResponderIterator end = _collisionResponders.end();
	for (CollisionResponderIterator iter = _collisionResponders.begin(); iter != end; ++iter)
	{
		ICollisionResponder * collisionResponder = *iter;
		collisionResponder->operator()(_contactInfos, virtualTime, timeNow);
	}
}



int CollisionWorld::DetectSphereToSphere( ShapeBase * shape1 , ShapeBase * shape2 )
{
	
	if (shape1->GetBoundingSphereDistance(*shape2) <= 0.0f) {
		ContactInfo & lastContact = NewContactInfo();
		const float radSum = shape1->GetBoundingSphere().GetRadius() + shape2->GetBoundingSphere().GetRadius();
		const float between = shape1->GetBoundingSphere().GetRadius() / radSum;
		const Math3D::Vector4 v3hitPosition = (1.0f - between) * shape1->GetBoundingSphere().GetV3Position() + between * shape2->GetBoundingSphere().GetV3Position();
		lastContact.mv3Position = v3hitPosition;
		const Math3D::Vector4 v3from1to2 = shape2->GetBoundingSphere().GetV3Position() - shape1->GetBoundingSphere().GetV3Position();
		const Math3D::Vector4 v3normal = v3from1to2.GetDir();
		lastContact.mv3Normal = v3normal;
		lastContact.mPenetrationDepth = -0.5f * shape1->GetBoundingSphereDistance(*shape2);
		lastContact.mShape1 = shape1;
		lastContact.mShape2 = shape2;
		return 1;
	}
	return 0;
}

int CollisionWorld::DetectConvexPolyhedronToConvexPolyhedron_Helper(ConvexPolyhedronShape * shape1, ConvexPolyhedronShape * shape2)
{
	return 0;
}

int CollisionWorld::DetectSphereToConvexPolyhedron(ShapeBase * shape1, ShapeBase * shape2)
{
	const SphereShape * sphereShape = reinterpret_cast< const SphereShape * >(shape1);
	const ConvexPolyhedronShape * cvxPolyShape = reinterpret_cast< const ConvexPolyhedronShape * >(shape2);
	// Transform query point from world space into model space of convex polyhedron.
	// (The opposite could also happen: Transform the convex polyhedron into world space.
	// That would be mathematically equivalent but computationally possibly slower.)
	const Math3D::Vector4 & v3worldSpaceQueryPoint = sphereShape->GetBoundingSphere().GetV3Position();
	Math3D::Vector4 translationVectorforcvxPolyShape = cvxPolyShape->GetLocalToWorld().getVec4W();
	translationVectorforcvxPolyShape.setW(0.0f);
	const Math3D::Vector4 v3translatedQueryPoint = v3worldSpaceQueryPoint - translationVectorforcvxPolyShape;
	const Math3D::Vector4 v3modelSpaceQueryPoint = cvxPolyShape->GetLocalToWorld().TransformNormalByUpper3x3Transpose(v3translatedQueryPoint);
	size_t idxMaxDist = ~size_t(0); // Initialize for safety, but ContactDistanceRelativePoint assigns to actual value does not matter.
	const float sphereToPlaneDist = cvxPolyShape->ContactDistanceRelativePoint(v3modelSpaceQueryPoint, idxMaxDist) - sphereShape->GetBoundingSphere().GetRadius();
	if ((sphereToPlaneDist <= 0.0f) && (idxMaxDist < cvxPolyShape->GetNumPlanes()))
	{ // Sphere made contact with convex polyhedron.
		Math3D::Vector4 contactPlane;
		cvxPolyShape->GetWorldSpacePlane(contactPlane, idxMaxDist);
		// Assign contact from shallowest penetration.
		// Found contact. Store its info.
		ContactInfo & lastContact = NewContactInfo();
		lastContact.mv3Normal = -Math3D::Vector4(contactPlane.getX(), contactPlane.getY(), contactPlane.getZ()); // Convention: Hit normal points from shape 1 to 2.
		lastContact.mPenetrationDepth = -sphereToPlaneDist;
		lastContact.mv3Position = v3worldSpaceQueryPoint - lastContact.mv3Normal * (-sphereToPlaneDist);
		lastContact.mShape1 = shape1;
		lastContact.mShape2 = shape2;
		return 1;
	}
	return 0;
}

int CollisionWorld::DetectSphereToTerrain(ShapeBase * shape1, ShapeBase * shape2)
{
	const SphereShape * sphereShape = reinterpret_cast< const SphereShape * >(shape1);
	const TerrainShape * terrainShape = reinterpret_cast< const TerrainShape * >(shape2);
	Math3D::Vector4 v3minProbeDir; // direction from sphere center to probe
	float minSep = std::numeric_limits<float>::max(); // minimum separation across all probes
	Math3D::Vector4 minPlane; // plane associated with minimum separation
	Math3D::Vector4 v3minProbePos; // position of probe with minimum separation

	Math3D::Vector4 sPosX(1.0f, 0.0f, 0.0f);
	Math3D::Vector4 sPosY(0.0f, 1.0f, 0.0f);
	Math3D::Vector4 sNegX(-1.0f, 0.0f, 0.0f);
	Math3D::Vector4 sNegY(0.0f, -1.0f, 0.0f);
	Math3D::Vector4 sNegZ(0.0f, 0.0f, -1.0f);
	
# define CHOOSE_MINIMAL_SEPARATION( probeDir ) \
{ \
float separation ; /* distance from terrain probe point and sphere center */ \
Math3D::Vector4 plane ; /* plane associated with contact point on terrain */ \
const Math3D::Vector4 v3probePosition = sphereShape->GetBoundingSphere().GetV3Position() + probeDir * sphereShape->GetBoundingSphere().GetRadius() ; \
terrainShape->GetSurfaceInfo( separation , plane , v3probePosition ) ; \
if( separation < minSep ) \
{ \
v3minProbeDir = probeDir ; \
minSep = separation ; \
minPlane = plane ; \
v3minProbePos = v3probePosition ; \
} \
} 
	CHOOSE_MINIMAL_SEPARATION(sNegZ);
	CHOOSE_MINIMAL_SEPARATION(sNegX);
	CHOOSE_MINIMAL_SEPARATION(sPosX);
	CHOOSE_MINIMAL_SEPARATION(sNegY);
	CHOOSE_MINIMAL_SEPARATION(sPosY);
# undef CHOOSE_MINIMAL_SEPARATION
	if (minSep < 0.0f)
	{ // Some part of sphere is below terrain.
		ContactInfo & lastContact = NewContactInfo();
		lastContact.mv3Normal = -Math3D::Vector4(minPlane.getX(), minPlane.getY(), minPlane.getZ()); // Convention: Hit normal points from shape 1 to 2.
		lastContact.mPenetrationDepth = std::fmin(-minSep, sphereShape->GetBoundingSphere().GetRadius() * 0.99f);
		const Math3D::Vector4 v3probeRel = lastContact.mv3Normal * (sphereShape->GetBoundingSphere().GetRadius() - 0.5f * lastContact.mPenetrationDepth); // Approximation.
		lastContact.mv3Position = sphereShape->GetBoundingSphere().GetV3Position() + v3probeRel;
		lastContact.mShape1 = shape1;
		lastContact.mShape2 = shape2;
		return 1;
	}
	return 0;

}

int CollisionWorld::DetectConvexPolyhedronToConvexPolyhedron(ShapeBase * shape1, ShapeBase * shape2)
{
	return 0;
}

int CollisionWorld::DetectConvexPolyhedronToTerrain(ShapeBase * shape1, ShapeBase * shape2)
{
	return 0;
}

int CollisionWorld::DetectNarrowPhase(ShapeBase * shape1, ShapeBase * shape2)
{
	switch (shape1->GetShapeType())
	{
	case SPHERE_SHAPE:
		switch (shape2->GetShapeType())
		{
		case SPHERE_SHAPE: return DetectSphereToSphere(shape1, shape2); break;
		case CONVEX_POLYHEDRON_SHAPE: return DetectSphereToConvexPolyhedron(shape1, shape2); break;
		case TERRAIN_SHAPE: return DetectSphereToTerrain(shape1, shape2); break;
		default: return 0; break;
		}
		break;
	case CONVEX_POLYHEDRON_SHAPE:
		switch (shape2->GetShapeType())
		{
		case SPHERE_SHAPE: return DetectSphereToConvexPolyhedron(shape2, shape1); break;
		case CONVEX_POLYHEDRON_SHAPE: return DetectConvexPolyhedronToConvexPolyhedron(shape2, shape1); break;
		case TERRAIN_SHAPE: return DetectConvexPolyhedronToTerrain(shape1, shape2); break;
		default: return false; break;
		}
		break;
	case TERRAIN_SHAPE:
		switch (shape2->GetShapeType())
		{
		case SPHERE_SHAPE: return DetectSphereToTerrain(shape2, shape1); break;
		case CONVEX_POLYHEDRON_SHAPE: return DetectConvexPolyhedronToTerrain(shape2, shape1); break;
		case TERRAIN_SHAPE: /* Why would this ever happen? When worlds collide. */ return 0; break;
		default: return 0; break;
		}
		break;
	default: return 0; break;
	}
}
