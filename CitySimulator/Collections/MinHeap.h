#pragma once
#include "List.h"
#include "HeapLevel.h"

template<typename T>
class MinHeap
{
public:
    MinHeap();
    virtual ~MinHeap();
    
    bool IsEmpty() const { return itemCount == 0; };
    int Count() const { return itemCount; };
    int Height() const { return lastLevel; };
    T& PeekTop() const;
    bool Add(const T& item);
    bool Update(const T& item);
    bool RemoveTop();
    void Clear();
    
private:
    List<HeapLevel<T>*> levels;
    
    int lastLevel;
    int itemCount;
    
    void Rebuild(int rootLevel, int rootIndex);
    int FindLevel(T& item, int levelN, int index) const;
    void ShiftUp(int rootLevel, int rootIndex);
};

template <typename T>
MinHeap<T>::MinHeap(): lastLevel(0), itemCount(0)
{
    auto level = new HeapLevel<T>(0);
    levels.InsertLast(level);
}

template <typename T>
MinHeap<T>::~MinHeap()
{
    for (auto && level : levels)
    {
        delete level;
    }
}

template <typename T>
T& MinHeap<T>::PeekTop() const
{
    if (IsEmpty())
    {
        throw std::out_of_range("Heap is currently empty");
    }
    return levels[0]->items[0];
}

template <typename T>
bool MinHeap<T>::Add(const T& item)
{
    // Point to last level
    HeapLevel<T>* currentLevel = levels[lastLevel];
    
    // If last level is currently full, add new level
    if (currentLevel->IsFull())
    {
        lastLevel++;
        currentLevel = new HeapLevel<T>(lastLevel);
        levels.InsertLast(currentLevel);
    }
    
    // Index item will have in level
    int index = currentLevel->itemCount;
    // Add item to last level
    auto temp = item;
    currentLevel->Add(temp);
    ++itemCount;
    
    // while is not at the top of the heap
    while (currentLevel->level > 0)
    {
        int parentIndex = index / 2;
        auto parentLevel = levels[currentLevel->level - 1];
        if (*(*parentLevel)[parentIndex] <= *(*currentLevel)[index])
        {
            return true;
        }
        
        std::swap((*parentLevel)[parentIndex], (*currentLevel)[index]);
        
        index = parentIndex;
        currentLevel = parentLevel;
    }
    
    return true;
}

template <typename T>
bool MinHeap<T>::Update(const T& item)
{
    auto t = item;
    const int levelNo = FindLevel(t, 0, 0);
    if (levelNo == -1)
    {
        return false;
    }
    
    auto& level = *levels[levelNo];
    int index;
    for (index = 0; index < level.itemCount; ++index)
    {
        if (level[index] == item)
        {
            break;
        }
    }
    ShiftUp(levelNo, index);
    
    return Add(t);
}

template <typename T>
bool MinHeap<T>::RemoveTop()
{
    if (IsEmpty())
    {
        return false;
    }
    
    HeapLevel<T>* level = levels[lastLevel];
    // Replace top with last level's last item
    (*levels[0])[0] = (*level)[level->itemCount - 1];
    --level->itemCount;
    if (level->itemCount == 0)
    {
        levels.RemoveLast();
        --lastLevel;
    }
    Rebuild(0, 0);
    
    return true;
}

template <typename T>
void MinHeap<T>::Clear()
{
    levels.Dispose();
}

template <typename T>
void MinHeap<T>::Rebuild(const int rootLevel, const int rootIndex)
{
    // Is not last level
    if (lastLevel > rootLevel)
    {
        auto currentLevel = levels[rootLevel];
        auto nextLevel = levels[rootLevel + 1];
        
        const int left = rootIndex * 2;
        // Has left child
        if (nextLevel->itemCount > left)
        {
            int smallerChild = left;
            const int right = left + 1;
            // Has right child
            if (nextLevel->itemCount > right)
            {
                if ((*nextLevel)[smallerChild] > (*nextLevel)[right] )
                {
                    smallerChild = right;
                }
            }

            if (*(*nextLevel)[smallerChild] < *(*currentLevel)[rootIndex])
            {
                std::swap((*currentLevel)[rootIndex], (*nextLevel)[smallerChild]);
                Rebuild(rootLevel + 1, smallerChild);
            }
        }         
    }
}

template <typename T>
int MinHeap<T>::FindLevel(T& item, const int levelN, const int index) const
{
    if (levels.Count() > levelN + 1)
    {
        auto & level = *levels[levelN + 1];
        const int left = index * 2;
        if (level.itemCount > left)
        {
            if (level[left] == item)
            {
                return levelN + 1;
            }
            if (level[left] < item)
            {
                const int found = FindLevel(item, levelN + 1, left);
                if (found != -1)
                {
                    return found;
                }
            }
        }

        const int right = left + 1;
        if (level.itemCount > right)
        {
            if (level[right] != item)
            {
                return levelN + 1;
            }
        
            if (level[right] < item)
            {
                return FindLevel(item, levelN + 1, right);
            }
        }
    }
    return -1;
}

template <typename T>
void MinHeap<T>::ShiftUp(const int rootLevel, const int rootIndex)
{
    if (levels.Count() > rootLevel + 1)
    {
        auto& nextLevel = *levels[rootLevel + 1];
        const int left = rootIndex * 2;
        // Has left child
        if (nextLevel.itemCount > left)
        {
            int smallerChild = left;
            const int right = left + 1;
            // Has right child
            if (nextLevel.itemCount > right)
            {
                if (nextLevel[smallerChild] > nextLevel[right] )
                {
                    smallerChild = right;
                }
            }
            auto& currentLevel = *levels[rootLevel];
            currentLevel[rootIndex] = nextLevel[smallerChild];
            ShiftUp(rootLevel + 1, smallerChild);
        }    
    }
}



