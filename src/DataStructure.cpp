//
// Created by cyj on 2017/10/24.
//

#include <cstring>
#include "DataStructure.h"

MyDataStructure::String::String(c* chars)
{
    int i;
    c* cha;
    for (i = 0, cha = chars; *cha; ++i, ++cha);
    if (!i)
    {
        ch = nullptr;
        length = 0;
    }
    else
    {
        if (!(ch = (c *)malloc(i * sizeof(c))))
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
    if (!(ch = (c*)malloc(chars.size() * sizeof(c))))
    {
        throw STRING_OVERFLOW;
    }
    ch = (c*)chars.data();
    length = chars.size();
}


MyDataStructure::c& MyDataStructure::String::operator[](int index)
{
    return ch[index];
}

MyDataStructure::c MyDataStructure::String::indexOf(int index)
{
    return ch[index];
}

MyDataStructure::String MyDataStructure::String::substring(int pos, int len)
{
    if (pos < 1 || pos > length || len <= 0 || len > length - pos + 1)
    {
        throw SUBSTRING_ERROR;
    }
    auto sub = new String;
    sub->ch = (c*)malloc(sizeof(c) * len);
    sub->length = len;
    for (int i = 0; i < len; i++)
    {
        sub->ch[i] = ch[pos - 1 + i];
    }
    return *sub;
}

MyDataStructure::String MyDataStructure::String::concat(String s)
{
    //TODO
    //return nullptr;
}

std::ostream& MyDataStructure::operator<<(std::ostream& out, String& s)
{
    for (int i = 0; i < s.length; i++)
    {
        out << s[i];
    }
    return out;
}

bool MyDataStructure::strcompare(String s1, String s2)
{
    for (int i = 0; i < s1.length && i < s2.length; ++i)
    {
        if (s1.ch[i] != s2.ch[i])
            return s1.ch[i] - s2.ch[i];
    }
    return s1.length - s2.length;
}
