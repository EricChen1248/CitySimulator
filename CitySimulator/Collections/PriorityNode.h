#pragma once
#include "Node.h"


/**
 * \brief Helper class used in priority nodes
 * \tparam T Type of item being stored in priority queue
 */
template<typename T>
class PriorityNode : public Node<T>
{
    template<class U>
    friend class PriorityQueue;
    PriorityNode(const T& item, const float score, Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : Node<T>(item, prev, next), score(score)
    {    }
    float score;
};
