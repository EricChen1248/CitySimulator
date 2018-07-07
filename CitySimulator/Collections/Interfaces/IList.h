#pragma once


/**
 * \brief Interface for a list collection
 * \tparam T type of item being store
 */
template<typename T>
class IList
{
public:
    virtual ~IList() = default;
    virtual T& operator[](int index) const = 0;
    virtual void InsertLast(const T& item) = 0;
    virtual void RemoveLast() = 0;
    virtual void Remove(int index) = 0;
    virtual void Remove(const T& item) = 0;
    virtual const int& Count() const = 0;
};