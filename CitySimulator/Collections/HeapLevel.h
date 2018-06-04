#pragma once
#include <cmath>

template<typename T>
class MaxHeap<T>;

template<typename T>
struct HeapLevel
{
    template<typename HeapType>
    friend class MaxHeap<HeapType>;
private:
    int level;
    int itemCount;
    int maxCount;
    
    T* items;
    
    HeapLevel(const int level) : level(level), itemCount(0)
    {
        maxCount = pow(2, level);
        
        items = new T[maxCount];
        for (int i = 0; i < maxCount; i++)
        {
            items[i] = NULL;
        }
    };
    ~HeapLevel()
    {
        delete [] items;
    }
};
