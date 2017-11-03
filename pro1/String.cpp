#include "stdafx.h"
#include "String.h"
#include <memory>
using namespace std;

String::String(std::wstring chars)
{
    current_tok_ptr = 0;
    if (!(ch = new c[chars.length() + 1]))
    {
        throw Error(STRING_OVERFLOW);
    }
    wcscpy(ch, chars.c_str());
    length = chars.length();
}


c& String::operator[](int index)
{
    if (index < 0 || index >= length)
        throw Error("String operator[]: index out of range");
    if (ch == nullptr)
    {
        cout << "address of ch:" << addressof(ch) << endl;
        throw Error("String operator[]: string not exists!");
    }
    return ch[index];
}

c String::indexOf(int index)
{
    if (index < 0 || index > length)
        throw Error("String: index out of range");
    return ch[index];
}

String* String::substring(int pos, int len)
{
    if (pos < 1 || pos > length || len <= 0 || len > length - pos + 1)
    {
        throw Error("String::substring: out of limit");
    }
    auto sub = new String;
    if (!(sub->ch = new c[len + 1]))
    {
        throw Error("String::substring: new fail");
    }

    sub->length = len;
    for (int i = 0; i < len; i++)
    {
        sub->ch[i] = ch[pos - 1 + i];
    }
    return sub;
}

String String::concat(String s)
{
    //TODO
    return String();
}

void String::output()
{
    for (int i = 0; i < length; i++)
    {
        wprintf(L"%c", ch[i]);
    }
}

String::~String()
{
    delete[] ch;
}

String* String::strtok(wchar_t delimiter)
{
    for (int i = current_tok_ptr + 1; i < length; i++)
    {
        if (ch[i] == delimiter)
        {
            auto sub = this->substring(current_tok_ptr + 1, i - current_tok_ptr);
            current_tok_ptr = i;
            return sub;
        }
    }

    return nullptr;
}

String* String::firststrtok(wchar_t delimiter)
{
    for (int i = 0; i < length; i++)
    {
        if (ch[i] == delimiter)
        {
            current_tok_ptr = i;
            break;
        }
    }
    for (int i = current_tok_ptr + 1; i < length; i++)
    {
        if (ch[i] == delimiter)
        {
            auto sub = this->substring(current_tok_ptr + 1, i - current_tok_ptr);
            current_tok_ptr = i;
            return sub;
        }
    }
    return nullptr;
}

c String::at(int index)
{
    if (index < 0 || index >= length)
        throw Error("String at: index out of range");
    if (ch == nullptr)
    {
        cout << "address of ch:" << addressof(ch) << endl;
        throw Error("String at: string not exists!");
    }

    return ch[index];
}

std::ostream& operator<<(std::ostream& out, String& s)
{
    for (int i = 0; i < s.length; i++)
    {
        out << s[i];
    }
    return out;
}

bool strcompare(String* s1, String* s2)
{
    for (int i = 0; i < s1->length && i < s2->length; ++i)
    {
        if (s1->ch[i] != s2->ch[i])
            return (s1->ch[i] - s2->ch[i]);
    }
    return (s1->length - s2->length);
}
