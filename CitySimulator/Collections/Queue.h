#pragma once
#include "Node.h"
#include <stdexcept>

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

template <typename T>
Queue<T>::~Queue()
{
    while (head != nullptr)
    {
        Dequeue();
    }
}

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

template <typename T>
const T& Queue<T>::Peek()
{
    if (head == nullptr)
    {
        throw std::out_of_range("Queue is empty but tried to dequeue");
    }
    
    return head->item;
}

