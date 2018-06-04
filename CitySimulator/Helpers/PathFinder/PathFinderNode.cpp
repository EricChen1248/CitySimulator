#include "PathFinderNode.h"


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

PathFinderNode::PathFinderNode(const Coordinate& coords)
{
    this->coords = coords;
}
