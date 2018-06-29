#pragma once
#include "Node.h"

/**
 * \brief Helper class that provides iteration functions for custom collections
 * \tparam T Type of item that will be use with the class 
 */
template<typename T>
class LinkedIterator
{
public:
    LinkedIterator(Node<T>& node) noexcept;
    LinkedIterator() noexcept;
    void operator++();
    bool operator!=(LinkedIterator<T>& other);
    const T& operator*();
private:
    Node<T>* node;
    
};

/**
 * \brief Used to generate the iterator for Begin()
 * \param node The "begin" / first node in the collection
 */
template <typename T>
LinkedIterator<T>::LinkedIterator(Node<T>& node) noexcept
{
    this->node = &node;
}

/**
 * \brief Used to generate the end iterator
 */
template <typename T>
LinkedIterator<T>::LinkedIterator() noexcept
{
    node = nullptr;
}

/**
 * \brief Advances the iterator to the next iter
 */
template <typename T>
void LinkedIterator<T>::operator++()
{
    node = node->next;
}

/**
 * \brief Used for comparing to end iter (node will be nullptr)
 * \param other Other iterator to compare to
 * \return False if address of node is different
 */
template <typename T>
bool LinkedIterator<T>::operator!=(LinkedIterator<T>& other)
{
    return node != other.node;
}

/**
 * \brief Dereferencing returns the item in the node for each in range-based loops
 * \return The item stored in the node
 */
template <typename T>
const T& LinkedIterator<T>::operator*()
{
    return node->item;
}
