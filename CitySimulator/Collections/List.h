#pragma once
#include "Interfaces/IList.h"
#include "ListIterator.h"

template<typename T>
class List : IList<T>
{
public:
    List(int initialSize = INITIAL_SIZE);
    ~List();
    T& operator[](int index) const override;
    void InsertLast(const T& item) override;
    void RemoveLast() override;
    void Remove(int index) override;
    void Remove(const T& item) override;
    void Dispose();
    const int& Count() const override { return itemCount; };
    
    // ReSharper disable once CppInconsistentNaming : name matching required for range based for loops
    ListIterator<T> begin() const { return ListIterator<T>(array); };
    // ReSharper disable once CppInconsistentNaming : name matching required for range based for loops
    ListIterator<T> end() const { return ListIterator<T>(&(array[itemCount])); };
    
private:
    const static int INITIAL_SIZE = 32;
    T* array;
    int arraySize;
    int itemCount;
};

template <typename T>
List<T>::List(const int initialSize /* = INITIAL_SIZE */)
{
    array = new T[initialSize];
    arraySize = initialSize;
    itemCount = 0;
}

template <typename T>
List<T>::~List()
{
    delete [] array;
}

template <typename T>
T& List<T>::operator[](const int index) const
{
    return array[index];
}

template <typename T>
void List<T>::InsertLast(const T& item)
{
    // Expand array if size not big enough
    if (itemCount == arraySize)
    {
        arraySize *= 2;
        T* temp = new T[arraySize];
        for (int i = 0; i < itemCount; ++i)
        {
            temp[i] = array[i];
        }
        delete [] array;
        array = temp;
    }
    array[itemCount++] = item;
}

template <typename T>
void List<T>::RemoveLast()
{
    --itemCount;
}

template <typename T>
void List<T>::Remove(const int index)
{
    for (int i = index + 1; i < itemCount; ++i)
    {
        array[i - 1] = array[i];
    }
    --itemCount;
}

template <typename T>
void List<T>::Remove(const T& item)
{
    for (int i = 0; i < itemCount; ++i)
    {
        if (array[i] == item)
        {
            Remove(i);
            return;
        }
    }
}

template <typename T>
void List<T>::Dispose()
{
    for (int i = 0; i < itemCount; ++i)
    {
        delete array[i];
    }
}
