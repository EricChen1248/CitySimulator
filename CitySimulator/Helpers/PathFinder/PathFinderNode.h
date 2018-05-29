#pragma once
#include "../../Helpers/Coordinate.h"
class PathFinder;

struct PathFinderNode
{
    friend PathFinder;
private:
    PathFinderNode(const Coordinate& coords);
    float step = 0;
    float estimatedSteps = 0;
    bool wasOpened = false;
    PathFinderNode* parent = nullptr;
    Coordinate coords;
};

