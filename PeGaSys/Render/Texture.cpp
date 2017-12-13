#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"


Texture::Texture()
{
	// generate new texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &mTextureName); // Generate a unique "name" for this texture.
}


Texture::~Texture()
{
}

void Texture::Create2DTextureFromImage(const Image * image)
{
	glBindTexture(GL_TEXTURE_2D, mTextureName); // bind texture so current object is configured

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetImage());
	glGenerateMipmap(GL_TEXTURE_2D);
	
}


void Texture::OpenGLBind()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureName);
	//TODO: add sampler state apply method here
}

unsigned int Texture::GetTextureName() const
{
	return mTextureName;
}

void Texture::Create2DTextureFromFile(const char * imgPath)
{/*
 int mWidth, mHeight, mNumChannels;
unsigned char * mImageData = stbi_load(imgPath, &mWidth, &mHeight, &mNumChannels, 0);
stbi_set_flip_vertically_on_load(true); // flip loaded texture's on the y-axis
if (mImageData) {
std::cout << "Loaded successfully" << std::endl;
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mImageData);
glGenerateMipmap(GL_TEXTURE_2D);
}
else {
std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(mImageData);
 */

}

void Texture::ActivateBind(unsigned int whichTex)
{
	glActiveTexture(GL_TEXTURE0 + whichTex); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, GetTextureName());
}


