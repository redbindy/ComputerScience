#pragma once

#include <cassert>
#include <cstring>

template<typename T>
class TArray final
{
public:
    TArray(const int capacity);
    ~TArray();
    TArray(const TArray<T>& other);
    TArray(TArray<T>&& other);
    TArray<T>& operator=(const TArray<T>& other);
    TArray<T>& operator=(TArray<T>&& other);

    int GetCapacity() const;
    int GetSize() const;

    bool IsFull() const;

    T& operator[](const int index);

    void Add(T item);
    void Insert(T item, const int index);
    void RemoveAt(const int index);
    void Remove(T item);

private:
    T* mpData;

    int mCapacity;
    int mSize;

private:
    void extendArray();
    void unsetArray(TArray& arr);
};

template<typename T>
inline TArray<T>::TArray(const int capacity)
    : mpData(nullptr)
    , mCapacity(capacity)
    , mSize(0)
{
    assert(capacity > 0);

    mpData = new T[capacity];
}

template<typename T>
inline TArray<T>::~TArray()
{
    delete[] mpData;

    unsetArray(*this);
}

template<typename T>
inline TArray<T>::TArray(const TArray<T>& other)
    : mpData(nullptr)
    , mCapacity(other.mCapacity)
    , mSize(other.mSize)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    mpData = new T[mCapacity];

    memcpy(mpData, other.mpData, sizeof(T) * mSize);
}

template<typename T>
inline TArray<T>::TArray(TArray<T>&& other)
    : mpData(other.mpData)
    , mCapacity(other.mCapacity)
    , mSize(other.mSize)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    unsetArray(other);
}

template<typename T>
inline TArray<T>& TArray<T>::operator=(const TArray<T>& other)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    if (this != &other)
    {
        delete[] mpData;

        mCapacity = other.mCapacity;
        mSize = other.mSize;

        mpData = new T[mCapacity];

        memcpy(mpData, other.mpData, sizeof(T) * mSize);
    }

    return *this;
}

template<typename T>
inline TArray<T>& TArray<T>::operator=(TArray<T>&& other)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    if (this != &other)
    {
        delete[] mpData;

        mpData = other.mpData;

        mCapacity = other.mCapacity;
        mSize = other.mSize;

        unsetArray(other);
    }

    return *this;
}

template<typename T>
inline int TArray<T>::GetCapacity() const
{
    return mCapacity;
}

template<typename T>
inline int TArray<T>::GetSize() const
{
    return mSize;
}

template<typename T>
inline bool TArray<T>::IsFull() const
{
    return mSize == mCapacity;
}

template<typename T>
inline T& TArray<T>::operator[](const int index)
{
    assert(index >= 0);
    assert(index < mSize);

    return mpData[index];
}

template<typename T>
inline void TArray<T>::Add(T item)
{
    if (IsFull())
    {
        extendArray();
    }

    mpData[mSize++] = item;
}

template<typename T>
inline void TArray<T>::Insert(T item, const int index)
{
    assert(index >= 0);
    assert(index <= mSize);

    if (IsFull())
    {
        extendArray();
    }

    T* const pREnd = mpData + index;

    for (T* pRIter = mpData + mSize; pRIter > pREnd; --pRIter)
    {
        *pRIter = *(pRIter - 1);
    }
    *pREnd = item;

    ++mSize;
}

template<typename T>
inline void TArray<T>::RemoveAt(const int index)
{
    assert(index >= 0);
    assert(index < mSize);

    const T* const pEnd = mpData + mSize - 1;

    for (T* pIter = mpData + index; pIter < pEnd; ++pIter)
    {
        *pIter = pIter[1];
    }

    --mSize;
}

template<typename T>
inline void TArray<T>::Remove(T item)
{
    const T* const pEnd = mpData + mSize;

    for (T* pIter = mpData; pIter < pEnd; ++pIter)
    {
        if (*pIter == item)
        {
            RemoveAt(static_cast<int>(pIter - mpData));

            return;
        }
    }
}

template<typename T>
inline void TArray<T>::extendArray()
{
    assert(mpData != nullptr);

    mCapacity *= 2;

    T* pNewData = new T[mCapacity];

    memcpy(pNewData, mpData, sizeof(T) * mSize);

    delete[] mpData;

    mpData = pNewData;
}

template<typename T>
inline void TArray<T>::unsetArray(TArray& arr)
{
    arr.mpData = nullptr;

    arr.mCapacity = -1;
    arr.mSize = -1;
}
