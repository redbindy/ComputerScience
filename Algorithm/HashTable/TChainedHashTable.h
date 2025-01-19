#pragma once

#include <list>

#include "THashTable.h"
#include "../PrimeNumber/PrimeNumber.h"

// Chaining + Division
template<typename K, typename V>
class TChainedHashTable final : THashTable<K, V>
{
public:
    TChainedHashTable(const int capacity);
    ~TChainedHashTable();
    TChainedHashTable(const TChainedHashTable<K, V>& other);
    TChainedHashTable(TChainedHashTable<K, V>&& other);
    TChainedHashTable<K, V>& operator=(const TChainedHashTable<K, V>& other);
    TChainedHashTable<K, V>& operator=(TChainedHashTable<K, V>&& other);

    virtual bool Insert(const K& key, const V& value) override;
    virtual void RemoveKey(const K& key) override;
    virtual bool ContainsKey(const K& key) override;
    virtual bool TryGetValue(const K& key, V& outValue) override;
    virtual V& operator[](const K& key) override;

private:
    std::list<KeyValuePair<K, V>>* mpBuckets;

private:
    virtual int getIndex(const K& key) const override;
    void copyBuckets(const TChainedHashTable<K, V>& other);

    std::list<KeyValuePair<K, V>>::iterator findIterator(std::list<KeyValuePair<K, V>>& list, const K& key);
};

template<typename K, typename V>
inline TChainedHashTable<K, V>::TChainedHashTable(const int capacity)
    : THashTable<K, V>()
    , mpBuckets(nullptr)
{
    assert(capacity > 0);

    THashTable<K, V>::mCapacity = capacity * 2 + 1;

    while (!IsPrimeNumber(THashTable<K, V>::mCapacity))
    {
        ++THashTable<K, V>::mCapacity;
    }

    mpBuckets = new std::list<KeyValuePair<K, V>>[THashTable<K, V>::mCapacity];
}

template<typename K, typename V>
inline TChainedHashTable<K, V>::~TChainedHashTable()
{
    delete[] mpBuckets;

    mpBuckets = nullptr;
}

template<typename K, typename V>
inline TChainedHashTable<K, V>::TChainedHashTable(const TChainedHashTable<K, V>& other)
    : THashTable<K, V>(other)
    , mpBuckets(nullptr)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    mpBuckets = new std::list<KeyValuePair<K, V>>[other.mCapacity];

    copyBuckets(other);
}

template<typename K, typename V>
inline TChainedHashTable<K, V>::TChainedHashTable(TChainedHashTable<K, V>&& other)
    : THashTable<K, V>(other)
    , mpBuckets(other.mpBuckets)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    other.mpBuckets = nullptr;
}

template<typename K, typename V>
inline TChainedHashTable<K, V>& TChainedHashTable<K, V>::operator=(const TChainedHashTable<K, V>& other)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    if (this != &other)
    {
        delete[] mpBuckets;

        THashTable<K, V>::operator=(other);

        mpBuckets = new std::list<KeyValuePair<K, V>>[other.mCapacity];

        copyBuckets(other);
    }

    return *this;
}

template<typename K, typename V>
inline TChainedHashTable<K, V>& TChainedHashTable<K, V>::operator=(TChainedHashTable<K, V>&& other)
{
    assert(other.mpBuckets != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    if (this != &other)
    {
        delete[] mpBuckets;

        THashTable<K, V>::operator=(other);

        mpBuckets = other.mpBuckets;

        other.mpBuckets = nullptr;
    }

    return *this;
}

template<typename K, typename V>
inline bool TChainedHashTable<K, V>::Insert(const K& key, const V& value)
{
    const int index = getIndex(key);

    mpBuckets[index].push_back({ key, value });

    ++THashTable<K, V>::mSize;

    return true;
}

template<typename K, typename V>
inline void TChainedHashTable<K, V>::RemoveKey(const K& key)
{
    const int index = getIndex(key);

    std::list<KeyValuePair<K, V>>& list = mpBuckets[index];

    typename std::list<KeyValuePair<K, V>>::iterator it = findIterator(list, key);

    if (it != list.end())
    {
        it = list.erase(it);
    }
}

template<typename K, typename V>
inline bool TChainedHashTable<K, V>::ContainsKey(const K& key)
{
    const int index = getIndex(key);

    std::list<KeyValuePair<K, V>>& list = mpBuckets[index];

    typename std::list<KeyValuePair<K, V>>::iterator it = findIterator(list, key);

    return it != list.end();
}

template<typename K, typename V>
inline bool TChainedHashTable<K, V>::TryGetValue(const K& key, V& outValue)
{
    const int index = getIndex(key);

    std::list<KeyValuePair<K, V>>& list = mpBuckets[index];

    typename std::list<KeyValuePair<K, V>>::iterator it = findIterator(list, key);

    if (it != list.end())
    {
        outValue = it->Value;

        return true;
    }

    return false;
}

template<typename K, typename V>
inline V& TChainedHashTable<K, V>::operator[](const K& key)
{
    assert(mpBuckets != nullptr);
    assert((THashTable<K, V>::mSize) > 0);

    const int index = getIndex(key);

    std::list<KeyValuePair<K, V>>& list = mpBuckets[index];

    typename std::list<KeyValuePair<K, V>>::iterator it = findIterator(list, key);
    assert(it != list.end());

    return it->Value;
}

template<typename K, typename V>
inline int TChainedHashTable<K, V>::getIndex(const K& key) const
{
    const unsigned int hash = THashTable<K, V>::getHash(reinterpret_cast<const char*>(&key), sizeof(K));

    return hash % THashTable<K, V>::mCapacity;
}

template<typename K, typename V>
inline void TChainedHashTable<K, V>::copyBuckets(const TChainedHashTable<K, V>& other)
{
    assert(other.mpBuckets != nullptr);
    assert((THashTable<K, V>::mCapacity) >= other.mCapacity);

    for (int i = 0; i < other.mCapacity; ++i)
    {
        mpBuckets[i] = other.mpBuckets[i];
    }
}

template<typename K, typename V>
inline std::list<KeyValuePair<K, V>>::iterator TChainedHashTable<K, V>::findIterator(std::list<KeyValuePair<K, V>>& list, const K& key)
{
    typename std::list<KeyValuePair<K, V>>::iterator it = list.begin();

    while (it != list.end())
    {
        if (it->Key)
        {
            break;
        }

        ++it;
    }

    return it;
}
