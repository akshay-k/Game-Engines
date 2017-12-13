#include "stdafx.h"
#include "TexturedGeometry.h"
#include <iostream>

//TexturedGeometry::TexturedGeometry()
//{
//}
//
//
//TexturedGeometry::~TexturedGeometry()
//{
//}

void TexturedGeometry::GenerateRectangle(Rectangle & rectangle, const unsigned char colorRGBA[4])
{
	VertexPosTexCol vert0, vert2;

	// First triangle
	vert0._position = Math3D::Vector4 /*Vec3*/(rectangle.get_x(), /*RhFromCanvas(*/rectangle.get_y()/*)*/, 0.0f);
	vert0._textureCoords = Math3D::Vector4 /*Vec2*/(1.0f, 1.0f, 1.0f);
	vert0._colorRGBA[0] = colorRGBA[0];
	vert0._colorRGBA[1] = colorRGBA[1];
	vert0._colorRGBA[2] = colorRGBA[2];
	vert0._colorRGBA[3] = colorRGBA[3];
	_vertices.push_back(vert0);
	{
		VertexPosTexCol vert1;
		vert1._position = Math3D::Vector4 /*Vec3*/(rectangle.get_x(), /*RhFromCanvas(*/rectangle.get_y() + rectangle.getHeight()/*)*/, 0.0f);
		vert1._textureCoords = Math3D::Vector4 /*Vec2*/(0.0f, 1.0f, 0.0f);
		vert1._colorRGBA[0] = colorRGBA[0];
		vert1._colorRGBA[1] = colorRGBA[1];
		vert1._colorRGBA[2] = colorRGBA[2];
		vert1._colorRGBA[3] = colorRGBA[3];
		_vertices.push_back(vert1);
	}

	vert2._position = Math3D::Vector4 /*Vec3*/(rectangle.get_x() + rectangle.getWidth(), /*RhFromCanvas*/(rectangle.get_y() + rectangle.getHeight()), 0.0f);
	vert2._textureCoords = Math3D::Vector4 /*Vec2*/(1.0f, 1.0f, 1.0f);
	vert2._colorRGBA[0] = colorRGBA[0];
	vert2._colorRGBA[1] = colorRGBA[1];
	vert2._colorRGBA[2] = colorRGBA[2];
	vert2._colorRGBA[3] = colorRGBA[3];
	_vertices.push_back(vert2);

	// Second triangle
	_vertices.push_back(vert0);
	_vertices.push_back(vert2);
	{
		VertexPosTexCol vert3;
		vert3._position = Math3D::Vector4 /*Vec3*/(rectangle.get_x() + rectangle.getWidth(), /*RhFromCanvas*/(rectangle.get_y()), 0.0f);
		vert3._textureCoords = Math3D::Vector4 /*Vec2*/(1.0f, 0.0f, 0.0f);
		vert3._colorRGBA[0] = colorRGBA[0];
		vert3._colorRGBA[1] = colorRGBA[1];
		vert3._colorRGBA[2] = colorRGBA[2];
		vert3._colorRGBA[3] = colorRGBA[3];
		_vertices.push_back(vert3);
	}
}

void TexturedGeometry::WriteMtlFile(const char * fileNameBase, bool hasTexture) const
{
	static const size_t filenameMaxLen = 128;
	char filename[filenameMaxLen];
	sprintf_s(filename, "%s.mtl", fileNameBase);
	FILE * pFile = fopen(filename, "w");
	if (NULL == pFile)
	{
		/*FAIL();*/
		cout << "Fail";
		return;
	}
	if (hasTexture)
	{
		fprintf(pFile
			, "# Material for %s\n"
			"newmtl material0\n"
			"Ka 1.000000 1.000000 1.000000\n"
			"Kd 1.000000 1.000000 1.000000\n"
			"Ks 0.000000 0.000000 0.000000\n"
			"Tr 1.000000\n"
			"illum 1\n"
			"Ns 0.000000\n"
			"map_Ka %s.ppm\n" // Want to use these texture options: "-blendu off -blendv off -clamp on" ...but MeshLab does not respect them.
			"map_Kd %s.ppm\n" // Want to use these texture options: "-blendu off -blendv off -clamp on" ...but MeshLab does not respect them.
			, fileNameBase
			, fileNameBase
			, fileNameBase);
	}

	else
	{
		fprintf(pFile
			, "# Material for %s\n"
			"newmtl material0\n"
			"Ka 1.000000 1.000000 1.000000\n"
			"Kd 1.000000 1.000000 1.000000\n"
			"Ks 0.000000 0.000000 0.000000\n"
			"Tr 1.000000\n"
			"illum 1\n"
			"Ns 0.000000\n"
			, fileNameBase);
	}
	fflush(pFile);
	fclose(pFile);
}

void TexturedGeometry::WriteObjFile(const char * fileNameBase) const
{
	static const size_t filenameMaxLen = 128;
	char filename[filenameMaxLen];
	sprintf_s(filename, "%s.obj", fileNameBase);
	FILE * pFile = fopen(filename, "w");
	if (NULL == pFile)
	{
		//FAIL();
		cout << "Fail";
		return;
	}

	// Write model file contents
	fprintf(pFile, "mtllib %s.mtl\n", fileNameBase);

	// For each vertex...
	// (might have to make each of these a contiguous list. Don't know if interleaving is allowed.)
	// Write vertex positions "v"
	// Write vertex texCoords "vt"
	// Wavefront OBJ has no way to represent per-vertex color.
	for (size_t iVert = 0; iVert < _vertices.size(); ++iVert)
	{   // For each vertex...
		const VertexPosTexCol & vert = _vertices[iVert];
		fprintf(pFile, "v %g %g %g\n", vert._position.getX(), vert._position.getY(), vert._position.getZ());
	}
	for (size_t iVert = 0; iVert < _vertices.size(); ++iVert)
	{   // For each vertex...
		const VertexPosTexCol & vert = _vertices[iVert];
		fprintf(pFile, "vt %g %g\n", vert._textureCoords.getX(), vert._textureCoords.getY());
	}

	fprintf(pFile, "use mtl material0\n");
	const size_t numTris = _vertices.size() / 3;
	for (size_t iTri = 0; iTri < numTris; ++iTri)
	{   // For each triangle...
		// Write triangle face
		const size_t iv0 = iTri * 3 + 1; // index of first vertex in triangle
		fprintf(pFile, "f %i/%i %i/%i %i/%i\n", iv0 + 0, iv0 + 0, iv0 + 1, iv0 + 1, iv0 + 2, iv0 + 2);
	}
	fflush(pFile);
	fclose(pFile);
}

//void FAIL() {
//	cout << "Fail";
//}
