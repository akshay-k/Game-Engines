#pragma once
#include "stdafx.h"
#include "Vector4.h"
using namespace Math3D;

class Anchor
{
	int anchorVal;
	int anchorWorldCoord;

	//typedef vector<int, int> Vec2;
	Math3D::Vector4 UpperLeft;
	Math3D::Vector4 LowerRight;

public:
	//Anchor();
	//~Anchor();

	int GetLocalAnchor() { return anchorVal; }

	int GetWorldAnchor(int parentRectMinWorldCoord, int parentRectMaxWorldCoord) { anchorWorldCoord = parentRectMinWorldCoord *(1 - anchorVal) + parentRectMaxWorldCoord*anchorVal; return anchorWorldCoord; }
};
