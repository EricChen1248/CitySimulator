#pragma once
#include "Queue.h"
#include "PriorityNode.h"

template<typename T>
class PriorityQueue : public Queue<T>
{
public:
    void Enqueue(T& item, float score);
 
};

template <typename T>
void PriorityQueue<T>::Enqueue(T& item, float score)
{
    auto node = new PriorityNode<T>(item, score);
    
    // Queue is empty
    if (Queue<T>::count == 0)
    {
        Queue<T>::head = node;
        Queue<T>::tail = node;    
        ++Queue<T>::count;
        return;
    }
    
    PriorityNode<T>* currentNode = static_cast<PriorityNode<T>*>(Queue<T>::head);
    PriorityNode<T>* last = nullptr;
    // While still node to compare to
    while (currentNode != nullptr)
    {
        // If current is smaller than score => score can try moving back
        if (currentNode->score < score)
        {
            last = currentNode;
            currentNode = static_cast<PriorityNode<T>*>(currentNode->next);
            continue;
        }
        // Score should be before current node
        node->next = currentNode;
        // No previous node
        if (last == nullptr)
        {
            // Score is the new head
            Queue<T>::head = node;
        }
        else
        {
            // Else last node points to score
           last->next = node;
        }
        ++Queue<T>::count;
        return;
    }
    
    // If while ended => no more points to compare to, score is last. Point to original tail and is new tail
    Queue<T>::tail->next = node;
    Queue<T>::tail = node;
    ++Queue<T>::count;
}
