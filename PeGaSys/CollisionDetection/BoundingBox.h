#pragma 
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "ShapeBase.h"
struct BoundingBox
{
	void Clear()
	{
		mV3Min = Math3D::Vector4(0.0f, 0.0f, 0.0f);
		mV3Max = Math3D::Vector4(0.0f, 0.0f, 0.0f);
		mShape = nullptr;
	}
	Math3D::Vector4 mV3Min; /// Minimal corner of axis-aligned bounding box
	Math3D::Vector4 mV3Max; /// Maximal corner of axis-aligned bounding box
	ShapeBase * mShape; /// (non-owning) Associated Shape object
};


#endif // !BOUNDINGBOX_H