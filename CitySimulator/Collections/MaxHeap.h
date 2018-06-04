#pragma once
#include "List.h"
#include "HeapLevel.h"

template<typename T>
class MaxHeap
{
public:
    MaxHeap();
    ~MaxHeap();
    
    bool IsEmpty() const { return itemCount == 0; };
    int Count() const { return itemCount; };
    int Height() const { return levelCount; };
    T& PeekTop() const;
    bool Add(const T& item);
    bool RemoveTop();
    void Clear();
    
private:
    List<HeapLevel<T>*> levels;
    
    int levelCount;
    int itemCount;
    
    void Rebuild(int rootLevel, int rootIndex);
};

template <typename T>
MaxHeap<T>::MaxHeap(): levelCount(0), itemCount(0)
{
    levels.InsertLast(new HeapLevel<T>(0));
}

template <typename T>
MaxHeap<T>::~MaxHeap()
{
    for (auto && level : levels)
    {
        delete level;
    }
}

template <typename T>
T& MaxHeap<T>::PeekTop() const
{
    if (IsEmpty())
    {
        throw std::out_of_range("Heap is currently empty");
    }
    return levels[0].items[0];
}

template <typename T>
bool MaxHeap<T>::RemoveTop()
{
    auto & lastLevel = levels[levelCount];
    levels[0].items[0] = lastLevel.items[lastLevel.itemCount];
}

template <typename T>
void MaxHeap<T>::Rebuild(int rootLevel, int rootIndex)
{
    auto& currentLevel = levels[rootLevel];
    if (levels.Count() > rootLevel)
    {
        auto & nextLevel = levels[rootLevel + 1];
        // Is not leaf
        
        if (nextLevel[rootIndex * 2] != NULL)
        {
            int largerChild = rootIndex * 2;
            const int right = rootIndex * 2 + 1;
            if (nextLevel[right] != NULL)
            {
                if (nextLevel[right] > nextLevel[largerChild])
                {
                    largerChild = right;
                }
            }

            if (currentLevel[rootIndex] < nextLevel[largerChild])
            {
                
            }
        }
    {
         
    }
}




