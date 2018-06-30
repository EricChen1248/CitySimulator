#pragma once

/**
 * \brief Helper class used in linked-based collections for storing items. Uses double link method.
 * \tparam T Type of item to be stored
 */
template <typename T>
class Node
{
    template <typename IteratorType>
    friend class LinkedIterator;
    template <typename ListType>
    friend class LinkedList;
    template <typename QueueType>
    friend class Queue;
    template <class QueueType>
    friend class PriorityQueue;
    template <typename StackType>
    friend class Stack;
    
    bool operator!=(Node<T>& other) { return this != &other; }
    Node<T> operator++() { return this->next; }
    
protected:
    /**
     * \brief Creates a new node used in collections that stores an item part of a doubly linked list
     * \param item Item to store
     * \param prev (Default nullptr) pointer to previous node
     * \param next (Default nullptr) pointer to next node
     */
    Node(T item, Node<T>* prev = nullptr, Node<T>* next = nullptr);
    ~Node() = default;
    
    T item;
    Node<T>* next;
    Node<T>* prev;
};

template <typename T>
Node<T>::Node(T item, Node<T>* prev, Node<T>* next)
{
    this->item = item;
    this->prev = prev;
    this->next = next;
}