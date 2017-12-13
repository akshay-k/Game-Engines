#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include "Shader.h"
#include <glad/glad.h>
//#include <GLFW/glfw3.h>

struct GenericVertex
{
	float position[3]; ///< untransformed (world-space) position
	float color[3]; ///< color in RGBA form
	float texture[2]; ///< 2D texture coordinates
	//float nx, ny, nz; ///< surface normal unit vector
};


class VertexBuffer
{
public:
	VertexBuffer(Shader &shader = Shader(), GLenum primitive = GL_TRIANGLES);
	virtual ~VertexBuffer();

	void LoadData(GenericVertex *data,
		size_t numVertices);

	void LoadData(const void * data,
		size_t population,
		size_t stride,
		GLvoid *positionOffset,
		GLvoid *colorOffset,
		GLvoid *textureOffset);

	// getters
	unsigned int GetName() const { return mVboName; }

	Shader GetShader() const { return mShader; }
	void SetShader(const Shader &shader);

	GLvoid * GetPositionOffset() const { return mOffsetPos; }
	GLvoid * GetColorOffset() const { return mOffsetColor; }
	GLvoid * GetTextureOffset() const { return mOffsetTex; }

	void ConfigureAttribute(const std::string & name, unsigned int size, GLvoid *offset);
	void ConfigureCommonAttributes(); // position, color, texture

	void RenderVertexBuffer();

private:

	unsigned int mVboName;

	Shader mShader;

	size_t mPopulation;
	size_t mStride;
	GLvoid *mOffsetPos;
	GLvoid *mOffsetColor;
	GLvoid *mOffsetTex;

	GLenum mPrimitive; // e.g., triangles
};

#endif