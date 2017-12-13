#include "Image.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Image::Image(const char * filePath)
{

	mImageData = stbi_load(filePath, &mWidth, &mHeight, &mNumChannels, 0);
	stbi_set_flip_vertically_on_load(true); // flip loaded texture's on the y-axis
	if (mImageData) {
	std::cout << "Loaded successfully" << std::endl;
	std::cout << "width: " << mWidth << " height: " << mHeight << " n channels: " << mNumChannels << std::endl;
	}
	else {
	std::cout << "Failed to load texture" << std::endl;
	}
}


Image::~Image()
{
	//FreeImageData();
}

int Image::GetWidth() const
{
	return mWidth;
}

int Image::GetHeight() const
{
	return mHeight;
}

int Image::GetNumChannels() const
{
	return mNumChannels;
}

unsigned char * Image::GetImage() const
{
	return mImageData;
}

void Image::FreeImageData()
{
	stbi_image_free(mImageData);
}
