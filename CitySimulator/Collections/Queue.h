#pragma once
#include <stdexcept>

/**
 * \brief Stores an item based on FIFO process
 * \tparam T Type of item being stored in queue
 */
template<typename T>
class Queue
{
public:
    Queue(int initialSize = DEFAULT_MAX);
    ~Queue();
    void Enqueue(T& item);
    void Dequeue();
    T& Peek() const;
    bool IsEmpty() const { return itemCount == 0; }
    int Count() const { return itemCount; };
protected:
    static const int DEFAULT_MAX = 128;
    T* array;
    int itemCount;
    int front;
    int back;
    int currentMax;
};


template <typename T>
Queue<T>::Queue(const int initialSize /* = DEFAULT_MAX */): itemCount(0), front(0), back(0), currentMax(initialSize)
{
    array = new T[initialSize];
}

/** 
 * \brief Cleans up memory used by the queue. If pointers are stored, contents should be manually dequeued and deleted if necessary 
 */
template <typename T>
Queue<T>::~Queue()
{
    delete array[];
}

/** 
 * \brief  Adds a new item to the queue;
 * \param  item: Item to add
 */ 
template <typename T>
void Queue<T>::Enqueue(T& item)
{
    // Expand if full
    if (itemCount == currentMax)
    {
        T* temp = new T[currentMax * 2];
        for (int i = 0; i < itemCount; ++i)
        {
            temp[i] = array[(front + i) % currentMax];
        }
        front = 0;
        back = itemCount;
        delete [] array;
        array = temp;
        currentMax *= 2;
    }
    
    // Add item to array
    array[back] = item;
    ++itemCount;
    
    // Increment and wrap around back of queue
    back = (back + 1) % currentMax;
}
/** 
 * \brief Returns and removes the item at the front of the queue. Throws an error is the queue is empty 
 * \return Item at the front of the queue 
 */ 
template <typename T>
void Queue<T>::Dequeue()
{
    if (itemCount == 0)
        throw std::out_of_range("Queue was dequeued but is empty");
    
    front = (front + 1) % currentMax;
    --itemCount;
}

/** 
 * \brief Returns a constant reference of the front of the queue without removing it 
 * \return Constant Reference to item at the front of the queue 
 */ 
template <typename T>
T& Queue<T>::Peek() const
{
    if (itemCount == 0)
        throw std::out_of_range("Queue was peeked but is empty");
    return array[front];
}


