#pragma once
#include "Node.h"

/**
 * \brief An unlimited, ordered collection that uses link-based memory backing.
 *        Last lookup location is cached to improve subsequenct consecutive lookups.
 * \tparam T 
 */
template <typename T>
class List
{
public:
    List();
    ~List();
    T operator[](int index);
    void Remove(int index);
    void Remove(T& item);
    
protected:
    Node<T>* first;
    Node<T>* last;
    int count;
    
private:
    int cachedIndex;
    Node<T>* cachedNode;
};

