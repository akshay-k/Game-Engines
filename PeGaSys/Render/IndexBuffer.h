#pragma once
#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad\glad.h>

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	unsigned int GetName() const { return mEboName; }
	int GetPopulation() const { return numIndices; }

	void LoadData(const unsigned int * data, const int population);


private:
	unsigned int mEboName; // identifier for this element buffer
	int numIndices; // number of indices currently loaded
};

#endif