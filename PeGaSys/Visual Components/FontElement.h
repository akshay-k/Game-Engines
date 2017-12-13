#pragma once
#include "stdafx.h"
#include "Vector4.h"
#include "builtInFont_MonoSpace.h"

class FontElement
{
private:
	//struct coordinates {
	//	int x, y;
	//};

	int identifier;
	float baseline_size;
	//vector<coordinates> lowerLeft;
	//vector<coordinates> bearing;
	//vector<coordinates> dimensions;

	Math3D::Vector4 v2lowerLeft;
	Math3D::Vector4 v2bearing;
	Math3D::Vector4 v2dimensions;

	//vector<int> width;
	//vector<int> height;

	Math3D::Vector4 v2widthandheight;
	float advance;

	unsigned mchar;
public:
	//FontElement();
	//~FontElement();

	FontElement(int identifier, BuiltInFontE builtInFont);

	const Math3D::Vector4 GetUpperRight() const;

	const float GetDescent() const;

	const float GetBearing() const;

	const float GetDimensions() const;

	const float GetAdvance() const;

	const Math3D::Vector4 GetLowerLeft() const;

	const const unsigned char GetBuiltInChar(size_t) const;

	const char GetChar() const;

};