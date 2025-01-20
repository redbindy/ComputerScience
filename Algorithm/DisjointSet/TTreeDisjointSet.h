#pragma once

#include <unordered_map>

template<typename T>
class TTreeDisjointSet
{
private:
    template<typename T>
    class Node
    {
    public:
        Node(const T& element)
            : Element(element)
            , pParent(this)
            , rank(0)
        {
        }

    public:
        T Element;

        Node* pParent;

        int rank;
    };

public:
    TTreeDisjointSet(const int capacity);
    ~TTreeDisjointSet();
    TTreeDisjointSet(const TTreeDisjointSet<T>& other) = delete;
    TTreeDisjointSet(TTreeDisjointSet<T>&& other) = default;
    TTreeDisjointSet<T>& operator=(const TTreeDisjointSet<T>& other) = delete;
    TTreeDisjointSet<T>& operator=(TTreeDisjointSet<T>&& other) = default;

    void MakeSet(const T& element);
    TTreeDisjointSet<T>::Node<T>* FindSet(const T& element);
    void Union(const T& elementLhs, const T& elementRhs);

private:
    std::unordered_map<T, Node<T>*> mSets;

private:
    TTreeDisjointSet<T>::Node<T>* findSetRecursive(const T& element);
};

template<typename T>
inline TTreeDisjointSet<T>::TTreeDisjointSet(const int capacity)
{
    mSets.reserve(capacity);
}

template<typename T>
inline TTreeDisjointSet<T>::~TTreeDisjointSet()
{
    for (std::pair<T, Node<T>*> pair : mSets)
    {
        delete pair.second;
    }

    mSets.clear();
}

template<typename T>
inline void TTreeDisjointSet<T>::MakeSet(const T& element)
{
    if (mSets.find(element) != mSets.end())
    {
        return;
    }

    Node<T>* const pNewNode = new Node<T>(element);

    mSets[element] = pNewNode;
}

template<typename T>
inline TTreeDisjointSet<T>::Node<T>* TTreeDisjointSet<T>::FindSet(const T& element)
{
    return findSetRecursive(element);
}

template<typename T>
inline void TTreeDisjointSet<T>::Union(const T& elementLhs, const T& elementRhs)
{
    Node<T>* const pLhs = FindSet(elementLhs);
    Node<T>* const pRhs = FindSet(elementRhs);

    if (pLhs->rank > pRhs->rank)
    {
        pRhs->pParent = pLhs;
    }
    else
    {
        pLhs->pParent = pRhs;

        if (pLhs->rank == pRhs->rank)
        {
            ++pRhs->rank;
        }
    }
}

template<typename T>
inline TTreeDisjointSet<T>::Node<T>* TTreeDisjointSet<T>::findSetRecursive(const T& element)
{
    Node<T>* pParent = mSets[element]->pParent;
    if (pParent->Element != element)
    {
        pParent = findSetRecursive(pParent->Element);
        mSets[element]->pParent = pParent;
    }

    return pParent;
}
