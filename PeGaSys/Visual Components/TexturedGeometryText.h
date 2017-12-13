#pragma once
#include "TextRendering.h"
#include "FontTexture.h"
class FontTexture;

class TexturedGeometryText : public TexturedGeometry
{
private:
	FontTexture * fontTexture;
	//vector<VertexPosTexCol> _vertices;
	//FontElement & mfontElement;
public:
	TexturedGeometryText() { fontTexture = new FontTexture(BUILT_IN_FONT_MONOSPACE); }
	//~TexturedGeometryText();

	void GenerateCharacter(size_t characterIndex, const Math3D::Vector4 & position, const unsigned char colorRGBA[4], Math3D::Vector4 & minXminYmaxXmaxY);
	void GenerateString(const char * string, size_t strLen, const Math3D::Vector4 & stringPosition, const Math3D::Vector4 & rgba, Math3D::Vector4 & minXminYmaxXmaxY);
	void SetTexCoords(Math3D::Vector4 &, Math3D::Vector4 &, FontElement);
};