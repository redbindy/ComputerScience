#pragma once

#include <unordered_map>
#include <cassert>

template<typename T>
class TLinkedDisjointSet
{
private:
    template<typename T>
    struct Set;

    template<typename T>
    class Node
    {
    public:
        Node(const T& element)
            : Element(element)
            , pRepresentation(nullptr)
            , pNext(nullptr)
        {
        }

    public:
        T Element;

        Set<T>* pRepresentation;
        Node* pNext;
    };

    template<typename T>
    struct Set
    {
        Node<T>* pHead;
        Node<T>* pTail;

        int Size;
    };

public:
    TLinkedDisjointSet(const int capacity);
    ~TLinkedDisjointSet();
    TLinkedDisjointSet(const TLinkedDisjointSet<T>& other) = delete;
    TLinkedDisjointSet(TLinkedDisjointSet<T>&& other) = default;
    TLinkedDisjointSet<T>& operator=(const TLinkedDisjointSet<T>& other) = delete;
    TLinkedDisjointSet<T>& operator=(TLinkedDisjointSet<T>&& other) = default;

    void MakeSet(const T& element);
    TLinkedDisjointSet<T>::Node<T>* FindSet(const T& element);
    void Union(const T& elementLhs, const T& elementRhs);

private:
    std::unordered_map<T, Node<T>*> mSets;

private:
    TLinkedDisjointSet<T>::Node<T>* destroyListRecursive(Node<T>* const pNodeOrNull);
};

template<typename T>
inline TLinkedDisjointSet<T>::TLinkedDisjointSet(const int capacity)
{
    mSets.reserve(capacity);
}

template<typename T>
inline TLinkedDisjointSet<T>::~TLinkedDisjointSet()
{
    for (std::pair<T, Node<T>*> pairs : mSets)
    {
        Node<T>* pNode = pairs.second;

        if (pNode == nullptr)
        {
            continue;
        }

        pNode = pNode->pRepresentation->pHead;
        delete pNode->pRepresentation;

        pNode = destroyListRecursive(pNode);

    }

    mSets.clear();
}

template<typename T>
inline void TLinkedDisjointSet<T>::MakeSet(const T& element)
{
    Node<T>* pNode = FindSet(element);

    if (pNode != nullptr)
    {
        return;
    }

    pNode = new Node<T>(element);

    Set<T>* const pSet = new Set<T>;
    pSet->pHead = pNode;
    pSet->pTail = pNode;
    pSet->Size = 1;

    pNode->pRepresentation = pSet;

    mSets[element] = pNode;
}

template<typename T>
TLinkedDisjointSet<T>::Node<T>* TLinkedDisjointSet<T>::FindSet(const T& element)
{
    if (mSets.find(element) != mSets.end())
    {
        return mSets[element]->pRepresentation->pHead;
    }

    return nullptr;
}

template<typename T>
inline void TLinkedDisjointSet<T>::Union(const T& elementLhs, const T& elementRhs)
{
    assert(mSets.find(elementLhs) != mSets.end());
    assert(mSets.find(elementRhs) != mSets.end());

    Node<T>* const pLhs = FindSet(elementLhs);
    Node<T>* const pRhs = FindSet(elementRhs);

    if (pLhs == pRhs)
    {
        return;
    }

    Set<T>* const pLhsSet = pLhs->pRepresentation;
    Set<T>* const pRhsSet = pRhs->pRepresentation;

    Set<T>* pRepreSet;
    Set<T>* pAppendingSet;
    if (pLhsSet->Size < pRhsSet->Size)
    {
        pRepreSet = pRhsSet;
        pAppendingSet = pLhsSet;
    }
    else
    {
        pRepreSet = pLhsSet;
        pAppendingSet = pRhsSet;
    }

    pRepreSet->pTail->pNext = pAppendingSet->pHead;
    pRepreSet->pTail = pAppendingSet->pTail;
    pRepreSet->Size += pAppendingSet->Size;

    Node<T>* p = pAppendingSet->pHead;
    while (p != nullptr)
    {
        p->pRepresentation = pRepreSet;

        p = p->pNext;
    }

    delete pAppendingSet;
}

template<typename T>
inline TLinkedDisjointSet<T>::Node<T>* TLinkedDisjointSet<T>::destroyListRecursive(Node<T>* const pNodeOrNull)
{
    if (pNodeOrNull != nullptr)
    {
        pNodeOrNull->pNext = destroyListRecursive(pNodeOrNull->pNext);
        mSets[pNodeOrNull->Element] = nullptr;

        delete pNodeOrNull;
    }

    return nullptr;
}