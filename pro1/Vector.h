#pragma once

typedef unsigned int SizeType;

template <typename T>
class Vector
{
private:
    T* m_pData;
    SizeType m_size;
public:
    Vector()
    {
        m_size = 0;
        m_pData = nullptr;
    }

public:
    void push_back(T data);
    T pop_back();
    SizeType size();
    T& operator[](SizeType index);
};
