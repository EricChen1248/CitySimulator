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
bool MaxHeap<T>::Add(const T& item)
{
    auto currentLevel = levels[levelCount];
    int levelIndex = levelCount;
    if(currentLevel->Add(item))
    {
        levels.InsertLast(new HeapLevel<T>(++levelCount));   
    }
    
    int index = currentLevel->itemCount - 1;
    bool inPlace = false;
    while (levelIndex > 0 && !inPlace)
    {
        int parentIndex = (index - 1) / 2;
        auto parentLevel = levels[--levelIndex];
        if (parentLevel[parentIndex] <= currentLevel[index])
        {
            inPlace = true;
            continue;
        }
        
        std::swap(parentLevel[parentIndex], currentLevel[index]);
        index = parentIndex;
        currentLevel = parentLevel;
    }
    
    ++itemCount;
    return true;
}

template <typename T>
bool MaxHeap<T>::RemoveTop()
{
    if (IsEmpty())
    {
        return false;
    }
    
    auto & lastLevel = levels[levelCount];
    levels[0] = lastLevel.items[lastLevel.itemCount];
    
    Rebuild(0,0);
    return true;
}

template <typename T>
void MaxHeap<T>::Clear()
{
    levels.Dispose();
}

template <typename T>
void MaxHeap<T>::Rebuild(const int rootLevel, const int rootIndex)
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
                std::swap(currentLevel[rootIndex], nextLevel[largerChild]);
                Rebuild(rootLevel + 1, largerChild);
            }
        }         
    }
}




