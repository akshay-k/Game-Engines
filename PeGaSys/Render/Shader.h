#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include "../Math/Matrix44.h"


class Shader {
public:
	Shader() {};
	// constructor reads and builds the shader
	Shader(const char* vertexPath, 
		const char* fragmentPath,
		int posIdx,
		int colorIdx,
		int texIdx);
	Shader(const char* vertexPath, const char* fragmentPath);



	unsigned int GetID() const { return ID; }

	// set uniform values
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetMat4(const std::string &name, const float * mat) const;

	// set attribute fields (default values match shader files currently in folder)
	void SetAttributeIndices(const std::string &posName = "aPosition",
		const std::string &colorName = "aColor",
		const std::string &texName = "aTexCoord");

	// get attribute from name
	int GetAttributeIndex(const std::string &name) const;
	// get expected attributes
	int GetPositionIndex() const { return aPositionIndex; }
	int GetColorIndex() const { return aColorIndex; }
	int GetTextureIndex() const { return aTextureIndex; }


	// use/activate the shader
	void Use();

protected:
	void LoadFromFile(const char* vertexPath, const char* fragmentPath);

	unsigned int ID;
	// expected attribute indices (for convenience)
	int aPositionIndex;
	int aColorIndex;
	int aTextureIndex;

	void CheckCompileErrors(unsigned int id, std::string shaderType) const;
};

#endif
