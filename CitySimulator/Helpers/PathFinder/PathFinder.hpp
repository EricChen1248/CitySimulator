#pragma once
#include "PathFinderNode.hpp"
#include "../../Collections/Stack.h"
#include "../../Collections/PriorityQueue.h"

/**
 * \brief Static class that uses A* heuristic pathfinding algorithm that can find a path from two coordinates
 */
class PathFinder
{
public:    
    static void Initialize();
    static Stack<Coordinate>* PathTo(const Coordinate& source, Coordinate dest);
    static bool Pathable(const Coordinate& source, const Coordinate& dest) { return CoordToNodeMap(source)->quadrant == CoordToNodeMap(dest)->quadrant; }
    static void MapPlot(Plot* plot);
    static Plot* GetPlot(const Coordinate& coords) { return CoordToNodeMap(coords)->plot; }
    static void RemapQuadrants();
    static void CheckQuadrant(Plot* plot);
private:
    PathFinder() = default;
    static int nodeCount;
    static int quandrantCount;
    static bool initialized;
    static PathFinderNode*** nodesMap;
    static PathFinderNode** openList;
    static int openCount;
    static PriorityQueue<PathFinderNode*> queue;
    
    static PathFinderNode* CoordToNodeMap(const Coordinate& coords);
    
};

