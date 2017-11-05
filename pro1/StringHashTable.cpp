#include "stdafx.h"
#include "StringHashTable.h"

unsigned int StringHashTable::hashfunction(String str)
{
    unsigned int hash = 0;
    int seed = 233;
    for (int i = 0; i < str.size(); i++)
    {
        hash = hash*seed + str[i];
        hash = hash % HASH_TABLE_SIZE;
    }
    return hash;
}

StringHashTable::StringHashTable()
{
    data = new LinkList<String>[HASH_TABLE_SIZE];
    if (!data)
    {
        throw Error("Init hashtable fail");
    }
    memset(data, NULL, HASH_TABLE_SIZE);
}

void StringHashTable::insert(String str)
{
    auto hashcode = hashfunction(str);
    if (!data[hashcode].contains(str))
    {
        data[hashcode].insert(str);
    }
}

bool StringHashTable::operator[](String str)
{
    auto hashcode = hashfunction(str);
    return data[hashcode].contains(str);
}
