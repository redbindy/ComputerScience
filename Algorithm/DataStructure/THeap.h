#pragma once

#include <cassert>
#include <cstring>

template<typename T>
class THeap
{
public:
    THeap(const int capacity);
    THeap(const int capacity, bool (*compare)(T&, T&));
    ~THeap();
    THeap(const THeap<T>& other);
    THeap(const THeap<T>&& other);
    THeap<T>& operator=(const THeap<T>& other);
    THeap<T>& operator=(const THeap<T>&& other);

    void Add(T& item);
    void Poll();
    T& Peek();

private:
    T* mpData;

    int mCapacity;
    int mSize;

    bool (*mbCompareFunc)(T&, T&);

private:
    void unsetHeap(THeap<T>& heap);

    static bool compare(T& a, T& b);
};

template<typename T>
inline THeap<T>::THeap(const int capacity)
    : THeap(capacity, THeap<T>::compare)
{
    assert(capacity > 0);
}

template<typename T>
inline THeap<T>::THeap(const int capacity, bool(*compare)(T&, T&))
    : mpData(nullptr)
    , mCapacity(capacity)
    , mSize(0)
    , mbCompareFunc(compare)
{
    assert(capacity > 0);
    assert(compare != nullptr);

    mpData = new T[capacity + 1];
}

template<typename T>
inline THeap<T>::~THeap()
{
    delete[] mpData;

    unsetHeap(*this);
}

template<typename T>
inline THeap<T>::THeap(const THeap<T>& other)
    : mpData(nullptr)
    , mCapacity(other.mCapacity)
    , mSize(other.mSize)
    , mbCompareFunc(other.mbCompareFunc)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    mpData = new T[other.mCapacity + 1];

    memcpy(mpData, other.mpData, sizeof(T) * (other.mCapacity + 1));
}

template<typename T>
inline THeap<T>::THeap(const THeap<T>&& other)
    : mpData(other.mpData)
    , mCapacity(other.mCapacity)
    , mSize(other.mSize)
    , mbCompareFunc(other.mbCompareFunc)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);
}

template<typename T>
inline THeap<T>& THeap<T>::operator=(const THeap<T>& other)
{
    if (this != &other)
    {
        delete[] mpData;

        mpData = new T[other.mCapacity + 1];

        mCapacity = other.mCapacity;
        mSize = other.mSize;

        mbCompareFunc = other.mbCompareFunc;

        memcpy(mpData, other.mpData, sizeof(T) * (other.mCapacity + 1));
    }

    return *this;
}

template<typename T>
inline THeap<T>& THeap<T>::operator=(const THeap<T>&& other)
{
    if (this != &other)
    {
        delete[] mpData;

        mpData = other.mpData;

        mCapacity = other.mCapacity;
        mSize = other.mSize;

        mbCompareFunc = other.mbCompareFunc;

        unsetHeap(other);
    }

    return *this;
}

template<typename T>
inline void THeap<T>::Add(T& item)
{
    if (mCapacity == mSize)
    {
        mCapacity *= 2;

        T* pNewData = new T[mCapacity + 1];

        memcpy(pNewData, mpData, sizeof(T) * (mSize + 1));

        delete[] mpData;

        mpData = pNewData;
    }

    ++mSize;

    int node = mSize;
    while (node != 1)
    {
        const int parent = node / 2;

        if (mbCompareFunc(mpData[parent], item))
        {
            break;
        }

        mpData[node] = mpData[parent];

        node = parent;
    }

    mpData[node] = item;
}

template<typename T>
inline void THeap<T>::Poll()
{
    assert(mSize > 0);

    T data = mpData[mSize--];

    int node = 1;
    while (true)
    {
        int childIndex = node * 2;

        if (childIndex > mSize)
        {
            break;
        }

        T leftChild = mpData[childIndex];
        T rightChild = mpData[childIndex + 1];

        if (!mbCompareFunc(leftChild, rightChild))
        {
            ++childIndex;
        }

        if (mbCompareFunc(data, mpData[childIndex]))
        {
            break;
        }

        mpData[node] = mpData[childIndex];

        node = childIndex;
    }

    mpData[node] = data;
}

template<typename T>
inline T& THeap<T>::Peek()
{
    assert(mSize > 0);

    return mpData[1];
}

template<typename T>
inline void THeap<T>::unsetHeap(THeap<T>& heap)
{
    heap.mpData = nullptr;
    
    heap.mCapacity = -1;
    heap.mSize = -1;
}

template<typename T>
inline bool THeap<T>::compare(T& a, T& b)
{
    return a < b;
}
