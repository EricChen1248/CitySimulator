#pragma once
#include "MinHeap.h"


/**
 * \brief Stores an item into a queue sorted by a provided score upon enqueue. Lower scores are sorted in front
 * \tparam T Type of item being stored in Priority Queue
 */
template<class T>
class PriorityQueue : public MinHeap<T>
{
public:
    void Enqueue(T& item);
    const T& GetTop() const;
    void Dequeue();    
};

/**
 * \brief Adds a new item to the priority queue and sorts it
 * \param item Item to add to queue
 */
template <class T>
void PriorityQueue<T>::Enqueue(T& item)
{
    MinHeap<T>::Add(item);
}

/**
 * \brief Returns the item at the top of the queue.
 * \return Item at the top of the queue
 * \throws out_of_range exception if empty
 */
template <class T>
const T& PriorityQueue<T>::GetTop() const
{
    return MinHeap<T>::PeekTop();
}


/**
 * \brief Removes the queue at the top of the queue
 */
template <class T>
void PriorityQueue<T>::Dequeue()
{
    MinHeap<T>::RemoveTop();
}

//
///**
// * \brief Adds and sorts an item into the queue
// * \param item Item to add to queue
// * \param score Score of the item to be added
// */
//template <class T>
//void PriorityQueue<T>::Enqueue(T& item, float score)
//{
//    auto node = new PriorityNode<T>(item, score);
//    
//    // Queue is empty
//    if (Queue<T>::count == 0)
//    {
//        Queue<T>::head = node;
//        Queue<T>::tail = node;    
//        ++Queue<T>::count;
//        return;
//    }
//    
//    PriorityNode<T>* currentNode = static_cast<PriorityNode<T>*>(Queue<T>::head);
//    PriorityNode<T>* last = nullptr;
//    // While still node to compare to
//    while (currentNode != nullptr)
//    {
//        // If current is smaller than score => score can try moving back
//        if (currentNode->score < score)
//        {
//            last = currentNode;
//            currentNode = static_cast<PriorityNode<T>*>(currentNode->next);
//            continue;
//        }
//        // Score should be before current node
//        node->next = currentNode;
//        // No previous node
//        if (last == nullptr)
//        {
//            // Score is the new head
//            Queue<T>::head = node;
//        }
//        else
//        {
//            // Else last node points to score
//           last->next = node;
//        }
//        ++Queue<T>::count;
//        return;
//    }
//    
//    // If while ended => no more points to compare to, score is last. Point to original tail and is new tail
//    Queue<T>::tail->next = node;
//    Queue<T>::tail = node;
//    ++Queue<T>::count;
//}
