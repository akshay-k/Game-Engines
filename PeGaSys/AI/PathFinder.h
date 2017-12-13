#pragma once
#include "stdafx.h"

class PathFinder
{
	template <class graph_type>
	void GraphHelper_CreateGrid(graph_type& graph,
		int cySize,
		int cxSize,
		int NumCellsY,
		int NumCellsX)
	{
		//need some temporaries to help calculate each node center
		double CellWidth = (double)cySize / (double)NumCellsX;
		double CellHeight = (double)cxSize / (double)NumCellsY;

		double midX = CellWidth / 2;
		double midY = CellHeight / 2;


		//first create all the nodes
		for (int row = 0; row<NumCellsY; ++row)
		{
			for (int col = 0; col<NumCellsX; ++col)
			{
				graph.AddNode(NavGraphNode<>(graph.GetNextFreeNodeIndex(),
					Math3D::Vector4(midX + (col*CellWidth),
						midY + (row*CellHeight))));

			}
		}
		//now to calculate the edges. (A position in a 2d array [x][y] is the
		//same as [y*NumCellsX + x] in a 1d array). Each cell has up to eight
		//neighbours.
		for (row = 0; row<NumCellsY; ++row)
		{
			for (int col = 0; col<NumCellsX; ++col)
			{
				GraphHelper_AddAllNeighboursToGridNode(graph, row, col, NumCellsX, NumCellsY);
			}
		}
	}

private:
	enum algorithm_type

	{
		non,
		search_astar,
		search_bfs,
		search_dfs,
		search_dijkstra
	};

	//the terrain type of each cell
	std::vector<int>              m_TerrainType;

	//this vector will store any path returned from a graph search
	std::list<int>                m_Path;

	//create a typedef for the graph type
	typedef SparseGraph<NavGraphNode<void*>, GraphEdge> NavGraph;
	NavGraph*                     m_pGraph;

	//this vector of edges is used to store any subtree returned from any of the graph algorithms (such as an SPT)
	std::vector<const GraphEdge*> m_SubTree;

	//the total cost of the path from target to source
	double                         m_dCostToTarget;

	//the currently selected algorithm
	algorithm_type                m_CurrentAlgorithm;

	//the current terrain brush
	//brush_type                    m_CurrentTerrainBrush;

	//the dimensions of the cells
	double                        m_dCellWidth;
	double                        m_dCellHeight;

	//number of cells vertically and horizontally
	int                           m_iCellsX, m_iCellsY;

	//local record of the client area
	int                           m_icxClient, m_icyClient;

	//the indices of the source and target cells
	int                           m_iSourceCell, m_iTargetCell;

	//flags to indicate if the start and finish points have been added
	bool                          m_bStart, m_bFinish;

	//should the graph (nodes and GraphEdges) be rendered?
	bool                          m_bShowGraph;


	//should the tile outlines be rendered
	bool                          m_bShowTiles;

	//holds the time taken for the most currently used algorithm to complete
	double                        m_dTimeTaken;

	//helper function for PaintTerrain (see below)
	//void  UpdateGraphFromBrush(int brush, int CellIndex);

	

public:

	PathFinder() {}
	~PathFinder() { delete m_pGraph; }

	void CreateGraph(int CellsUp, int CellsAcross);
	
	std::string GetNameOfCurrentSearchAlgorithm()const;
	
	void CreatePathAStar();

	//this calls the appropriate algorithm
	void  UpdateAlgorithm();

	bool PointToIndex(POINTS p, int& NodeIndex);

	POINTS VectorToPOINTS(const Math3D::Vector4& v);
	//{
	//	POINTS p;
	//	p.x = (short)v.getX()/*.x*/;
	//	p.y = (short)v.getY()/*.y*/;

	//	return p;
	//}
};