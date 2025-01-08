#pragma once

template<typename T>
class TStack
{
public:
    TStack() = default;
    virtual ~TStack() = default;
    TStack(const TStack<T>& other) = delete;
    TStack(TStack<T>&& other) = delete;
    TStack<T>& operator=(const TStack<T>& other) = delete;
    TStack<T>& operator=(TStack<T>&& other) = delete;

    virtual int GetSize() const = 0;

    virtual void Push(T item) = 0;
    virtual void Pop() = 0;
    virtual T& Peek() = 0;
};
