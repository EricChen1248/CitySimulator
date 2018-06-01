#pragma once
#include "Node.h"

template<typename T>
class Iterator
{
public:
    Iterator(Node<T>& node);
    Iterator();
    void operator++();
    bool operator!=(Iterator<T>& other);
    T& operator*();
private:
    Node<T>* node;
    
};

template <typename T>
Iterator<T>::Iterator(Node<T>& node)
{
    this->node = &node;
}

template <typename T>
Iterator<T>::Iterator()
{
    node = nullptr;
}

template <typename T>
void Iterator<T>::operator++()
{
    node = node->next;
}

template <typename T>
bool Iterator<T>::operator!=(Iterator<T>& other)
{
    return node != other.node;
}

template <typename T>
T& Iterator<T>::operator*()
{
    return node->item;
}
