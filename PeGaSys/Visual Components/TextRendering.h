#pragma once
#include"../Math/Matrix44.h"

struct VertexPosTexCol {
	Math3D::Vector4 _textureCoords;
	unsigned char _colorRGBA[4];
	Math3D::Vector4 _position;
	char _character;
};

//vector<VertexPosTexCol> _vertices;