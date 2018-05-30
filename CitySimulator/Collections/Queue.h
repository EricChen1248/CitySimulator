#pragma once
#include "Node.h"
#include <stdexcept>

/**
 * \brief Stores an item based on FIFO process
 * \tparam T Type of item being stored in queue
 */
template<typename T>
class Queue
{
public:
    Queue();
    ~Queue();
    void Enqueue(T item);
    T Dequeue();
    const T& Peek();
    bool IsEmpty() const { return count == 0; };
protected:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int count = 0;
};

template <typename T>
Queue<T>::Queue() = default;


/**
 * \brief Cleans up memory used by the queue. If pointers are stored, contents should be manually dequeued and deleted if necessary
 */
template <typename T>
Queue<T>::~Queue()
{
    while (head != nullptr)
    {
        Dequeue();
    }
}

/**
 * \brief Adds an item to the end of the queue
 * \param item Item to add
 */
template <typename T>
void Queue<T>::Enqueue(T item)
{
    auto node = new Node<T>(item);
    if( tail != nullptr)
    {
        tail->next = node;
    }
    tail = node;
    if (head == nullptr)
    {
        head = node;
    }
    ++count;
}


/**
 * \brief Returns and removes the item at the front of the queue. Throws an error is the queue is empty
 * \return Item at the front of the queue
 */
template <typename T>
T Queue<T>::Dequeue()
{
    if (head == nullptr)
    {
        throw std::out_of_range("Queue is empty but tried to dequeue");
    }
    auto node = head->next;
    auto item = head->item;
    delete head;
    head = node;
    --count;
    return item;
    
}


/**
 * \brief Returns a constant reference of the front of the queue without removing it
 * \return Constant Reference to item at the front of the queue
 */
template <typename T>
const T& Queue<T>::Peek()
{
    if (head == nullptr)
    {
        throw std::out_of_range("Queue is empty but tried to dequeue");
    }
    
    return head->item;
}

