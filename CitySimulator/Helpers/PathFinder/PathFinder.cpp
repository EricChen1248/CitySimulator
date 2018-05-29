#include "PathFinder.h"
#include "../Constants.h"
#include "../../Collections/PriorityQueue.h"


PathFinderNode**** PathFinder::nodesMap;
PathFinderNode** PathFinder::openList;
int PathFinder::openCount;

void PathFinder::Initialize()
{
    int nodeCount = 0;
    const int size = RIGHT - LEFT;
    nodesMap = new PathFinderNode***[size];
    for (int i = 0; i < size; ++i)
    {
        nodesMap[i] = new PathFinderNode**[size];
        for (int j = 0; j < size; ++j)
        {
            nodesMap[i][j] = new PathFinderNode*[size];
            for (int k = 0; k < size; ++k)
            {
                if (i + j + k == 3 * -LEFT)
                {
                    ++nodeCount;
                    nodesMap[i][j][k] = new PathFinderNode(Coordinate(i + LEFT,j + LEFT,k + LEFT));
                    continue;
                }
                nodesMap[i][j][k] = nullptr;
            }
        }
    }
    
    openList = new PathFinderNode*[nodeCount];
    openCount = 0;
}

Stack<Coordinate>* PathFinder::PathTo(Coordinate source, Coordinate dest)
{
    auto current = source;
    PriorityQueue<PathFinderNode*> queue;
    Queue<PathFinderNode*> openList;
    PathFinderNode* currentNode = CoordToNodeMap(source);
    while (current != dest)
    {
        const auto neighbours = current.GetNeighbours();
        for (int i = 0; i < 6; ++i)
        {
            auto neighbourNode = CoordToNodeMap(neighbours[i]);
            if (neighbourNode == nullptr)
            {
                continue;
            }
            
            // TODO add path cost
            if (neighbourNode->wasOpened && neighbourNode->step < currentNode->step + 1)
            {
                continue;
            }
            neighbourNode->parent = currentNode;
            neighbourNode->step = currentNode->step + 1;
            if (!neighbourNode->wasOpened)
            {
                neighbourNode->estimatedSteps = EstimateSteps(neighbourNode->coords, dest);
            }
            const float score = neighbourNode->estimatedSteps + neighbourNode->step;
            neighbourNode->wasOpened = true;
            openList.Enqueue(neighbourNode);
            queue.Enqueue(neighbourNode, score);
        }
        delete [] neighbours;
        
        currentNode = queue.Dequeue();
        current = currentNode->coords;
    }
    
    while(!openList.IsEmpty())
    {
        openList.Dequeue()->wasOpened = false;
    }
    auto path = new Stack<Coordinate>;
    while (current != source)
    {
        path->Push(current);
        currentNode = currentNode->parent;
        current = currentNode->coords;
    }
    
    return path;
}

PathFinderNode* PathFinder::CoordToNodeMap(Coordinate& coords)
{
    if (coords.X() < LEFT || coords.X() >= RIGHT || coords.Y() < LEFT || coords.Y() >= RIGHT || coords.Z() < LEFT || coords.Z() >= RIGHT )
    {
        return nullptr;    
    }
    return nodesMap[coords.X() - LEFT][coords.Y() - LEFT][coords.Z() - LEFT];
}

float PathFinder::EstimateSteps(Coordinate& source, Coordinate& dest)
{
    return dest.Distance(source);
}
