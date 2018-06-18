#pragma once
#include <cmath>

template<typename T>
struct HeapLevel
{
    template<typename HeapType>
    friend class MinHeap;
    
    ~HeapLevel()
    {
        delete [] items;
    }
private:
    int level;
    int itemCount;
    int maxCount;
    
    T* items;
    T& operator[](const int index) { return items[index]; }
    HeapLevel(const int level) : level(level), itemCount(0)
    {
        maxCount = int(pow<int>(2, level));
        
        items = new T[maxCount];
    }
    
    bool Add(T& item)
    {
        items[itemCount++] = item;
        return itemCount == maxCount;
    }
    
    bool IsFull() const
    {
        return itemCount == maxCount;
    }
};
