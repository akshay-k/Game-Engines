#pragma once
#include "ShapeBase.h"
class SphereShape :
	public ShapeBase
{
public:
	static const ShapeType sShapeType;
	SphereShape(ShapeType shapeType);
	~SphereShape();
};

