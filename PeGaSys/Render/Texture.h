#pragma once
#include "Image.h"
class Texture
{
public:
	Texture();
	~Texture();

	void Create2DTextureFromImage(const Image * image);
	void OpenGLBind();
	unsigned int GetTextureName() const;
	void Create2DTextureFromFile(const char* imgPath);
	void ActivateBind(unsigned int whichTex); // activates texture before binding


private:
	unsigned int mTextureName; // unique "name" of texture

};

