#pragma once

#include <cassert>
#include <cstring>

#include "TQueue.h"

template<typename T>
class TArrayQueue final : public TQueue<T>
{
public:
    TArrayQueue(const int capacity);
    ~TArrayQueue() override;
    TArrayQueue(const TArrayQueue<T>& other);
    TArrayQueue(TArrayQueue<T>&& other);
    TArrayQueue<T>& operator=(const TArrayQueue<T>& other);
    TArrayQueue<T>& operator=(TArrayQueue<T>&& other);

    int GetSize() const;
    bool IsFull() const;

    void Enqueue(T item) override;
    void Dequeue() override;
    T& PeekFront() override;
    T& PeekBack() override;

private:
    T* mpData;

    int mCapacity;
    int mSize;

    int mFront;
    int mBack;

private:
    void unsetArrayQueue(TArrayQueue<T>& queue);
};

template<typename T>
inline TArrayQueue<T>::TArrayQueue(const int capacity)
    : mpData(nullptr)
    , mCapacity(capacity)
    , mSize(0)
    , mFront(0)
    , mBack(0)
{
    assert(capacity > 0);

    mpData = new T[mCapacity];
}

template<typename T>
inline TArrayQueue<T>::~TArrayQueue()
{
    delete[] mpData;

    unsetArrayQueue(*this);
}

template<typename T>
inline TArrayQueue<T>::TArrayQueue(const TArrayQueue<T>& other)
    : mpData(nullptr)
    , mSize(other.mSize)
    , mCapacity(other.mCapacity)
    , mFront(other.mFront)
    , mBack(other.mBack)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    mpData = new T[mCapacity];

    memcpy(mpData, other.mpData, sizeof(T) * other.mSize);
}

template<typename T>
inline TArrayQueue<T>::TArrayQueue(TArrayQueue<T>&& other)
    : mpData(other.mpData)
    , mCapacity(other.mCapacity)
    , mSize(other.mSize)
    , mFront(other.mFront)
    , mBack(other.mBack)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    unsetArrayQueue(other);
}

template<typename T>
inline TArrayQueue<T>& TArrayQueue<T>::operator=(const TArrayQueue<T>& other)
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

        memcpy(mpData, other.mpData, sizeof(T) * other.mSize);

        mFront = other.mFront;
        mBack = other.mBack;
    }

    return *this;
}

template<typename T>
inline TArrayQueue<T>& TArrayQueue<T>::operator=(TArrayQueue<T>&& other)
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

        mFront = other.mFront;
        mBack = other.mBack;

        unsetArrayQueue(other);
    }

    return *this;
}

template<typename T>
inline int TArrayQueue<T>::GetSize() const
{
    return mSize;
}

template<typename T>
inline bool TArrayQueue<T>::IsFull() const
{
    return mSize == mCapacity;
}

template<typename T>
inline void TArrayQueue<T>::Enqueue(T item)
{
    if (IsFull())
    {
        TArrayQueue<int> tmp = *this;

        delete[] mpData;

        mCapacity *= 2;
        mSize = 0;

        mFront = 0;
        mBack = 0;

        mpData = new T[mCapacity];

        while (tmp.GetSize() != 0)
        {
            Enqueue(tmp.PeekFront());
            tmp.Dequeue();
        }
    }

    mpData[mBack] = item;

    mBack = (mBack + 1) % mCapacity;

    ++mSize;
}

template<typename T>
inline void TArrayQueue<T>::Dequeue()
{
    assert(mSize > 0);

    mFront = (mFront + 1) % mCapacity;

    --mSize;
}

template<typename T>
inline T& TArrayQueue<T>::PeekFront()
{
    assert(mSize > 0);

    return mpData[mFront];
}

template<typename T>
inline T& TArrayQueue<T>::PeekBack()
{
    assert(mSize > 0);

    return mpData[(mBack - 1 + mCapacity) % mCapacity];
}

template<typename T>
inline void TArrayQueue<T>::unsetArrayQueue(TArrayQueue<T>& queue)
{
    queue.mpData = nullptr;

    queue.mCapacity = -1;
    queue.mSize = -1;
}
