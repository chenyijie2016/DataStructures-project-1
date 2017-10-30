#include "stdafx.h"
#include "String.h"
String::String(std::wstring chars)
{
    current_tok_ptr = 0;
    if (!(ch = new c[chars.length()+1]))
    {
        throw Error(STRING_OVERFLOW);
    }
    wcscpy(ch, chars.c_str());
//    ch = (c *)
//    ch[chars.length()] = L'\0';
    length = chars.length();
}


c &String::operator[](int index)
{
    return ch[index];
}

c String::indexOf(int index)
{
    return ch[index];
}

String *String::substring(int pos, int len)
{
    if (pos < 1 || pos > length || len <= 0 || len > length - pos + 1)
    {
        throw Error(SUBSTRING_OVER_LENGTH);
    }
    auto sub = new String;
    if (!(sub->ch = new c[len + 1]))
    {
        throw Error(SUBSTRING_ERROR);
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

String *String::strtok(wchar_t delimiter)
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

String *String::firststrtok(wchar_t delimiter)
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
    return ch[index];

}

std::ostream &operator<<(std::ostream &out, String &s)
{
    for (int i = 0; i < s.length; i++)
    {
        out << s[i];
    }
    return out;
}

bool strcompare(String *s1, String *s2)
{
    //wprintf(L"compare:[%ls], [%ls] \r\n", s1->ch, s2->ch);
    for (int i = 0; i < s1->length && i < s2->length; ++i)
    {
        if (s1->ch[i] != s2->ch[i])
            return (s1->ch[i] - s2->ch[i]);
    }
    return (s1->length - s2->length);
}