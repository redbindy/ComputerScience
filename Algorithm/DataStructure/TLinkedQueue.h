#pragma once

#include <cassert>

#include "TQueue.h"
#include "TLinkedList.h"

template<typename T>
class TLinkedQueue final : public TQueue<T>
{
public:
    TLinkedQueue() = default;
    ~TLinkedQueue() = default;
    TLinkedQueue(const TLinkedQueue<T>& other);
    TLinkedQueue(TLinkedQueue<T>&& other);
    TLinkedQueue<T>& operator=(const TLinkedQueue<T>& other);
    TLinkedQueue<T>& operator=(TLinkedQueue<T>&& other);

    int GetSize() const;

    void Enqueue(T item) override;
    void Dequeue() override;
    T& PeekFront() override;
    T& PeekBack() override;

private:
    TLinkedList<T> mList;
};

template<typename T>
inline TLinkedQueue<T>::TLinkedQueue(const TLinkedQueue<T>& other)
    : mList(other.mList)
{

}

template<typename T>
inline TLinkedQueue<T>::TLinkedQueue(TLinkedQueue<T>&& other)
    : mList(std::move(other.mList))
{

}

template<typename T>
inline TLinkedQueue<T>& TLinkedQueue<T>::operator=(const TLinkedQueue<T>& other)
{
    mList = other.mList;

    return *this;
}

template<typename T>
inline TLinkedQueue<T>& TLinkedQueue<T>::operator=(TLinkedQueue<T>&& other)
{
    mList = std::move(other.mList);

    return *this;
}

template<typename T>
inline int TLinkedQueue<T>::GetSize() const
{
    return mList.GetSize();
}

template<typename T>
inline void TLinkedQueue<T>::Enqueue(T item)
{
    mList.AddBack(item);
}

template<typename T>
inline void TLinkedQueue<T>::Dequeue()
{
    mList.Remove(mList.GetHeadItem());
}

template<typename T>
inline T& TLinkedQueue<T>::PeekFront()
{
    return mList.GetHeadItem();
}

template<typename T>
inline T& TLinkedQueue<T>::PeekBack()
{
    return mList.GetTailItem();
}
