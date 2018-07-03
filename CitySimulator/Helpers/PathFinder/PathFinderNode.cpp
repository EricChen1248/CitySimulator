#include "PathFinderNode.h"
#include "../Constants.h"
#include "../../Controllers/CoreController.h"


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

PathFinderNode::PathFinderNode(const Coordinate& coords) : coords(coords), plot(nullptr), quadrant(0)
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
    coordNeighbours = neighbours;
}

/**
 * \brief The estimated distance used in A* pathfinding. (admissible distance) (subject to change)
 * \param dest Destination coordinates to end estimation
 */
void PathFinderNode::EstimateSteps(Coordinate& dest)
{
    estimatedSteps = float(dest.Distance(coords)) / Road::MAX_SPEED;
}


PathFinderNode::~PathFinderNode()
{
    delete [] coordNeighbours;
}
