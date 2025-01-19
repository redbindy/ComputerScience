#pragma once

#include <cassert>
#include <utility>

template<typename K, typename V>
struct KeyValuePair
{
    K Key;
    V Value;
};

template<typename K, typename V>
class THashTable
{
public:
    THashTable(const int capacity);
    virtual ~THashTable();
    THashTable(const THashTable<K, V>& other);
    THashTable(THashTable<K, V>&& other);
    THashTable<K, V>& operator=(const THashTable<K, V>& other);
    THashTable<K, V>& operator=(THashTable<K, V>&& other);
    int GetCapacity() const;
    int GetSize() const;

    virtual bool Insert(const K& key, const V& value) = 0;
    virtual void RemoveKey(const K& key) = 0;
    virtual bool ContainsKey(const K& key) = 0;
    virtual bool TryGetValue(const K& key, V& outValue) = 0;
    virtual V& operator[](const K& key) = 0;

protected:
    THashTable();
    unsigned getHash(const char* pValue, const int byteSize) const;
    virtual int getIndex(const K& key) const = 0;

    int mCapacity;
    int mSize;

private:
    void unsetHashTable(THashTable<K, V>& other);
};

template<typename K, typename V>
inline THashTable<K, V>::THashTable()
    : mCapacity(0)
    , mSize(0)
{
}

template<typename K, typename V>
inline THashTable<K, V>::THashTable(const int capacity)
    : mCapacity(capacity)
    , mSize(0)
{
    assert(capacity >= 0);
}

template<typename K, typename V>
inline THashTable<K, V>::~THashTable()
{
    unsetHashTable(*this);
}

template<typename K, typename V>
inline THashTable<K, V>::THashTable(const THashTable<K, V>& other)
    : mCapacity(other.mCapacity)
    , mSize(other.mSize)
{
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);
}

template<typename K, typename V>
inline THashTable<K, V>::THashTable(THashTable<K, V>&& other)
    : mCapacity(other.mCapacity)
    , mSize(other.mSize)
{
    unsetHashTable(other);
}

template<typename K, typename V>
inline THashTable<K, V>& THashTable<K, V>::operator=(const THashTable<K, V>& other)
{
    if (this != &other)
    {
        mCapacity = other.mCapacity;
        mSize = other.mSize;
    }

    return *this;
}

template<typename K, typename V>
inline THashTable<K, V>& THashTable<K, V>::operator=(THashTable<K, V>&& other)
{
    if (this != &other)
    {
        mCapacity = other.mCapacity;
        mSize = other.mSize;

        unsetHashTable(other);
    }

    return *this;
}

template<typename K, typename V>
inline int THashTable<K, V>::GetCapacity() const
{
    return mCapacity;
}

template<typename K, typename V>
inline int THashTable<K, V>::GetSize() const
{
    return mSize;
}

template<typename K, typename V>
inline void THashTable<K, V>::unsetHashTable(THashTable<K, V>& other)
{
    other.mCapacity = -1;
    other.mSize = -1;
}

template<typename K, typename V>
unsigned THashTable<K, V>::getHash(const char* pValue, const int byteSize) const
{
    assert(pValue != nullptr);
    assert(byteSize >= 1);

    unsigned int hash = 0;
    for (const char* p = pValue; p < pValue + byteSize; ++p)
    {
        hash += *p;
    }

    return hash;
}
