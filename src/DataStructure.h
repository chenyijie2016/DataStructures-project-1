//
// Created by cyj on 2017/10/24.
//

#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

#include <iostream>

namespace MyDataStructure
{
    //可能出现的错误
    enum ERROR
    {
        NO_ERROR,
        STACK_MEMORY_OVERFLOW,
        STACK_EMPTY,
        STRING_OVERFLOW

    };


#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 50

    //自定义栈
    template<class T>
    class stack
    {
    public:
        stack()
        {
            base = (T *)malloc(STACK_INIT_SIZE * sizeof(T));
            top = base;
            stacksize = STACK_INIT_SIZE;
        }

        //Data field
        T *top;
        T *base;
        int stacksize;

        // Method
        void push(T data);

        T pop();

        T gettop();

        bool is_empty();
    };

    template<class T>
    void stack<T>::push(T data)
    {
        if (top - base >= stacksize)
        {
            base = (T *)realloc(base, (stacksize + STACK_INCREMENT) * sizeof(T));
            if (!base)
            {
                throw STACK_MEMORY_OVERFLOW;
            }
            top = base + stacksize;
            stacksize += STACK_INCREMENT;
        }

        *top = data;
    }

    template<class T>
    T stack<T>::pop()
    {
        if (top == base)
        {
            throw STACK_EMPTY;
        }
        auto e = *--top;
        return e;
    }

    template<class T>
    T stack<T>::gettop()
    {
        if (top == base)
        {
            throw STACK_EMPTY;
        }
        return *top;
    }

    template<class T>
    bool stack<T>::is_empty()
    {
        return top == base;
    }

    //自定义字符串
    class String
    {
    public:
        wchar_t *ch;
        int length;
        String() = default;

        explicit String(wchar_t *ch);

        explicit String(std::string);

        wchar_t &operator[](int index);

        //friend bool operator==(String &s1, String &s2);
    };
};

#endif //_DATASTRUCTURE_H
