#include "stdafx.h"
#include "String.h"

String::String(const CharType* str)
{
    int size = (str ? wcslen(str) + 1 : 1);
    data = new CharType[size];
    if (str)
    {
        wcscpy(data, str);
    }
    else
    {
        data[0] = '\0';
    }
}

String::String(std::wstring str)
{
    int size = str.size() + 1;
    data = new CharType[size];
    wcscpy(data, str.data());
}

String::String(String& str)
{
    data = new CharType[str.size() + 1];
    wcscpy(data, str.data);
}

/**
 * \brief 赋值(assign)
 * \param str 
 * \return 
 */
String& String::operator=(const String& str)
{
    if (this != &str)
    {
        destory();
        data = new CharType[wcslen(str.data) + 1];
        wcscpy(data, str.data);
    }

    return *this;
}

String::~String()
{
    destory();
}

/**
 * \brief 
 * \param index 
 * \return 
 */
CharType& String::operator[](SizeType index)
{
    if (index >= this->size() || index < 0)
    {
        throw Error("String::operator[]: index out of range");
    }
    return data[index];
}

/**
 * \brief 获取字符串长度
 * \return 
 */
SizeType String::size()
{
    return wcslen(data);
}

/**
 * \brief 判断两个字符串是否相等
 * \param str 
 * \return 
 */
bool String::operator==(const String str) const
{
    return wcscmp(data, str.data) == 0;
}

/**
 * \brief 返回下标从start_p到end_p的子字符串，**不包括end_p**
 * \param start_p 
 * \param end_p 
 * \return 
 */
String String::substr(SizeType start_p, SizeType end_p)
{
    if (start_p < 0 || start_p >= size() || end_p < 0 || end_p > size() || start_p >= end_p)
    {
        std::cout << "Traceback start_p= " << start_p << "  end_p= " << end_p << std::endl;
        throw Error("String::substr: index error");
    }
    CharType* subdata = new CharType[end_p - start_p + 1];
    int j = 0;
    for (int i = start_p; i < end_p; i++)
    {
        subdata[j] = data[i];
        j++;
    }
    subdata[j] = L'\0';
    String tmp(subdata);
    delete[] subdata;
    return tmp;
}

/**
 * \brief 使用kmp算法进行字符串匹配
 * \param sub_str 待匹配的子串
 * \return 子串第一次出现的位置，未出现则返回this->size();
 */
SizeType String::indexof(String& sub_str)
{
    if (sub_str.empty())
    {
        return size();
    }

    int* next = new int[sub_str.size() + 1];
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < sub_str.size(); ++i)
    {
        while (j > -1 && sub_str[j + 1] != sub_str[i])
            j = next[j];
        if (sub_str[j + 1] == sub_str[i])
            ++j;
        next[i] = j;
    }
    j = -1;
    for (int i = 0; i < size(); ++i)
    {
        while (j > -1 && sub_str[j + 1] != data[i])
            j = next[j];
        if (sub_str[j + 1] == data[i])
            ++j;
        if (j == sub_str.size() - 1)
        {
            delete[] next;
            return i - sub_str.size() + 1;
        }
    }
    delete[] next;
    return size();
}

/**
 * \brief 字符串连接
 * \param str 待连接的字符串
 * \return 连接后的字符串,注意此函数不会改变两个连接的字符串的内容
 */
String String::concat(String& str)
{
    CharType* concatdata = new CharType[size() + str.size() + 1];
    int i, j;
    for (i = 0; i < size(); i++)
    {
        concatdata[i] = data[i];
    }
    for (j = i; j < size() + str.size(); j++)
    {
        concatdata[j] = str[j - i];
    }
    concatdata[size() + str.size()] = L'\0';
    String concatstring(concatdata);
    delete[] concatdata;
    return concatstring;
}

/**
 * \brief 是否为空
 * \return 
 */
bool String::empty()
{
    return size() == 0;
}

/**
 * \brief 字符串分割
 * \param delim 分隔符
 * \param first 是否是第一次执行
 * \return 分割出的子字符串，不可继续分割时返回空字符串
 */
String String::strtok(CharType delim, bool first)
{
    if (first)
    {
        int start = 0, end = 0, i;
        for (i = 1; i < size(); i++)
        {
            if (data[i] == delim)
            {
                start = i;
                break;
            }
        }
        for (int j = 1 + i; j < size(); j++)
        {
            if (data[j] == delim)
            {
                end = j;
                tok_point = j;
                break;
            }
        }
        String tmp;
        if (end > start)
            tmp = substr(start, end);
        return tmp;
    }
    else
    {
        int end = 0;
        int i;
        for (i = tok_point + 1; i < size(); i++)
        {
            if (data[i] == delim)
            {
                end = i;
                break;
            }
        }


        String tmp;
        if (i == size() && tok_point < size() && end == 0)
        {
            tmp = substr(tok_point, size());
            tok_point = size();
            return tmp;
        }
        if (end > tok_point)
        {
            tmp = substr(tok_point, end);
            tok_point = end;
        }
        return tmp;
    }
}


/**
 * \brief 释放内存
 */
void String::destory()
{
    if (data)
    {
        delete[] data;
        data = nullptr;
    }
}

/**
 * \brief 将src中的unicode编码字符转为gbk编码
 * \param src 
 * \return 
 */
String decode(String src)
{
    String b, result;
    String tag;
    tag = String(L"&#");
    int current_p = 0;
    while (true)
    {
        unsigned int start = src.indexof(tag);
        if (start == src.size())
        {
            String temp;
            if (start > current_p)
                temp = src.substr(current_p, start);
            result = result.concat(temp);
            break;
        }
        String temp;
        if (start > current_p)
            temp = src.substr(current_p, start);
        result = result.concat(temp);
        current_p = start;
        b = src.substr(start + 2, start + 7);
        int ans = 0;
        for (int i = 0; i < 5; i++)
        {
            ans = ans * 10;
            ans += b[i] - L'0';
        }
        CharType tmp[] = L" ";
        tmp[0] = ans;
        String tmpstr(tmp);
        result = result.concat(tmpstr);

        src = src.substr(start + 7, src.size());
    }
    return result;
}
#ifdef DEBUG

void String::output()
{
    wprintf(L"%ls", data);
}

#endif
