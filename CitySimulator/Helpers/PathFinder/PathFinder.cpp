#include "PathFinder.h"
#include "../Constants.h"
#include "../../Collections/PriorityQueue.h"
#include "../Logger.h"
#include "../HelperFunctions.h"
#include "../../Collections/Queue.h"


int PathFinder::nodeCount = 0;
int PathFinder::quandrantCount = 0;
bool PathFinder::initialized = false;
PathFinderNode*** PathFinder::nodesMap;
PathFinderNode** PathFinder::openList;
int PathFinder::openCount;
PriorityQueue<PathFinderNode*> PathFinder::queue;

/**
 * \brief Initializes the pathfinder and allocates the required memory space, must only be initialized once
 */
void PathFinder::Initialize()
{
    if (initialized)
    { 
        Logger::Log("Pathfinder has already been initialized");
    }
    initialized = true;
    const int size = RIGHT - LEFT;
    nodesMap = new PathFinderNode**[size];
    for (int i = LEFT; i < RIGHT; ++i)
    {
        const int x = i - LEFT;
        const int left = Max(LEFT -i, LEFT);
        const int right = Min(RIGHT - i, RIGHT);
        nodesMap[x] = new PathFinderNode*[size];
        for (int j = 0; j < size; ++j)
        {
            nodesMap[x][j] = nullptr;
        }
        
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
Stack<Coordinate>* PathFinder::PathTo(const Coordinate& source, Coordinate dest)
{
    // If source and destination are in different quadrants, no path is available
    if (!Pathable(source, dest))
    {
        return nullptr;
    }
    const int size = RIGHT - LEFT;
    auto current = source;
    queue.Reset();
    auto currentNode = CoordToNodeMap(source);
    while (current != dest)
    {
        auto& neighbours = currentNode->neighbours;
        for (auto && neighbour : neighbours)
        {
            auto neighbourNode = CoordToNodeMap(neighbour);
            auto & coords = neighbourNode->coords;
            // TODO add path cost
            const int x = (coords.X() - LEFT) * size;
            const int y = coords.Y() - LEFT;
            if (openList[x + y] == nullptr)
            {
                neighbourNode->EstimateSteps(dest);
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

void PathFinder::MapPlot(Plot* plot)
{
    CoordToNodeMap(plot->Coords())->plot = plot;
}

void PathFinder::RemapQuadrants()
{
    // No need to remap if there is only one quadrant left
    if (quandrantCount == 1)
        return;

    const int size = RIGHT - LEFT;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (nodesMap[i][j] == nullptr || nodesMap[i][j]->plot->IsRiver())
            {
                continue;
            }
            nodesMap[i][j]->quadrant = INT_MAX;
        }
    }

    int currentMapping = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            auto current = nodesMap[i][j];
            if (current == nullptr || current->plot->IsRiver() || current->quadrant != INT_MAX)
            {
                continue;
            }
            Queue<PathFinderNode*> queue;
            queue.Enqueue(current);


            while (!queue.IsEmpty())
            {
                const auto node = queue.Peek();
                queue.Dequeue();

                auto& neighbours = node->neighbours;
                // For all neighbours that is not a river and hasn't been marked yet, add to queue
                for (auto&& neighbour : neighbours)
                {
                    auto n = CoordToNodeMap(neighbour);
                    if (n->plot->IsRiver() || n->quadrant != INT_MAX)
                    {
                        continue;
                    }
                    n->quadrant = currentMapping;
                    queue.Enqueue(n);
                }
            }
            ++currentMapping;
        }
    }
    quandrantCount = currentMapping;
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
