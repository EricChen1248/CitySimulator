#pragma once
#include "PathFinderNode.h"
#include "../../Collections/Stack.h"

class PathFinder
{
public:    
    static void Initialize();
    static Stack<Coordinate>* PathTo(Coordinate source, Coordinate dest);
private:
    static PathFinderNode**** nodesMap;
    static PathFinderNode** openList;
    static int openCount;
    
    static PathFinderNode* CoordToNodeMap(Coordinate& coords);
    static float EstimateSteps(Coordinate& source, Coordinate& dest);
};

