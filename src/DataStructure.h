//
// Created by cyj on 2017/10/24.
//

#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

#include <iostream>

namespace MyDataStructure
{
    typedef wchar_t c;

    //可能出现的错误
    enum ERROR
    {
        NO_ERROR,
        STACK_MEMORY_OVERFLOW,
        STACK_EMPTY,
        STRING_OVERFLOW,
        SUBSTRING_ERROR,
        SUBSTRING_OVER_LENGTH,
    };


#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 50

    //自定义栈
    template <class T>
    class stack
    {
    public:

        T* top;
        T* base;
        int stacksize;
    public:
        stack()
        {
            base = (T *)malloc(STACK_INIT_SIZE * sizeof(T));
            top = base;
            stacksize = STACK_INIT_SIZE;
        }

        void push(T data);

        T pop();

        T* gettop();

        bool is_empty();
    };

    template <class T>
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

        *top++ = data;
    }

    template <class T>
    T stack<T>::pop()
    {
        if (top == base)
        {
            throw STACK_EMPTY;
        }
        auto e = *--top;
        return e;
    }

    template <class T>
    T* stack<T>::gettop()
    {
        if (top == base)
        {
            throw STACK_EMPTY;
        }
        return top - 1;
    }

    template <class T>
    bool stack<T>::is_empty()
    {
        return top == base;
    }

    //自定义字符串
    class String
    {
    public:

        c* ch;
        int length;
    public:
        String() = default;

        explicit String(c* ch);

        explicit String(std::string);

        explicit String(std::wstring);
        c& operator[](int index);

        c indexOf(int index);

        String* substring(int pos, int end);

        String concat(String s);

        void output();

        virtual ~String();


        //friend std::ostream& operator<<(std::ostream& out, String& s);

        //friend bool strcompare(String& s1, String& s2);
        //friend bool operator==(String &s1, String &s2);
    };

    std::ostream& operator<<(std::ostream& out, String& s);
    bool strcompare(String s1, String s2);
    bool strcompare(String* s1, String* s2);
};

#endif //_DATASTRUCTURE_H
