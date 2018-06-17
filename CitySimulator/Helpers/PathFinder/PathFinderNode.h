#pragma once
#include "../../Helpers/Coordinate.h"
#include "../../Collections/List.h"
class PathFinder;

/**
 * \brief Struct that acts as the collection holder for the pathfind system
 */
struct PathFinderNode
{
    friend PathFinder;
public:
    bool operator<(PathFinderNode& other) const;
    bool operator<=(PathFinderNode& other) const;
    bool operator==(PathFinderNode& other) const;
private:
    PathFinderNode(const Coordinate& coords);
    ~PathFinderNode();
    float step = 0;
    float estimatedSteps = 0;
    bool wasOpened = false;
    PathFinderNode* parent = nullptr;
    Coordinate coords;
    List<Coordinate> neighbours;
};

