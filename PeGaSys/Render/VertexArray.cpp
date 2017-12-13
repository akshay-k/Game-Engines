#include "VertexArray.h"
#include <glad/glad.h>
#include <assert.h>
#include <iostream>

VertexArray::VertexArray(GLenum primitive) : mPrimitive(primitive)
{
	glGenVertexArrays(1, &mVaoName);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mVaoName);
}



void VertexArray::SetIndexBuffer(const IndexBuffer & idxBuffer)
{
	mIdxBuffer = idxBuffer;
}

void VertexArray::RemoveIndexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, -1);
}

void VertexArray::Bind()
{
	glBindVertexArray(mVaoName);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Render()
{
	int idxPopulation = mIdxBuffer.GetPopulation();
	assert(idxPopulation > 0); // data is loaded in index buffer
	//glBindVertexArray(mVaoName);
	glDrawElements(mPrimitive, idxPopulation, GL_UNSIGNED_INT, 0);
	//std::cout << "idxpop in vao:" << idxPopulation << std::endl;
}

void VertexArray::Render(unsigned int numVertices)
{
	//glBindVertexArray(mVaoName);
	glDrawArrays(mPrimitive, 0, numVertices);
}
