#pragma once
#include "../../Helpers/Coordinate.h"
class PathFinder;

/**
 * \brief Struct that acts as the collection holder for the pathfind system
 */
struct PathFinderNode
{
    friend PathFinder;
public:
    bool operator<(PathFinderNode& other) const;
private:
    PathFinderNode(const Coordinate& coords);
    float step = 0;
    float estimatedSteps = 0;
    bool wasOpened = false;
    PathFinderNode* parent = nullptr;
    Coordinate coords;
};

