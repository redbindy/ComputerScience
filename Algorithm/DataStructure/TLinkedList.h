#pragma once

template<typename T>
class TLinkedList final
{
private:
    template<typename T>
    class Node final
    {
    public:
        Node(const T value)
            : Value(value)
            , pNext(nullptr)
        {

        }

    public:
        T Value;
        Node* pNext;
    };

public:
    TLinkedList();
    ~TLinkedList();
    TLinkedList(const TLinkedList<T>& other);
    TLinkedList(TLinkedList<T>&& other);
    TLinkedList<T>& operator=(const TLinkedList<T>& other);
    TLinkedList<T>& operator=(TLinkedList<T>&& other);

    int GetSize() const;

    T& GetHeadItem() const;
    T& GetTailItem() const;

    void AddFront(T item);
    void AddBack(T item);

    void Remove(T item);

private:
    Node<T>* mpHead;
    Node<T>* mpTail;

    int mSize;

private:
    void destroyNodeList();
    void unsetLinkedList(TLinkedList<T>& linkedList);
    void copyNodeList(const TLinkedList& other);
};

template<typename T>
inline TLinkedList<T>::TLinkedList()
    : mpHead(nullptr)
    , mpTail(nullptr)
    , mSize(0)
{

}

template<typename T>
inline TLinkedList<T>::~TLinkedList()
{
    destroyNodeList();

    unsetLinkedList(*this);
}

template<typename T>
inline TLinkedList<T>::TLinkedList(const TLinkedList<T>& other)
    : mpHead(nullptr)
    , mpTail(nullptr)
    , mSize(other.mSize)
{
    assert(other.mSize >= 0);

    copyNodeList(other);
}

template<typename T>
inline TLinkedList<T>::TLinkedList(TLinkedList<T>&& other)
    : mpHead(other.mpHead)
    , mpTail(other.mpTail)
    , mSize(other.mSize)
{
    assert(other.mSize >= 0);

    unsetLinkedList(other);
}

template<typename T>
inline TLinkedList<T>& TLinkedList<T>::operator=(const TLinkedList<T>& other)
{
    if (this != &other)
    {
        destroyNodeList();

        copyNodeList(other);
    }

    return *this;
}

template<typename T>
inline TLinkedList<T>& TLinkedList<T>::operator=(TLinkedList<T>&& other)
{
    if (this != &other)
    {
        destroyNodeList();

        mpHead = other.mpHead;
        mpTail = other.mpTail;

        mSize = other.mSize;

        unsetLinkedList(other);
    }

    return *this;
}

template<typename T>
inline int TLinkedList<T>::GetSize() const
{
    return mSize;
}

template<typename T>
T& TLinkedList<T>::GetHeadItem() const
{
    return mpHead->Value;
}

template<typename T>
T& TLinkedList<T>::GetTailItem() const
{
    return mpTail->Value;
}

template<typename T>
inline void TLinkedList<T>::AddFront(T item)
{
    Node<T>* const pNewNode = new Node<T>(item);

    pNewNode->pNext = mpHead;

    mpHead = pNewNode;

    if (mpTail == nullptr)
    {
        mpTail = pNewNode;
    }

    ++mSize;
}

template<typename T>
inline void TLinkedList<T>::AddBack(T item)
{
    Node<T>* const pNewNode = new Node<T>(item);

    if (mpHead == nullptr)
    {
        mpHead = pNewNode;
        mpTail = pNewNode;
    }
    else
    {
        /*Node<T>* pNode = mpHead;
        while (pNode->pNext != nullptr)
        {
            pNode = pNode->pNext;
        }

        pNode->pNext = pNewNode;*/

        mpTail->pNext = pNewNode;
        mpTail = pNewNode;
    }

    ++mSize;
}

template<typename T>
inline void TLinkedList<T>::Remove(T item)
{
    if (mSize == 0)
    {
        return;
    }

    if (mpHead->Value == item)
    {
        Node<T>* pNext = mpHead->pNext;

        delete mpHead;

        if (mSize == 1)
        {
            mpTail = nullptr;
        }

        mpHead = pNext;
    }
    else
    {
        Node<T>* pPrev = mpHead;
        Node<T>* pNode = mpHead->pNext;

        while (pNode != nullptr)
        {
            if (pNode->Value == item)
            {
                Node<T>* const pNext = pNode->pNext;

                if (pNode == mpTail)
                {
                    mpTail = pPrev;
                }

                delete pNode;

                pPrev->pNext = pNext;

                break;
            }

            pPrev = pNode;
            pNode = pNode->pNext;
        }
    }

    --mSize;
}

template<typename T>
inline void TLinkedList<T>::destroyNodeList()
{
    Node<T>* pNode = mpHead;
    while (pNode != nullptr)
    {
        Node<T>* const pNext = pNode->pNext;

        delete pNode;

        pNode = pNext;
    }
}

template<typename T>
inline void TLinkedList<T>::unsetLinkedList(TLinkedList<T>& linkedList)
{
    linkedList.mpHead = nullptr;
    linkedList.mpTail = nullptr;

    linkedList.mSize = -1;
}

template<typename T>
inline void TLinkedList<T>::copyNodeList(const TLinkedList& other)
{
    assert(other.mSize >= 0);

    if (other.mSize == 0)
    {
        return;
    }

    Node<T>* pNode = other.mpHead;
    mpHead = new Node<T>(pNode->Value);

    Node<T>* pThisNode = mpHead;
    pNode = pNode->pNext;

    while (pNode != nullptr)
    {
        pThisNode->pNext = new Node<T>(pNode->Value);

        pThisNode = pThisNode->pNext;
        mpTail = pThisNode;

        pNode = pNode->pNext;
    }
}
