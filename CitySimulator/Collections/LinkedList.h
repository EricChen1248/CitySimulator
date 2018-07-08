#pragma once
#include "Node.h"
#include <stdexcept>
#include <sstream>

#include "../Helpers/CustomExceptions.h"
#include "LinkedIterator.h"
#include "Interfaces/IList.h"

/**
 * \brief An unlimited, ordered collection that uses link-based memory backing.
 * \tparam T type of item being stored
 */
template <typename T>
class LinkedList : public IList<T>
{
public:
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();
    T& operator[](int index) const;
    void InsertLast(const T& item);
    void RemoveLast();
    void Remove(int index);
    void Remove(const T& item);
    void Dispose();
    const int& Count() const  { return count; }
    // ReSharper disable once CppInconsistentNaming : name matching required for range based for loops
    LinkedIterator<T> begin() const { return LinkedIterator<T>(*first); };
    // ReSharper disable once CppInconsistentNaming : name matching required for range based for loops
    LinkedIterator<T> end() const { return LinkedIterator<T>(); };
    
protected:
    Node<T>* first;
    Node<T>* last;
    int count;
    
};


template <typename T>
LinkedList<T>::LinkedList()
{
    first = nullptr;
    last = nullptr;
    count = 0;

}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList()
{
    for (auto && item : other)
    {
        InsertLast(item);   
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    auto nextNode = first;
    while (nextNode != nullptr)
    {
        auto temp = nextNode->next;
        delete nextNode;
        nextNode = temp;
    }
}

/**
 * \brief Returns the item located at an index of a LinkedList. Cached lookup speeds up consecutive lookups
 * \param index Index of item in LinkedList
 * \return Item at index of type T
 */
template <typename T>
T& LinkedList<T>::operator[](const int index) const
{
    if (index < 0 || index >= count)
    {
        std::stringstream ss;
        ss << "Index: " << index << " is out of range of LinkedList in " << __FILE__ << "at line: " << __LINE__;
        throw std::out_of_range(ss.str());
    }
    
    if (index == 0)
        return first->item;
    if (index == count - 1)
        return last->item;

    const int toFirst = index;
    const int toLast = count - index - 1;

    auto node = first;
    int dir = 1;
    int currentIndex = 0;
    if (toLast < toFirst)
    {
        node = last;
        dir = -1;
        currentIndex = count - 1;
    }

    while (currentIndex != index)
    {
        switch (dir)
        {
        case 1:
            node = node->next;
            break;
        case -1:
            node = node->prev;
            break;
        default:
            throw CodingError("This should not happen, error at " + std::string(__FILE__) + " at line: " + std::to_string(__LINE__));
        }
        currentIndex += dir;
    }

    return node->item;
}

/**
 * \brief Inserts an item to the end of the LinkedList
 * \param item Item to insert
 */
template <typename T>
void LinkedList<T>::InsertLast(const T& item)
{
    Node<T>* node = new Node<T>(item);
    if (first == nullptr)
    {
        first = node;
    }
    if (last != nullptr)
    {
        last->next = node;
    }
    node->prev = last;
    last = node;
    ++count;
}

/**
 * \brief Removes the last item in the LinkedList
 */
template <typename T>
void LinkedList<T>::RemoveLast()
{
    auto node = last->prev;
    delete last;
    last = node;
    if (node == nullptr)
    {
        first = nullptr;
    }
    else
    {
        node->next = nullptr;
    }
    --count;
}

/**
 * \brief Removes an item from the LinkedList based on index
 * \param index Index of item to remove
 */
template <typename T>
void LinkedList<T>::Remove(const int index)
{
    if (index < 0 || index >= count)
    {
        std::stringstream ss;
        ss << "Index: " << index << " is out of range of LinkedList in " << __FILE__ << "at line: " << __LINE__;
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
    else
    {
        const int toFirst = index;
        const int toLast = count - index - 1;

        auto node = first;
        int dir = 1;
        int currentIndex = 0;
        if (toLast < toFirst)
        {
            node = last;
            dir = -1;
            currentIndex = count - 1;
        }
        // Traversing indexes
        while (currentIndex != index)
        {
            switch (dir)
            {
            case 1:
                node = node->next;
                break;
            case -1:
                node = node->prev;
                break;
            default:
                throw CodingError("This should not happen");
            }
            currentIndex += dir;
        }
        curNode = node;
    }
    
    auto next = curNode->next;
    auto prev = curNode->prev;

    if (next == nullptr)
    {
        last = prev;
    }
    else
    {
        next->prev = prev;
    }
    if (prev == nullptr)
    {
        first = next;
    }
    else
    {
        prev->next = next;
    }
    delete curNode;
    --count;
}

/**
 * \brief Removes the first item that returns true with operator==
 * \param item Item to remove
 */
template <typename T>
void LinkedList<T>::Remove(const T& item)
{
    auto node = first;
    while (node != nullptr)
    {
        if (node->item == item)
        {
            if(node->prev != nullptr)
            {
                node->prev->next = node->next;
            }
            else
            {
                first = node->next;
            }
            if (node->next != nullptr)
            {
                node->next->prev = node->prev;
            }
            else
            {
                last = node->prev;
            }
            delete node;
            --count;
            return;
        }
        node = node->next;
    }
}

/**
 * \brief Interface to delete pointer if stored item is a pointer
 */
template <typename T>
void LinkedList<T>::Dispose()
{
    auto node = first;
    while(node != nullptr)
    {
        auto temp = node->next;
        delete node->item;
        node = temp;
    }
}
