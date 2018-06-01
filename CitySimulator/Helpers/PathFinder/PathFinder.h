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
    static Stack<Coordinate>* PathTo(Coordinate source, Coordinate dest);
private:
    PathFinder() = default;;
    static bool initialized;
    static PathFinderNode**** nodesMap;
    static PathFinderNode** openList;
    static int openCount;
    
    static PathFinderNode* CoordToNodeMap(Coordinate& coords);
    static float EstimateSteps(Coordinate& source, Coordinate& dest);
};

