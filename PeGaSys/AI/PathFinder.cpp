#include "stdafx.h"
#include "PathFinder.h"

extern HWND g_hwndToolbar;
extern const char*  g_szApplicationName;
extern const char*	g_szWindowClassName;

void PathFinder::CreateGraph(int CellsUp, int CellsAcross)
{
	//get the height of the toolbar
	RECT rectToolbar;
	GetWindowRect(g_hwndToolbar, &rectToolbar);

	//get the dimensions of the client area
	HWND hwndMainWindow = FindWindow(g_szWindowClassName, g_szApplicationName);

	RECT rect;
	GetClientRect(hwndMainWindow, &rect);

	m_icxClient = rect.right;
	m_icyClient = rect.bottom - abs(rectToolbar.bottom - rectToolbar.top) - /*InfoWindowHeight*/ 20;

	//initialize the terrain vector with normal terrain
	m_TerrainType.assign(CellsUp * CellsAcross, 0);

	m_iCellsX = CellsAcross;
	m_iCellsY = CellsUp;
	m_dCellWidth = (double)m_icxClient / (double)CellsAcross;
	m_dCellHeight = (double)m_icyClient / (double)CellsUp;

	//delete any old graph
	delete m_pGraph;

	//create the graph
	m_pGraph = new NavGraph(false);//not a digraph

	GraphHelper_CreateGrid(*m_pGraph, m_icxClient, m_icyClient, CellsUp, CellsAcross);

	//initialize source and target indexes to mid top and bottom of grid 
	PointToIndex(VectorToPOINTS(Math3D::Vector4(m_icxClient / 2, m_dCellHeight * 2, 0.0f)), m_iTargetCell);
	PointToIndex(VectorToPOINTS(Math3D::Vector4(m_icxClient / 2, m_icyClient - m_dCellHeight * 2, 0.0f)), m_iSourceCell);

	m_Path.clear();
	m_SubTree.clear();
	m_CurrentAlgorithm = non;
	m_dTimeTaken = 0;
}

void PathFinder::CreatePathAStar()

{
	//set current algorithm
	m_CurrentAlgorithm = search_astar;

	//create and start a timer
	//PrecisionTimer timer; timer.Start();
	
	clock_t start;
	double duration;

	start = clock();

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	//create a couple of typedefs so the code will sit comfortably on the page   
	typedef Graph_SearchAStar<NavGraph, Heuristic_Euclid> AStarSearch;

	//create an instance of the A* search using the Euclidean heuristic
	AStarSearch AStar(*m_pGraph, m_iSourceCell, m_iTargetCell);

	//record the time taken  
	//m_dTimeTaken = timer.TimeElapsed();
	m_dTimeTaken = duration;
	m_Path = AStar.GetPathToTarget();
	m_SubTree = AStar.GetSPT();
	m_dCostToTarget = AStar.GetCostToTarget();
}

std::string PathFinder::GetNameOfCurrentSearchAlgorithm()const
{
	switch (m_CurrentAlgorithm)
	{
		case non: return "";
		case search_astar: return "A Star";
		case search_bfs: return "Breadth First";
		case search_dfs: return "Depth First";
		case search_dijkstra: return "Dijkstras";
	}
}

void PathFinder::UpdateAlgorithm()

{
	//update any current algorithm
	switch (m_CurrentAlgorithm)
	{
		case non:				break;
		//case search_dfs:		CreatePathDFS(); break;
		//case search_bfs:		CreatePathBFS(); break;
		//case search_dijkstra:	CreatePathDijkstra(); break;
		case search_astar:		CreatePathAStar(); break;
		default: break;
	}
}

bool PathFinder::PointToIndex(POINTS p, int& NodeIndex)
{
	//convert p to an index into the graph
	int x = (int)((double)(p.x) / m_dCellWidth);
	int y = (int)((double)(p.y) / m_dCellHeight);

	//make sure the values are legal
	if ((x>m_iCellsX) || (y>m_iCellsY))
	{
		NodeIndex = -1;
		return false;
	}

	NodeIndex = y*m_iCellsX + x;
	return true;
}

POINTS PathFinder::VectorToPOINTS(const Math3D::Vector4& v)
{
	POINTS p;
	p.x = (short)v.getX()/*.x*/;
	p.y = (short)v.getY()/*.y*/;

	return p;
}
