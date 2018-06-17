#include "PathFinder.h"
#include "../Constants.h"
#include "../../Collections/PriorityQueue.h"
#include "../CustomExceptions.h"


int PathFinder::nodeCount = 0;
bool PathFinder::initialized = false;
PathFinderNode*** PathFinder::nodesMap;
PathFinderNode** PathFinder::openList;
int PathFinder::openCount;

/**
 * \brief Initializes the pathfinder and allocates the required memory space, must only be initialized once
 */
void PathFinder::Initialize()
{
    if (initialized)
    { 
        throw DuplicateInitialization("Pathfinder has already been initialized");
    }
    initialized = true;
    const int size = RIGHT - LEFT;
    nodesMap = new PathFinderNode**[size];
    for (int i = LEFT; i < RIGHT; ++i)
    {
        const int x = i - LEFT;
        const int left = std::max(LEFT -i, LEFT);
        const int right = std::min(RIGHT - i, RIGHT);
        nodesMap[x] = new PathFinderNode*[size];
        for (int j = left; j < right; ++j)
        {
            const int y = j - LEFT;
            nodesMap[x][y] = new PathFinderNode(Coordinate(i,j ,-i - j));
        }
    }
    nodeCount = size * size;
    openList = new PathFinderNode*[nodeCount];
    for (int i = 0; i < nodeCount; ++i)
    {
        openList[i] = nullptr;
    }
    openCount = 0;
}

/**
 * \brief Attemps to find a path between to coordinates
 * \param source Coordinate to path from
 * \param dest Coordinate to path to
 * \return Pointer to stack of coordinates that contains the found path
 */
Stack<Coordinate>* PathFinder::PathTo(Coordinate source, Coordinate dest)
{
    const int size = RIGHT - LEFT;
    auto current = source;
    PriorityQueue<PathFinderNode*> queue;
    PathFinderNode* currentNode = CoordToNodeMap(source);
    while (current != dest)
    {
        for (auto && neighbour : currentNode->neighbours)
        {
            auto neighbourNode = CoordToNodeMap(neighbour);
            
            // TODO add path cost
            const int x = (neighbourNode->coords.X() - LEFT) * size;
            const int y = neighbourNode->coords.Y() - LEFT;
            if (openList[x + y] == nullptr)
            {
                neighbourNode->estimatedSteps = EstimateSteps(neighbourNode->coords, dest);
            }
            
            if (openList[x + y] == nullptr || openList[x + y]->step > currentNode->step + 1)
            {
                openList[x + y] = neighbourNode;
                neighbourNode->parent = currentNode;
                neighbourNode->step = currentNode->step + 1;
                queue.Enqueue(neighbourNode);
            }
        }
        currentNode = queue.GetTop();
        queue.RemoveTop();
        current = currentNode->coords;
    }

    for (int i = 0; i < nodeCount; ++i)
    {
        openList[i] = nullptr;  
    }
    
    auto path = new Stack<Coordinate>;
    path->Push(dest);
    while (current != source)
    {
        currentNode = currentNode->parent;
        current = currentNode->coords;
        path->Push(current);
    }
    
    return path;
}

/**
 * \brief Interface for easy access to retrieve pathfinder nodes of a coordinate
 * \param coords Coordinates reference to the coords
 * \return Pointer to the pathfinder node of the coords
 */
PathFinderNode* PathFinder::CoordToNodeMap(const Coordinate& coords)
{
    return nodesMap[coords.X() - LEFT][coords.Y() - LEFT];
}

/**
 * \brief The estimated distance used in A* pathfinding. (admissible distance) (subject to change)
 * \param source Source coordinates to start estimatino
 * \param dest Destination coordinates to end estimation
 * \return The estimated distance
 */
float PathFinder::EstimateSteps(Coordinate& source, Coordinate& dest)
{
    //TODO : Update pathfinder heuristics
    return dest.Distance(source);
}
