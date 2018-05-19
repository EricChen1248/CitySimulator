#include "List.h"
#include <cmath>
#include <stdexcept>
#include <sstream>
#include "../System/CustomExceptions.h"

template <typename T>
List<T>::List()
{
    first = nullptr;
    last = nullptr;
    count = 0;

    cachedIndex = -1;
    cachedNode = nullptr;
}

template <typename T>
List<T>::~List()
{
    auto nextNode = first;
    while (nextNode != nullptr)
    {
        auto temp = nextNode.next;
        delete nextNode;
        nextNode = temp;
    }
}

/**
 * \brief Returns the item located at an index of a list. Cached lookup speeds up consecutive lookups
 * \param index Index of item in list
 * \return Item at index of type T
 */
template <typename T>
T List<T>::operator[](const int index)
{
    if (index < 0 || index >= count)
    {
        std::stringstream ss;
        ss << "Index: " << index << " is out of range of list";
        throw std::out_of_range(ss.str());
    }
    
    if (index == 0)
        return first->item;
    if (index == count - 1)
        return last->item;
    if (index == cachedIndex)
        return last->item;

    const int toFirst = index;
    const int toLast = count - index - 1;
    const int toCache = abs(index - cachedIndex);

    auto node = first;
    int dir = 1;
    int currentIndex = 0;
    if (toLast < toFirst && toLast <= toCache)
    {
        node = last;
        dir = -1;
        currentIndex = count - 1;
    }
    else if (toCache < toFirst && toCache < toLast)
    {
        node = cachedNode;
        dir = index > cachedIndex ? 1 : -1;
        currentIndex = cachedIndex;
    }

    while (currentIndex != index)
    {
        switch (dir)
        {
        case 1:
            node = node.next;
            break;
        case -1:
            node = node.last;
            break;
        default:
            throw CodingError("This should not happen");
        }
    }

    cachedIndex = currentIndex;
    cachedNode = node;
    return node.item;
}

template <typename T>
void List<T>::Remove(const int index)
{
    if (index < 0 || index >= count)
    {
        std::stringstream ss;
        ss << "Index: " << index << " is out of range of list";
        throw std::out_of_range(ss.str());
    }
    
    Node<T>* curNode;
    if (index == 0)
    {
        curNode = first;
    }
    else if (index == count - 1)
    {
        curNode = last;
    }
    else if (index == cachedIndex)
    {
        curNode = cachedNode;
    }
    else
    {
        // Calculating distances from cached positions
        const int toFirst = index;
        const int toLast = count - index - 1;
        const int toCache = abs(index - cachedIndex);

        auto node = first;
        int dir = 1;
        int currentIndex = 0;
        if (toLast < toFirst && toLast <= toCache)
        {
            node = last;
            dir = -1;
            currentIndex = count - 1;
        }
        else if (toCache < toFirst && toCache < toLast)
        {
            node = cachedNode;
            dir = index > cachedIndex ? 1 : -1;
            currentIndex = cachedIndex;
        }

        // Traversing indexes
        while (currentIndex != index)
        {
            switch (dir)
            {
            case 1:
                node = node.next;
                break;
            case -1:
                node = node.last;
                break;
            default:
                throw CodingError("This should not happen");
            }
        }
        curNode = node;
    }
    
    auto next = curNode->next;
    auto prev = curNode->last;
    
    next.last = prev;
    prev.next = next;
    delete curNode;
}
