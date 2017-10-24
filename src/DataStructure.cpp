//
// Created by cyj on 2017/10/24.
//

#include <cstring>
#include "DataStructure.h"

MyDataStructure::String::String(wchar_t* chars)
{
    int i;
    wchar_t* c;
    for (i = 0, c = chars; *c; ++i, ++c);
    if (!i)
    {
        ch = nullptr;
        length = 0;
    }
    else
    {
        if (!(ch = (wchar_t *)malloc(i * sizeof(wchar_t))))
        {
            throw STRING_OVERFLOW;
            //exit(STRING_OVERFLOW);
        }
        for (int j = 0; j < i; j++)
            ch[j] = chars[j];
        length = i;
    }
}

MyDataStructure::String::String(std::string chars)
{
    if (!(ch = (wchar_t*)malloc(chars.size() * sizeof(wchar_t))))
    {
        throw STRING_OVERFLOW;
    }
    length = chars.size();
}


wchar_t& MyDataStructure::String::operator[](int index)
{
    return ch[index];
}

//bool MyDataStructure::operator==(MyDataStructure::String &s1, MyDataStructure::String &s2)
//{
//    return false;
//}
