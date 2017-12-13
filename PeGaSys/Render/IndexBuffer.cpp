#include "IndexBuffer.h"

#include <iostream>

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &mEboName);
}


IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mEboName);
	mEboName = 0;
	numIndices = 0;
}

void IndexBuffer::LoadData(const unsigned int * data, const int population)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEboName);
	std::cout << "sizeof data in ib:" << population * sizeof(unsigned int) << std::endl;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, population * sizeof(unsigned int), data, GL_STREAM_DRAW);
	numIndices = population;
}
