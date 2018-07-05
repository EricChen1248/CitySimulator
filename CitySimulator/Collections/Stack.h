#pragma once

#include "Node.h"
#include <stdexcept>

/**
 * \brief Stores items based on LIFO.
 * \tparam T Item type to store in the Stack
 */
template <typename T>
class Stack
{
  public:
    ~Stack() noexcept;
    void Push(const T& item) noexcept;
    T Pop();
    const T &Peek();
    int Count() const noexcept;
    bool IsEmpty() const noexcept;

  private:
    int count = 0;
    Node<T> *top = nullptr;
};

/** 
 * \brief  Deconstructs the stack and takes care of DMA
 * \note   If stack contains pointer to objects, user must handle them manually
 */
template <typename T>
Stack<T>::~Stack() noexcept
{
    for (int i = 0; i < count; ++i)
    {
        Pop();
    }
}

/** 
 * \brief  Pushes a new item to the top of the stack
 * \note   Item is copied by reference value. Pass in pointers for original object storage or large classes
 * \param  item: Item being pushed
 * \retval None
 */
template <typename T>
void Stack<T>::Push(const T& item) noexcept
{
    Node<T> *node = new Node<T>(item, top);
    top = node;
    ++count;
}

/** 
 * \brief  Removes and returns the item at the top of the stack
 * \note   Throws out of range if stack is empty
 * \retval Item at the top of the stack
 */
template <typename T>
T Stack<T>::Pop()
{
    if (count == 0)
    {
        throw std::out_of_range("Stack is empty");
    }
    
    T item = top->item;
    Node<T> *node = top->prev;
    delete top;
    top = node;
    --count;
    return item;
}

/** 
 * \brief  Returns a reference of the item at the top of the stack
 * \note   Throws out of range error is stack is empty
 * \retval Reference to the item at the top of the stack
 */
template <typename T>
const T &Stack<T>::Peek()
{
    if (top == nullptr)
        throw std::out_of_range("Stack is empty");
    return top->item;
}

/** 
 * \brief  Returns a the item count of the stack
 * \retval Integer value of stack item count
 */
template <typename T>
int Stack<T>::Count() const noexcept
{
    return count;
}

/** 
 * \brief  Returns if the stack is empty
 * \retval True if is empty, otherwise false
 */
template <typename T>
bool Stack<T>::IsEmpty() const noexcept
{
    return count == 0;
}
