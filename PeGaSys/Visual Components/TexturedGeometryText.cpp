#include "stdafx.h"
#include "TexturedGeometryText.h"


//TexturedGeometryText::TexturedGeometryText()
//{
//}
//
//
//TexturedGeometryText::~TexturedGeometryText()
//{
//}

void TexturedGeometryText::GenerateCharacter(size_t characterIndex, const Math3D::Vector4 & v2position, const unsigned char colorRGBA[4], Math3D::Vector4 & minXminYmaxXmaxY)
{
	const FontElement & fontElement = fontTexture->GetElement(characterIndex);
	// Generate quad.  Width depends on character width.  Assign texture coordinates based on lookup in FontTexture.
	Math3D::Vector4 v3positionBase = Math3D::Vector4(v2position.getX() + fontElement.GetBearing()/*.x*/, /*RhFromCanvas(*/v2position.getY()/*)*/, 0.0f);
	Math3D::Vector4 v2texCoords00, v2texCoords11;
	SetTexCoords(v2texCoords00, v2texCoords11, fontElement);
	VertexPosTexCol vert0, vert2;

	// First triangle
	vert0._position = v3positionBase + Math3D::Vector4(0.0f, /*RhFromCanvas(*/ /* upward */ -fontElement.GetBearing()/*.y*//*)*/, 0.0f);
	vert0._textureCoords = v2texCoords00;
	vert0._colorRGBA[0] = colorRGBA[0];
	vert0._colorRGBA[1] = colorRGBA[1];
	vert0._colorRGBA[2] = colorRGBA[2];
	vert0._colorRGBA[3] = colorRGBA[3];
	vert0._character = fontElement.GetChar();
	_vertices.push_back(vert0);

	minXminYmaxXmaxY.setX(fmin(minXminYmaxXmaxY.getX(), vert0._position.getX()));
	minXminYmaxXmaxY.setY(fmin(minXminYmaxXmaxY.getY(), vert0._position.getY()));
	minXminYmaxXmaxY.setZ(fmax(minXminYmaxXmaxY.getZ(), vert0._position.getX()));
	minXminYmaxXmaxY.setW(fmax(minXminYmaxXmaxY.getW(), vert0._position.getY()));

	{
		VertexPosTexCol vert1;
		vert1._position = v3positionBase + Math3D::Vector4(0.0f,/* RhFromCanvas( *//* downward */ fontElement.GetDescent()/*)*/, 0.0f);
		vert1._textureCoords.setX(v2texCoords00.getX());
		vert1._textureCoords.setY(v2texCoords11.getY());
		vert1._colorRGBA[0] = colorRGBA[0];
		vert1._colorRGBA[1] = colorRGBA[1];
		vert1._colorRGBA[2] = colorRGBA[2];
		vert1._colorRGBA[3] =colorRGBA[3];
		vert1._character = fontElement.GetChar();
		_vertices.push_back(vert1);

		minXminYmaxXmaxY.setX(fmin(minXminYmaxXmaxY.getX(), vert1._position.getX()));
		minXminYmaxXmaxY.setY(fmin(minXminYmaxXmaxY.getY(), vert1._position.getY()));
		minXminYmaxXmaxY.setZ(fmax(minXminYmaxXmaxY.getZ(), vert1._position.getX()));
		minXminYmaxXmaxY.setW(fmax(minXminYmaxXmaxY.getW(), vert1._position.getY()));
	}

	vert2._position = v3positionBase + Math3D::Vector4(fontElement.GetDimensions()/*.x*/, /*RhFromCanvas(*/ /* downward */ fontElement.GetDescent()/*)*/, 0.0f);
	vert2._textureCoords.setX(v2texCoords11.getX());
	vert2._textureCoords.setY(v2texCoords11.getY());
	vert2._colorRGBA[0] = colorRGBA[0];
	vert2._colorRGBA[1] = colorRGBA[1];
	vert2._colorRGBA[2] = colorRGBA[2];
	vert2._colorRGBA[3] = colorRGBA[3];
	vert2._character = fontElement.GetChar();
	_vertices.push_back(vert2);

	minXminYmaxXmaxY.setX(fmin(minXminYmaxXmaxY.getX(), vert2._position.getX()));
	minXminYmaxXmaxY.setY(fmin(minXminYmaxXmaxY.getY(), vert2._position.getY()));
	minXminYmaxXmaxY.setZ(fmax(minXminYmaxXmaxY.getZ(), vert2._position.getX()));
	minXminYmaxXmaxY.setW(fmax(minXminYmaxXmaxY.getW(), vert2._position.getY()));

	// Second triangle
	_vertices.push_back(vert0);
	_vertices.push_back(vert2);
	{
		VertexPosTexCol vert3;
		vert3._position = v3positionBase + Math3D::Vector4(fontElement.GetDimensions()/*.x*/, /*RhFromCanvas(*/ /* upward */ -fontElement.GetBearing()/*.y*//*)*/, 0.0f);
		vert3._textureCoords.setX(v2texCoords11.getX());
		vert3._textureCoords.setY(v2texCoords00.getY());
		vert3._colorRGBA[0] = colorRGBA[0];
		vert3._colorRGBA[1] = colorRGBA[1];
		vert3._colorRGBA[2] = colorRGBA[2];
		vert3._colorRGBA[3] = colorRGBA[3];
		vert3._character = fontElement.GetChar();
		_vertices.push_back(vert3);

		minXminYmaxXmaxY.setX(fmin(minXminYmaxXmaxY.getX(), vert3._position.getX()));
		minXminYmaxXmaxY.setY(fmin(minXminYmaxXmaxY.getY(), vert3._position.getY()));
		minXminYmaxXmaxY.setZ(fmin(minXminYmaxXmaxY.getZ(), vert3._position.getX()));
		minXminYmaxXmaxY.setW(fmin(minXminYmaxXmaxY.getW(), vert3._position.getY()));
	}
}

void TexturedGeometryText::GenerateString(const char * string, size_t strLen, const Math3D::Vector4 & stringPosition, const Math3D::Vector4 & rgba, Math3D::Vector4 & minXminYmaxXmaxY)
{
	// for each char in string, ...
	//      GenerateCharacter
	//      advance position (including kerning).

	const unsigned char colorRGBA[4] = { static_cast< unsigned char >(/*255.0f * */rgba.getX())
		, static_cast< unsigned char >(/*255.0f * */rgba.getY())
		, static_cast< unsigned char >(/*255.0f * */rgba.getZ())
		, static_cast< unsigned char >(/*255.0f * */rgba.getW()) };

	Math3D::Vector4 charPos(stringPosition);

	minXminYmaxXmaxY = Math3D::Vector4(FLT_MAX, FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (size_t iChar = 0; iChar < strLen; ++iChar)
	{
		const int charIdx = string[iChar];
		GenerateCharacter(/*static_cast< int >*/(charIdx), charPos, colorRGBA, minXminYmaxXmaxY);
		const FontElement & fontElement = fontTexture->GetElement(charIdx);
		const float advance = fontElement.GetAdvance();
		//charPos.x += advance;
		charPos.setX(charPos.getX() + advance);
	}
}

void TexturedGeometryText::SetTexCoords(Math3D::Vector4 & v2texCoords00, Math3D::Vector4 & v2texCoords11, FontElement fontElement)
{
	v2texCoords00 = fontElement.GetLowerLeft();
	v2texCoords11 = fontElement.GetUpperRight();
}
