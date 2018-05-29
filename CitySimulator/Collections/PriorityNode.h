#pragma once
#include "Node.h"


template<typename T>
class PriorityNode : public Node<T>
{
    template<typename T>
    friend class PriorityQueue;
private:
    PriorityNode(const T& item, const float score, Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : Node<T>(item, prev, next), score(score)
    {    }
    float score;
};
