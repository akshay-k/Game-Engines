#pragma once
#include "VertexElement.h"
class VertexDataFormat
{
	enum VertexFormatE
	{
		VERTEX_FORMAT_NONE,
		POSITION,
		POSITION_NORMAL,
		POSITION_COLOR,
		POSITION_TEXTURE,
		POSITION_NORMAL_COLOR,
		POSITION_NORMAL_TEXTURE,
		POSITION_COLOR_TEXTURE,
		POSITION_NORMAL_COLOR_TEXTURE,
		GENERIC,
		NUM_FORMATS
	};

public:
	VertexDataFormat();
	~VertexDataFormat();

private:
	VertexElement* mVertexElements;
};

