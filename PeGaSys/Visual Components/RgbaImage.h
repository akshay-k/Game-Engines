#pragma once
class RgbaImage
{
protected:
	int width;
	int height;
	unsigned char * rgba;
public:
	RgbaImage() {}
	~RgbaImage() {}

	int set_height(int h) { height = h; }
	int set_width(int w) { width = w; }

	int get_height() { return height; }
	int get_width() { return width; }
};