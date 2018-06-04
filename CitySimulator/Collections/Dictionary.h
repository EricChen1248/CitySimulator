#pragma once
#include "List.h"


template<typename KeyType, typename ValueType>
class Dictionary
{
public:
    Dictionary(int size = 16);
    void Insert(KeyType& key, ValueType& value);
    bool Contains(KeyType& key) const;
    ValueType& GetItem(KeyType& key);
private:
    ValueType* table;
    List<KeyType&> keys;
    int count;
};

template <typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary(const int size)
{
    table = new ValueType[size];
    for (int i = 0; i < size; ++i)
    {
        table[i] = NULL;
    }
    count = 0;
}

template <typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::Insert(KeyType& key, ValueType& value)
{
    if (Contains(key))
    {
        throw KeyValueError("Item with key: " + key + " already exists in dictionary");
    }
    keys.InsertLast(key);
    const int hash = key.hash() % count;
    table[hash] = value;
    ++count;
}


template <typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Contains(KeyType& key) const
{
    const int hash = key.hash() % count;
    if (table[hash] == NULL)
    {
        return false;
    }
    return true;
}

template <typename KeyType, typename ValueType>
ValueType& Dictionary<KeyType, ValueType>::GetItem(KeyType& key)
{
    if (Contains(key))
    {
        const int hash = key.hash();
        return table[hash];
    }
    throw KeyNotFound("Key: " + key + " does not exist in dictionary");
}
