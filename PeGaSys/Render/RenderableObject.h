#pragma once

#include <vector>
#include <string>
#include "../Math/Vector4.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class RenderableObject
{
public:
	RenderableObject();
	~RenderableObject();

private:

	float * mShapeVertices;
	unsigned int mNumShapeVertices;

	VertexArray mVAO;
	VertexBuffer mVBO;

	std::string mObjectIdentifier;
	std::vector<Math3D::Vector4> mWorldCoordinates;

};

