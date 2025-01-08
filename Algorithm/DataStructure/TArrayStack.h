#pragma once

#include <cassert>
#include <cstring>

#include "TStack.h"

template<typename T>
class TArrayStack final : public TStack<T>
{
public:
    TArrayStack(const int capacity);
    ~TArrayStack() override;
    TArrayStack(const TArrayStack<T>& other);
    TArrayStack(TArrayStack<T>&& other);
    TArrayStack<T>& operator=(const TArrayStack<T>& other);
    TArrayStack<T>& operator=(TArrayStack<T>&& other);

    int GetSize() const override;
    bool IsFull() const;

    void Push(T item) override;
    void Pop() override;
    T& Peek() override;

private:
    T* mpData;

    int mCapacity;
    int mSize;

private:
    void unsetArrayStack(TArrayStack<T>& stack);
};

template<typename T>
inline TArrayStack<T>::TArrayStack(const int capacity)
    : mpData(nullptr)
    , mCapacity(capacity)
    , mSize(0)
{
    assert(capacity > 0);

    mpData = new T[capacity];
}

template<typename T>
inline TArrayStack<T>::~TArrayStack()
{
    delete[] mpData;

    unsetArrayStack(*this);
}

template<typename T>
inline TArrayStack<T>::TArrayStack(const TArrayStack<T>& other)
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
inline TArrayStack<T>::TArrayStack(TArrayStack<T>&& other)
    : mpData(other.mpData)
    , mCapacity(other.mCapacity)
    , mSize(other.mSize)
{
    assert(other.mpData != nullptr);
    assert(other.mCapacity > 0);
    assert(other.mSize >= 0);

    unsetArrayStack(other);
}

template<typename T>
inline TArrayStack<T>& TArrayStack<T>::operator=(const TArrayStack<T>& other)
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
    }

    return *this;
}

template<typename T>
inline TArrayStack<T>& TArrayStack<T>::operator=(TArrayStack<T>&& other)
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

        unsetArrayStack(other);
    }

    return *this;
}

template<typename T>
inline int TArrayStack<T>::GetSize() const
{
    return mSize;
}

template<typename T>
inline bool TArrayStack<T>::IsFull() const
{
    return mSize == mCapacity;
}

template<typename T>
inline void TArrayStack<T>::Push(T item)
{
    if (IsFull())
    {
        mCapacity *= 2;

        T* pNewData = new T[mCapacity];

        memcpy(pNewData, mpData, sizeof(T) * mSize);

        delete[] mpData;

        mpData = pNewData;
    }

    mpData[mSize++] = item;
}

template<typename T>
inline void TArrayStack<T>::Pop()
{
    assert(mSize > 0);

    --mSize;
}

template<typename T>
inline T& TArrayStack<T>::Peek()
{
    assert(mSize > 0);

    return mpData[mSize - 1];
}

template<typename T>
inline void TArrayStack<T>::unsetArrayStack(TArrayStack<T>& stack)
{
    stack.mpData = nullptr;

    stack.mCapacity = -1;
    stack.mSize = -1;
}
