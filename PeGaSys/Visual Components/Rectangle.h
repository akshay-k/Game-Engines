#pragma once

class Rectangle
{
private:
	float _y;
	float _x;
	float _height;
	float _width;

public:
	Rectangle() {}
	Rectangle(float, float) { _width = 1; _height = 1; }

	float get_y() { return _y; }
	float set_y(float Y) { _y = Y; return _y; }

	float get_x() { return _x; }
	float set_x(float X) { _x = X; return _x; }

	float getHeight() { return _height; }
	float setHeight(float H) { _height = H; return _height; }

	float getWidth() { return _width; }
	float setWidth(float W) { _width = W; return _width; }
};