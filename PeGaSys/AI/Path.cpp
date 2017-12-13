#pragma once
#include "stdafx.h"
#include "Path.h"

std::list<Math3D::Vector4> Path::CreateRandomPath(int NumWaypoints, double MinX, double MinY, double MaxX, double MaxY)
{
	m_WayPoints.clear();
	double midX = (MaxX + MinX) / 2.0;
	double midY = (MaxY + MinY) / 2.0;
	double smaller = min(midX, midY);
	double spacing = TwoPi / (double)NumWaypoints;

	for (int i = 0; i<NumWaypoints; ++i)
	{
		double RadialDist = RandInRange(smaller*0.2f, smaller);
		Math3D::Vector4 temp(static_cast<float>(RadialDist), 0.0f, 0.0f);
		//Vec2DRotateAroundOrigin(temp, i*spacing);
		temp.setX(midX); 
		temp.setY(midY);
		m_WayPoints.push_back(temp);
	}

	curWaypoint = m_WayPoints.begin();

	return m_WayPoints;
}
