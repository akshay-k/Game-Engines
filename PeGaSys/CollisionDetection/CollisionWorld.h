#pragma once

#include "BoundingBox.h"
#include "ConvexPolyhedronShape.h"
#include <iostream>
#include <vector>
struct ContactInfo
{
	Math3D::Vector4 mv3Position; // World-space coordinate where overlap occurs. This is NOT necessarily where contact point will resolve to after separation; it is where penetration was detected.
	Math3D::Vector4 mv3Normal; // Direction along which to separate bodies, pointing from shape 1 to 2.
	float mPenetrationDepth; // How far along normal bodies have interpenetrated
	ShapeBase * mShape1; // (non-owning) Address of shape 1
	ShapeBase * mShape2; // (non-owning) Address of shape 2
	int mNumContactsForPair; // Number of simultaneous contacts between shape1 and shape2
};

typedef std::vector<ContactInfo> ContactInfoVector;
/** Abstract callback functor to handle collisions.
*/
class ICollisionResponder
{
public:
	// Returns whether callback changed body position or orientation, i.e. whether contact were invalidated.
	virtual bool operator()(const ContactInfoVector & contactInfoVector, double virtualTime, float timeStep) = 0;
};

class CollisionWorld
{
public:
	explicit CollisionWorld();
	~CollisionWorld();
	ShapeBase * AddNewShape(ShapeType shapeType);
	ShapeBase * NewShape(ShapeType shapeType);
	void ReserveCollisionResponders(size_t numCollisionResponders);
	void AppendCollisionResponder(class ICollisionResponder * collisionResponder);
	int CollideShapes(double virtualTime, float timeStep);

private:
	typedef std::vector<BoundingBox> BBoxContainer;
	typedef BBoxContainer::iterator BBoxIterator;
	typedef std::vector< class ICollisionResponder * > CollisionResponderContainer;
	typedef CollisionResponderContainer::iterator CollisionResponderIterator;
	typedef std::vector<ContactInfo> ContactInfoVector;
	typedef std::vector<ShapeBase * > ShapeContainer;

	ContactInfoVector _contactInfos; // Array of collision contacts
	ShapeContainer _shapes; // Addresses of collidable shape objects
	BBoxContainer _AABBs; // Axis-aligned bounding boxes, one per shape object
	CollisionResponderContainer _collisionResponders; //Callbacks to handle collisions


	ContactInfo & NewContactInfo();
	void ClearContactInfos();
	void AddShape(ShapeBase * shape);
	void RespondToCollisions(double virtualTime, float timeNow);
	int DetectSphereToSphere(ShapeBase * shape1, ShapeBase * shape2);
	int DetectConvexPolyhedronToConvexPolyhedron_Helper(ConvexPolyhedronShape * shape1, ConvexPolyhedronShape * shape2);
	int DetectSphereToConvexPolyhedron(ShapeBase * shape1, ShapeBase * shape2);
	int DetectSphereToTerrain(ShapeBase * shape1, ShapeBase * shape2);
	int DetectConvexPolyhedronToConvexPolyhedron(ShapeBase * shape1, ShapeBase * shape2);
	int DetectConvexPolyhedronToTerrain(ShapeBase * shape1, ShapeBase * shape2);
	int DetectNarrowPhase(ShapeBase * shape1, ShapeBase * shape2);

};

