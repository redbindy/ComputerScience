#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
    : mpRoot(nullptr)
    , mSize(0)
{

}

BinarySearchTree::~BinarySearchTree()
{
    mpRoot = destroyRecursive(mpRoot);
}

int BinarySearchTree::GetSize() const
{
    return mSize;
}

bool BinarySearchTree::HasKey(const int key) const
{
    const Node* const pNode = searchRecursive(mpRoot, key);

    return pNode != nullptr;
}

void BinarySearchTree::InsertKey(const int key)
{
    mpRoot = insertKeyRecursive(mpRoot, key);

    ++mSize;
}

void BinarySearchTree::RemoveKey(const int key)
{
    mpRoot = removeKeyRecursive(mpRoot, key);
}

BinarySearchTree::Node* BinarySearchTree::destroyRecursive(Node* const pNodeOrNull)
{
    if (pNodeOrNull != nullptr)
    {
        pNodeOrNull->pLeft = destroyRecursive(pNodeOrNull->pLeft);
        pNodeOrNull->pRight = destroyRecursive(pNodeOrNull->pRight);

        delete pNodeOrNull;
    }

    return nullptr;
}

const BinarySearchTree::Node* BinarySearchTree::searchRecursive(const Node* const pNodeOrNull, const int key) const
{
    if (pNodeOrNull == nullptr)
    {
        return nullptr;
    }

    if (pNodeOrNull->Key == key)
    {
        return pNodeOrNull;
    }

    if (key < pNodeOrNull->Key)
    {
        return searchRecursive(pNodeOrNull->pLeft, key);
    }

    return searchRecursive(pNodeOrNull->pRight, key);
}

BinarySearchTree::Node* BinarySearchTree::insertKeyRecursive(Node* const pNodeOrNull, const int key)
{
    if (pNodeOrNull == nullptr)
    {
        return new Node(key);
    }

    if (key < pNodeOrNull->Key)
    {
        pNodeOrNull->pLeft = insertKeyRecursive(pNodeOrNull->pLeft, key);
    }
    else
    {
        pNodeOrNull->pRight = insertKeyRecursive(pNodeOrNull->pRight, key);
    }

    return pNodeOrNull;
}

BinarySearchTree::Node* BinarySearchTree::removeKeyRecursive(Node* const pNodeOrNull, const int key)
{
    if (pNodeOrNull == nullptr)
    {
        return nullptr;
    }

    if (pNodeOrNull->Key == key)
    {
        Node* const pLeft = pNodeOrNull->pLeft;
        Node* const pRight = pNodeOrNull->pRight;

        if (pLeft != nullptr && pRight != nullptr)
        {
            Node* pSuccessor = pRight;
            while (pSuccessor->pLeft != nullptr)
            {
                pSuccessor = pSuccessor->pLeft;
            }

            const int successorKey = pSuccessor->Key;

            pNodeOrNull->pRight = removeKeyRecursive(pRight, successorKey);

            pNodeOrNull->Key = successorKey;

            return pNodeOrNull;
        }

        delete pNodeOrNull;
        --mSize;

        if (pLeft == nullptr)
        {
            return pRight;
        }

        return pLeft;
    }

    if (key < pNodeOrNull->Key)
    {
        pNodeOrNull->pLeft = removeKeyRecursive(pNodeOrNull->pLeft, key);
    }
    else
    {
        pNodeOrNull->pRight = removeKeyRecursive(pNodeOrNull->pRight, key);
    }

    return pNodeOrNull;
}
