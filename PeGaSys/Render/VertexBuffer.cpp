#include "VertexBuffer.h"
#include <iostream>
#include <cstddef>

VertexBuffer::VertexBuffer(Shader &shader, 
	GLenum primitive) : mShader(shader), mPrimitive(primitive)
{
	glGenBuffers(1, &mVboName);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &mVboName);
	mVboName = 0;
}

void VertexBuffer::LoadData(GenericVertex* data, size_t numVertices)
{
	int baseOffset = 0;
	mPopulation = 8*numVertices;
	mStride = sizeof(GenericVertex);
	mOffsetPos = reinterpret_cast<void*>(baseOffset + offsetof(GenericVertex, position));
	mOffsetColor = reinterpret_cast<void*>(baseOffset + offsetof(GenericVertex, color));
	mOffsetTex = reinterpret_cast<void*>(baseOffset + offsetof(GenericVertex, texture));
	glBindBuffer(GL_ARRAY_BUFFER, mVboName);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GenericVertex), data, GL_STREAM_DRAW);
}

//TODO: get rid of that sizeof float
void VertexBuffer::LoadData(const void * data,
	size_t population,
	size_t stride,
	GLvoid *positionOffset,
	GLvoid *colorOffset, 
	GLvoid *textureOffset)
{
	mPopulation = population;
	mStride = stride;
	mOffsetPos = positionOffset;
	mOffsetColor = colorOffset;
	mOffsetTex = textureOffset;
	glBindBuffer(GL_ARRAY_BUFFER, mVboName);
	std::cout << "sizeof data in vb:" << mPopulation * sizeof(float) << std::endl;
	glBufferData(GL_ARRAY_BUFFER, mPopulation*sizeof(float), data, GL_STREAM_DRAW);
}

void VertexBuffer::SetShader(const Shader & shader)
{
	mShader = shader;
}

void VertexBuffer::ConfigureAttribute(const std::string & name, unsigned int size, GLvoid * offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVboName);
	int idx = mShader.GetAttributeIndex(name);
	if (idx != -1) {
		glEnableVertexAttribArray(idx);
		glVertexAttribPointer(idx, size, GL_FLOAT, GL_FALSE, (unsigned int)mStride, offset);
	}
}

void VertexBuffer::ConfigureCommonAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, mVboName);
	int idx = mShader.GetPositionIndex();
	std::cout << "position index: " << idx << std::endl;
	if (idx != -1) {
		glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, (unsigned int)mStride, mOffsetPos);
		glEnableVertexAttribArray(idx);
	}
	idx = mShader.GetColorIndex();
	std::cout << "color index: " << idx << std::endl;
	if (idx != -1) {
		glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, (unsigned int)mStride, mOffsetColor);
		glEnableVertexAttribArray(idx);
	}
	idx = mShader.GetTextureIndex();
	std::cout << "texture index: " << idx << std::endl;
	if (idx != -1) {
		glVertexAttribPointer(idx, 2, GL_FLOAT, GL_FALSE, (unsigned int)mStride, mOffsetTex);
		glEnableVertexAttribArray(idx);
	}
}

void VertexBuffer::RenderVertexBuffer()
{
	glDrawArrays(mPrimitive, 0, (unsigned int)mPopulation);
}

