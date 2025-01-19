#pragma once

#include <cstring>

#include "THashTable.h"

// LinearProbing + Multiplication
template<typename K, typename V>
class TLinearHashTable final : public THashTable<K, V>
{
public:
    TLinearHashTable(const int capacity);
    ~TLinearHashTable();
    TLinearHashTable(const TLinearHashTable<K, V>& other);
    TLinearHashTable(TLinearHashTable<K, V>&& other);
    TLinearHashTable<K, V>& operator=(const TLinearHashTable<K, V>& other);
    TLinearHashTable<K, V>& operator=(TLinearHashTable<K, V>&& other);

    virtual bool Insert(const K& key, const V& value) override;
    virtual void RemoveKey(const K& key) override;
    virtual bool ContainsKey(const K& key) override;
    virtual bool TryGetValue(const K& key, V& outValue) override;
    virtual V& operator[](const K& key) override;

private:
    KeyValuePair<K, V>* mpBuckets;
    bool* mpExist;

private:
    virtual int getIndex(const K& key) const override;
    void copyContainers(const TLinearHashTable<K, V>& other);

    int findKeyIndex(const K& key) const;
};

template<typename K, typename V>
inline TLinearHashTable<K, V>::TLinearHashTable(const int capacity)
    : THashTable<K, V>(capacity)
    , mpBuckets(nullptr)
    , mpExist(nullptr)
{
    assert(capacity > 0);

    mpBuckets = new KeyValuePair<K, V>[capacity];
    mpExist = new bool[capacity];

    memset(mpExist, false, sizeof(bool) * capacity);
}

template<typename K, typename V>
inline TLinearHashTable<K, V>::~TLinearHashTable()
{
    delete[] mpBuckets;
    delete[] mpExist;

    mpBuckets = nullptr;
    mpExist = nullptr;
}

template<typename K, typename V>
inline TLinearHashTable<K, V>::TLinearHashTable(const TLinearHashTable<K, V>& other)
    : THashTable<K, V>(other)
    , mpBuckets(nullptr)
    , mpExist(nullptr)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mpExist != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    mpBuckets = new KeyValuePair<K, V>[other.mCapacity];
    mpExist = new bool[other.mCapacity];

    copyContainers(other);
}

template<typename K, typename V>
inline TLinearHashTable<K, V>::TLinearHashTable(TLinearHashTable<K, V>&& other)
    : THashTable<K, V>(other)
    , mpBuckets(other.mpBuckets)
    , mpExist(other.mpExist)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mpExist != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    other.mpBuckets = nullptr;
    other.mpExist = nullptr;
}

template<typename K, typename V>
inline TLinearHashTable<K, V>& TLinearHashTable<K, V>::operator=(const TLinearHashTable<K, V>& other)
{
    if (this != &other)
    {
        delete[] mpBuckets;
        delete[] mpExist;

        THashTable<K, V>::operator=(other);

        mpBuckets = new KeyValuePair<K, V>[other.mCapacity];
        mpExist = new bool[other.mCapacity];

        copyContainers(other);
    }

    return *this;
}

template<typename K, typename V>
inline TLinearHashTable<K, V>& TLinearHashTable<K, V>::operator=(TLinearHashTable<K, V>&& other)
{
    if (this != &other)
    {
        delete[] mpBuckets;
        delete[] mpExist;

        THashTable<K, V>::operator=(other);

        mpBuckets = other.mpBuckets;
        mpExist = other.mpExist;

        other.mpBuckets = nullptr;
        other.mpExist = nullptr;
    }

    return *this;
}

template<typename K, typename V>
inline bool TLinearHashTable<K, V>::Insert(const K& key, const V& value)
{
    const int index = getIndex(key);

    int indexToInsert = index;
    while (mpExist[indexToInsert])
    {
        if (mpBuckets[indexToInsert].Key == key)
        {
            break;
        }

        indexToInsert = (indexToInsert + 1) % THashTable<K, V>::mCapacity;

        if (indexToInsert == index)
        {
            return false;
        }
    }

    mpBuckets[indexToInsert].Key = key;
    mpBuckets[indexToInsert].Value = value;
    mpExist[indexToInsert] = true;

    ++THashTable<K, V>::mSize;

    return true;
}

template<typename K, typename V>
inline void TLinearHashTable<K, V>::RemoveKey(const K& key)
{
    const int indexToRemove = findKeyIndex(key);

    if (indexToRemove == -1)
    {
        return;
    }

    mpExist[indexToRemove] = false;

    --THashTable<K, V>::mSize;
}

template<typename K, typename V>
inline bool TLinearHashTable<K, V>::ContainsKey(const K& key)
{
    const int index = findKeyIndex(key);

    return index != -1;;
}

template<typename K, typename V>
inline bool TLinearHashTable<K, V>::TryGetValue(const K& key, V& outValue)
{
    const int index = findKeyIndex(key);

    if (index == -1)
    {
        return false;
    }

    outValue = mpBuckets[index].Value;

    return true;
}

template<typename K, typename V>
inline V& TLinearHashTable<K, V>::operator[](const K& key)
{
    assert(mpBuckets != nullptr);
    assert(mpExist != nullptr);
    assert((THashTable<K, V>::mSize) > 0);

    const int index = findKeyIndex(key);

    return mpBuckets[index].Value;
}

template<typename K, typename V>
inline int TLinearHashTable<K, V>::getIndex(const K& key) const
{
    constexpr double MULTIPLIER = 0.6180339887;

    const double hash = THashTable<K, V>::getHash(reinterpret_cast<const char*>(&key), sizeof(K));
    const double scaledHash = hash * MULTIPLIER;

    const int index = static_cast<int>((scaledHash - (unsigned int)scaledHash) * THashTable<K, V>::mCapacity);

    return index;
}

template<typename K, typename V>
inline void TLinearHashTable<K, V>::copyContainers(const TLinearHashTable<K, V>& other)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mpExist != nullptr);
    assert((THashTable<K, V>::mCapacity) >= other.mCapacity);

    for (int i = 0; i < other.mCapacity; ++i)
    {
        mpBuckets[i] = other.mpBuckets[i];
        mpExist[i] = other.mpExist[i];
    }
}

template<typename K, typename V>
inline int TLinearHashTable<K, V>::findKeyIndex(const K& key) const
{
    const int index = getIndex(key);

    int retIndex = index;
    while (!mpExist[retIndex] || mpBuckets[retIndex].Key != key)
    {
        retIndex = (retIndex + 1) % THashTable<K, V>::mCapacity;

        if (retIndex == index)
        {
            return -1;
        }
    }

    return retIndex;
}
