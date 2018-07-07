#pragma once

/**
 * \brief Helper class that provides iteration functions for array-based collections
 * \tparam T Type of item that will be use with the class 
 */
template<typename T>
class ListIterator
{
public:

/**
    * \brief Used to generate the iterator for Begin()
    * \param item The "begin" / first item in the collection
*/
    ListIterator(T* item) noexcept: item(item) {};
    void operator++();
    bool operator!=(ListIterator<T>& other);
    const T& operator*();
private:
    T* item;
    
};

/**
 * \brief Advances the iterator to the next iter
 */
template <typename T>
void ListIterator<T>::operator++()
{
    ++item;
}

/**
 * \brief Used for comparing to end iter (node will be nullptr)
 * \param other Other iterator to compare to
 * \return False if address of node is different
 */
template <typename T>
bool ListIterator<T>::operator!=(ListIterator<T>& other)
{
    return item != other.item;
}

/**
 * \brief Dereferencing returns the item in the node for each in range-based loops
 * \return The item stored in the node
 */
template <typename T>
const T& ListIterator<T>::operator*()
{
    return *item;
}
