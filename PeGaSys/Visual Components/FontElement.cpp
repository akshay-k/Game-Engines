#include "stdafx.h"
#include "FontElement.h"



//FontElement::FontElement()
//{
//}


//FontElement::~FontElement()
//{
//}

/// Set values from built-in default font
FontElement::FontElement(int identifier, BuiltInFontE builtInFont)
	: identifier(identifier)
{
	// Following OpenGL texture coordinate convention:
	// (0,0) refers to lower left corner, which is the last row in the image.
	baseline_size = BuiltInFont_MonoSpace::_baseline;
	v2lowerLeft.setX(static_cast< float >(BuiltInFont_MonoSpace::_pixelsWidePerChar *   (identifier % BuiltInFont_MonoSpace::_numCharsPerRow)));
	v2lowerLeft.setY(BuiltInFont_MonoSpace::_pixelsHighTotal - static_cast< float >(BuiltInFont_MonoSpace::_pixelsHighPerChar * ((identifier / BuiltInFont_MonoSpace::_numCharsPerRow))));
	v2bearing = Math3D::Vector4(0.0f, BuiltInFont_MonoSpace::_pixelsHighPerChar - BuiltInFont_MonoSpace::_baseline, 0.0f);
	v2dimensions = Math3D::Vector4(static_cast< float >(BuiltInFont_MonoSpace::_pixelsWidePerChar), static_cast< float >(BuiltInFont_MonoSpace::_pixelsHighPerChar), 0.0f);
	advance = BuiltInFont_MonoSpace::_pixelsWidePerChar + 1.0f;
	mchar = GetBuiltInChar(identifier);
}

const Math3D::Vector4 FontElement::GetUpperRight() const
{
	Math3D::Vector4 v2upperRight(v2lowerLeft.getX() + v2dimensions.getX(), v2lowerLeft.getY() - v2dimensions.getY(), 0.0f);
	return v2upperRight;
}

const float FontElement::GetDescent() const
{
	return v2dimensions.getY() - v2bearing.getY();
}

const float FontElement::GetBearing() const
{
	return v2bearing.getY();
}

const float FontElement::GetDimensions() const
{
	return v2dimensions.getX() - v2dimensions.getY();
}

const float FontElement::GetAdvance() const
{
	return advance;
}

const Math3D::Vector4 FontElement::GetLowerLeft() const
{
	return v2lowerLeft;
}

const const unsigned char FontElement::GetBuiltInChar(size_t charidx) const
{
	int row = charidx % BuiltInFont_MonoSpace::_numCharsPerRow;
	int col = BuiltInFont_MonoSpace::_pixelsWidePerChar * (charidx%16);
	return builtInFont_MonoSpace_Rgba[row][col];
}

const char FontElement::GetChar() const
{
	return mchar;
}
