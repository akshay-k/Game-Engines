#pragma once
#include "TextRendering.h"
#include "Rectangle.h"
#include "Vector4.h"

class TexturedGeometry
{
private:
	//RgbaImage * image;
	float canvas_height = 100;
protected:
	vector<VertexPosTexCol> _vertices;
public:
	TexturedGeometry() {}
	//~TexturedGeometry();
	

	void GenerateRectangle(Rectangle & rectangle, const unsigned char colorRGBA[4]);
	void WriteMtlFile(const char * fileNameBase, bool hasTexture) const;
	void WriteObjFile(const char * fileNameBase) const;
};

