#include "PathFinderNode.h"
#include "../Constants.h"


bool PathFinderNode::operator<(PathFinderNode& other) const
{
    return this->step + this->estimatedSteps < other.step + other.estimatedSteps;
}

bool PathFinderNode::operator<=(PathFinderNode& other) const
{
    return *this < other || *this == other;
}

bool PathFinderNode::operator==(PathFinderNode& other) const
{
    return this->step + this->estimatedSteps == other.step + other.estimatedSteps;
}

PathFinderNode::PathFinderNode(const Coordinate& coords) : coords(coords)
{
    const auto neighbours = coords.GetNeighbours();
    for (int i = 0; i < 6; ++i)
    {
        auto& coord = neighbours[i];
        if (std::abs(coord.X() + coord.Y()) > -LEFT || std::abs(coord.X()) > -LEFT || std::abs(coord.Y()) > -LEFT)
        {
            continue;
        }
        this->neighbours.InsertLast(coord);
    }
    delete [] neighbours;
}

/**
 * \brief The estimated distance used in A* pathfinding. (admissible distance) (subject to change)
 * \param dest Destination coordinates to end estimation
 */
void PathFinderNode::EstimateSteps(Coordinate& dest)
{
    //TODO : Update pathfinder heuristics
    estimatedSteps = dest.Distance(coords);
}


PathFinderNode::~PathFinderNode() 
= default;
