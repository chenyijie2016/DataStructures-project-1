#pragma once

#include "Error.h"

#include<iostream>
#define DEBUG
typedef wchar_t CharType;
typedef unsigned int SizeType;

class String
{
private:
    CharType* data;
    SizeType tok_point;
    void destory();

public:
    explicit String(const CharType* str = nullptr);

    explicit String(std::wstring);

    String(String& str);

    String& operator=(const String& str);

    ~String();

public:
    inline CharType& operator[](SizeType index);

    bool operator==(const String str) const;

    SizeType size();

    String substr(SizeType start_p, SizeType end_p);

    SizeType indexof(String& str);

    String concat(String& str);

    bool empty();

    String strtok(CharType delim, bool first = false);

#ifdef DEBUG
    void output();
#endif
};
String decode(String src);
