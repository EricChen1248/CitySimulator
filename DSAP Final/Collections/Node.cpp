#include "Node.h"

template <typename T>
Node<T>::Node(T item, Node<T>* last, Node<T>* next)
{
    this->item = item;
    this->last = last;
    this->next = next;
}