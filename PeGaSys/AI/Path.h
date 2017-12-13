#pragma once
#include "stdafx.h"
#include "Matrix44.h"

class Path
{
private:
	std::list<Math3D::Vector4>::iterator  curWaypoint;
	std::list<Math3D::Vector4> m_WayPoints;
	bool m_bLooped;

	const double   Pi = 3.14159;
	const double   TwoPi = Pi * 2;

public:
	Path() :m_bLooped(false), curWaypoint() {}

	Path(int    NumWaypoints, double MinX, double MinY, double MaxX, double MaxY, bool looped) : m_bLooped(looped)
	{
		CreateRandomPath(NumWaypoints, MinX, MinY, MaxX, MaxY);
		curWaypoint = m_WayPoints.begin();
	}

	Math3D::Vector4 CurrentWaypoint()const { /*assert(curWaypoint != NULL);*/ return *curWaypoint; }

	//creates a random path which is bound by rectangle described by the min/max values
	std::list<Math3D::Vector4> CreateRandomPath(int NumWaypoints, double MinX, double MinY, double MaxX, double MaxY);

	void LoopOn() { m_bLooped = true; }

	void LoopOff() { m_bLooped = false; }

	//void AddWayPoint(Math3D::Vector4 new_point);


	//methods for setting the path with either another Path or a list of vectors

	void Set(std::list<Math3D::Vector4> new_path) { m_WayPoints = new_path; curWaypoint = m_WayPoints.begin(); }

	void Set(const Path& path) { m_WayPoints = path.GetPath(); curWaypoint = m_WayPoints.begin(); }

	void Clear() { m_WayPoints.clear(); }

	std::list<Math3D::Vector4> GetPath()const { return m_WayPoints; }

	bool Finished() { return !(curWaypoint != m_WayPoints.end()); }

	inline double RandFloat() { return ((rand()) / (RAND_MAX + 1.0)); }

	inline int   RandInt(int x, int y) { return rand() % (y - x + 1) + x; }

	inline double RandInRange(double x, double y)
	{
		return x + RandFloat()*(y - x);
	}

	inline void Path::SetNextWaypoint()
	{
		assert(m_WayPoints.size() > 0);
		if (++curWaypoint == m_WayPoints.end())
		{
			if (m_bLooped)
			{
				curWaypoint = m_WayPoints.begin();
			}
		}
	}
};