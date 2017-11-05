#pragma once
#include "String.h"
#include "Error.h"
#include "LinkList.h"
#define HASH_TABLE_SIZE  100007


class StringHashTable
{
public:
    LinkList<String>* data;
    unsigned int hashfunction(String str);
    StringHashTable();

    StringHashTable(const StringHashTable& sht)
    {
        data = sht.data;
    }

    void insert(String str);
    bool operator[](String str);
};
