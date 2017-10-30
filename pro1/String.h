#pragma once

#include "Error.h"

typedef wchar_t c;

class String
{
public:
    c *ch;
    int length;
    int current_tok_ptr;
public:
    String() = default;

    //explicit String(c *ch);

    //explicit String(std::string);

    explicit String(std::wstring);

    c &operator[](int index);

    c indexOf(int index);

    String *substring(int pos, int end);

    String concat(String s);

    void output();

    virtual ~String();

    String *strtok(wchar_t delimiter);

    String *firststrtok(wchar_t delimiter);

    c at(int index);

    //friend std::ostream& operator<<(std::ostream& out, String& s);

    //friend bool strcompare(String& s1, String& s2);
    //friend bool operator==(String &s1, String &s2);
};

std::ostream &operator<<(std::ostream &out, String &s);

//bool strcompare(String s1, String s2);

bool strcompare(String *s1, String *s2);
