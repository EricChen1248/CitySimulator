#pragma once
#include "PathFinderNode.h"
#include "../../Collections/Stack.h"

/**
 * \brief Static class that uses A* heuristic pathfinding algorithm that can find a path from two coordinates
 */
class PathFinder
{
public:    
    static void Initialize();
    static Stack<Coordinate>* PathTo(const Coordinate& source, Coordinate dest);
private:
    PathFinder() = default;;
    static int nodeCount;
    static bool initialized;
    static PathFinderNode*** nodesMap;
    static PathFinderNode** openList;
    static int openCount;
    static PriorityQueue<PathFinderNode*> queue;
    
    static PathFinderNode* CoordToNodeMap(const Coordinate& coords);
    
};

