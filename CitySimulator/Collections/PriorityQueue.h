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
    /**
     * \brief Adds a new item to the priority queue and sorts it
     * \param item Item to add to queue
     */
    void Enqueue(T& item) { MinHeap<T>::Add(item); }
    /**
     * \brief Returns the item at the top of the queue.
     * \return Item at the top of the queue
     * \throws out_of_range exception if empty
     */
    const T& GetTop() const { return MinHeap<T>::PeekTop(); }
    /**
     * \brief Removes the queue at the top of the queue
     */
    void Dequeue() { MinHeap<T>::RemoveTop(); }
    
    /**
     * \brief Resets the Priority Queue to allow reuse
     */
    void Reset() { MinHeap<T>::Reset(); }
};