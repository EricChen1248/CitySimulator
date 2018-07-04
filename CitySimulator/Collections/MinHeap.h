#pragma once

template<typename T>
T* DeRef(T& item) noexcept 
{
    return &item;
}
template<typename T>
T* DeRef(T* item) noexcept
{
    return item;
}

/** 
 * @brief  Heap implementation that uses operator> to compare 
 */
template <typename T>
class MinHeap
{
  public:
    MinHeap(const int initialSize = 31) noexcept;
    ~MinHeap() noexcept;
    /** 
     * @brief  Returns the item count in the heap
     * @retval int type item count
     */
    int ItemCount() const noexcept { return itemCount; }
    void Add(T &item) noexcept;
    /** 
     * @brief  Returns an item reference to the item at the top of the heap
     * @retval Reference of item at the top of the heap
     */
    const T &PeekTop() const { return array[0]; } 
    void RemoveTop();
    
    /**
     * \brief Efficient reset that sets itemCount to 0 for reuse of Heap
     */
    void Reset() { itemCount = 0; };

  private:
    static int ParentIndex(const int index) noexcept { return (index - 1) / 2; };
    static int LeftChildIndex(const int index) noexcept { return index * 2 + 1; };
    static int RightChildIndex(const int index) noexcept { return index * 2 + 2; };
    
    int itemCount;
    int maxSize;
    T *array;
};

template <typename T>
MinHeap<T>::MinHeap(const int initialSize) noexcept : itemCount(0), maxSize(initialSize)
{
    array = new T[maxSize];
}

template <typename T>
MinHeap<T>::~MinHeap() noexcept
{
    delete[] array;
}

/** 
 * @brief  Inserts a new item into the heap and sorts it
 * @note   Item must support operator>
 * @param  item: Item being inserted
 */
template <typename T>
void MinHeap<T>::Add(T &item) noexcept
{
    // Increase heap size if no big enough
    if (itemCount == maxSize)
    {
        maxSize = (maxSize + 1) * 2 - 1;
        T *newArray = new T[maxSize];

        for (int i = 0; i < itemCount; ++i)
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }

    int index = itemCount++;
    // While item is not root
    while (index > 0)
    {
        const int parentIndex = ParentIndex(index);

        // Swap child and parent if child is larger
        if (*DeRef(item) < *DeRef(array[parentIndex]))
        {
            array[index] = array[parentIndex];
            index = parentIndex;
            continue;
        }
        // Child is smaller and loop can end
        break;
    }
    array[index] = item;
}

/** 
 * @brief  Removes the item at the top of the heap and resorts it
 * @note   Item must support operator>
 */
template <typename T>
void MinHeap<T>::RemoveTop()
{
    int index = 0;
    T temp = array[--itemCount];
    while (index < itemCount)
    {
        int largerChild = LeftChildIndex(index);
        // Left child doesn't exist
        if (largerChild >= itemCount)
        {
            break;
        }
        // Check if right child is larger
        const int right = RightChildIndex(index);
        if (right < itemCount)
        {
            if (*DeRef(array[right]) < *DeRef(array[largerChild]))
            {
                largerChild = right;
            }
        }
        // Compare temp to larger child
        if (*DeRef(array[largerChild]) < *DeRef(temp))
        {
            array[index] = array[largerChild];
            index = largerChild;
            continue;
        }
        break;
    }
    array[index] = temp;
}