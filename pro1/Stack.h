#pragma once
#include "Error.h"
#define STACK_INIT_SIZE 1000
#define STACK_INCREMENT 50

//自定义栈
template <typename T>
class Stack
{
public:

    T* top;
    T* base;
    int stacksize;
public:
    Stack()
    {
        base = (T *)malloc(STACK_INIT_SIZE * sizeof(T));
        top = base;
        stacksize = STACK_INIT_SIZE;
    }

    void push(T data);

    T pop();

    T* gettop();

    int size();

    bool is_empty();
};

template <class T>
void Stack<T>::push(T data)
{
    if (top - base >= stacksize)
    {
        base = (T *)realloc(base, (stacksize + STACK_INCREMENT) * sizeof(T));
        if (!base)
        {
            throw Error(STACK_MEMORY_OVERFLOW);
        }
        top = base + stacksize;
        stacksize += STACK_INCREMENT;
    }

    *top++ = data;
}

template <class T>
T Stack<T>::pop()
{
    if (top == base)
    {
        throw Error(STACK_EMPTY);
    }

    return *--top;
}

template <class T>
T* Stack<T>::gettop()
{
    if (top == base)
    {
        throw Error(STACK_EMPTY);
    }
    return (top - 1);
}

template <class T>
bool Stack<T>::is_empty()
{
    return top == base;
}

template <class T>
int Stack<T>::size()
{
    return top - base;
}
