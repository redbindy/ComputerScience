#pragma once

#include <cassert>
#include <utility>

#include "TStack.h"
#include "TLinkedList.h"

template<typename T>
class TLinkedStack final : public TStack<T>
{
public:
    TLinkedStack() = default;
    ~TLinkedStack() = default;
    TLinkedStack(const TLinkedStack<T>& other);
    TLinkedStack(TLinkedStack<T>&& other);
    TLinkedStack<T>& operator=(const TLinkedStack<T>& other);
    TLinkedStack<T>& operator=(TLinkedStack<T>&& other);

    int GetSize() const;

    void Push(T item) override;
    void Pop() override;
    T& Peek() override;

private:
    TLinkedList<T> mList;
};

template<typename T>
inline TLinkedStack<T>::TLinkedStack(const TLinkedStack<T>& other)
    : mList(other.mList)
{

}

template<typename T>
inline TLinkedStack<T>::TLinkedStack(TLinkedStack<T>&& other)
    : mList(std::move(other.mList))
{
}

template<typename T>
inline TLinkedStack<T>& TLinkedStack<T>::operator=(const TLinkedStack<T>& other)
{
    mList = other.mList;

    return *this;
}

template<typename T>
inline TLinkedStack<T>& TLinkedStack<T>::operator=(TLinkedStack<T>&& other)
{
    mList = std::move(other.mList);

    return *this;
}

template<typename T>
inline int TLinkedStack<T>::GetSize() const
{
    return mList.GetSize();
}

template<typename T>
inline void TLinkedStack<T>::Push(T item)
{
    mList.AddFront(item);
}

template<typename T>
inline void TLinkedStack<T>::Pop()
{
    assert(mList.GetSize() > 0);

    mList.Remove(mList.GetHeadItem());
}

template<typename T>
inline T& TLinkedStack<T>::Peek()
{
    assert(mList.GetSize() > 0);

    return mList.GetHeadItem();
}


