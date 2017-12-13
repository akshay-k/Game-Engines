#pragma once
class Image
{
public:
	Image(const char * filePath);
	~Image();

	int GetWidth() const;
	int GetHeight() const;
	int GetNumChannels() const;
	unsigned char* GetImage()const;

	void FreeImageData();


private:
	int mWidth;				// width in pixels
	int mHeight;			// height in pixels
	int mNumChannels;		// number of channels
	
	unsigned char *mImageData;	// image data

};

