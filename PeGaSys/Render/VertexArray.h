#pragma once
#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include <glad\glad.h>
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray(GLenum primitive = GL_TRIANGLES);
	~VertexArray();

	unsigned int GetName() const { return mVaoName; }
	IndexBuffer GetIndexBuffer() const { return mIdxBuffer; }
	void SetIndexBuffer(const IndexBuffer &idxBuffer);
	void RemoveIndexBuffer();

	void Bind();
	void Unbind();
	void Render();
	void Render(unsigned int numVertices);


private:
	unsigned int mVaoName;
	GLenum mPrimitive;

	IndexBuffer mIdxBuffer;
};

#endif
