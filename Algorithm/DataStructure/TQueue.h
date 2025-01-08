#pragma once

template<typename T>
class TQueue
{
public:
    TQueue() = default;
    virtual ~TQueue() = default;
    TQueue(const TQueue<T>& other) = delete;
    TQueue(TQueue<T>&& other) = delete;
    TQueue<T>& operator=(const TQueue<T>& other) = delete;
    TQueue<T>& operator=(TQueue<T>&& other) = delete;

    virtual void Enqueue(T item) = 0;
    virtual void Dequeue() = 0;
    virtual T& PeekFront() = 0;
    virtual T& PeekBack() = 0;
};
