#include "BTree.h"

BTree::BTree(const int maxKeyCount)
    : MAX_KEY_COUNT(maxKeyCount)
    , mpRoot(nullptr)
{
    assert(maxKeyCount % 2 != 0);
}

BTree::~BTree()
{
    mpRoot = destroyRecursive(mpRoot);;
}

bool BTree::HasKey(const int key) const
{
    BNode* pNode = mpRoot;
    while (pNode != nullptr)
    {
        if (findKeyIndex(pNode, key) != -1)
        {
            return true;
        }

        int i;
        for (i = 0; i < pNode->Keys.size(); ++i)
        {
            if (key < pNode->Keys[i])
            {
                break;
            }
        }

        pNode = pNode->Children[i];
    }

    return false;
}

void BTree::InsertKey(const int key)
{
    if (mpRoot == nullptr)
    {
        mpRoot = new BNode(MAX_KEY_COUNT);
    }

    BNode* parent = nullptr;
    BNode* pNode = mpRoot;

    while (pNode != nullptr)
    {
        if (findKeyIndex(pNode, key) >= 0)
        {
            return;
        }

        if (pNode->Keys.size() == MAX_KEY_COUNT)
        {
            pNode = splitNode(parent, key);
        }

        parent = pNode;

        int i;
        for (i = 0; i < pNode->Keys.size(); ++i)
        {
            if (key < pNode->Keys[i])
            {
                break;
            }
        }

        pNode = pNode->Children[i];
    }

    addKey(parent, key, nullptr, nullptr);
}

void BTree::RemoveKey(const int key)
{
    BNode* pParent = nullptr;
    BNode* pNode = mpRoot;

    int parentIndex = 0;
    int nodeIndex = -1;

    int currKey = key;
    while (pNode != nullptr)
    {
        if (pNode->Keys.size() <= MAX_KEY_COUNT / 2 && pParent != nullptr)
        {
            if (!tryBorrowKey(pParent, parentIndex))
            {
                pNode = bindNode(pParent, parentIndex);
            }
        }

        nodeIndex = findKeyIndex(pNode, currKey);
        if (nodeIndex >= 0)
        {
            if (pNode->Children[0] == nullptr)
            {
                break;
            }

            makeSwap(pNode, nodeIndex, currKey);
        }

        pParent = pNode;
        for (parentIndex = 0; parentIndex < pNode->Keys.size(); ++parentIndex)
        {
            if (currKey < pNode->Keys[parentIndex])
            {
                break;
            }
        }

        pNode = pNode->Children[parentIndex];
    }

    if (pNode == nullptr)
    {
        return;
    }

    if (pNode->Keys.size() <= MAX_KEY_COUNT / 2 && pParent != nullptr)
    {
        if (!tryBorrowKey(pParent, parentIndex))
        {
            pNode = bindNode(pParent, parentIndex);
        }
    }

    eraseKey(pNode, findKeyIndex(pNode, currKey));
}

void BTree::PrintTree() const
{
    assert(mpRoot != nullptr);

    printTreeRecursive(mpRoot, 0);
}

BTree::BNode* BTree::destroyRecursive(BNode* const pNodeOrNull)
{
    if (pNodeOrNull != nullptr)
    {
        for (BNode*& pChild : pNodeOrNull->Children)
        {
            pChild = destroyRecursive(pChild);
        }

        delete pNodeOrNull;
    }

    return nullptr;
}

int BTree::findKeyIndex(const BNode* const pNode, const int key) const
{
    assert(pNode != nullptr);

    for (int i = 0; i < pNode->Keys.size(); ++i)
    {
        if (pNode->Keys[i] == key)
        {
            return i;
        }
    }

    return -1;
}

void BTree::addKey(BNode* const pNode, const int key, BNode* const pLeftOrNull, BNode* const pRightOrNull)
{
    assert(pNode != nullptr);

    int index = static_cast<int>(pNode->Keys.size());
    while (index > 0 && pNode->Keys[index - 1] > key)
    {
        pNode->Children[index + 1] = pNode->Children[index];
        --index;
    }

    pNode->Keys.insert(pNode->Keys.begin() + index, key);
    pNode->Children[index] = pLeftOrNull;
    pNode->Children[index + 1] = pRightOrNull;
}

BTree::BNode* BTree::splitNode(BNode* const pPivotOrNull, const int key)
{
    assert(mpRoot != nullptr);

    BNode* pLeft = nullptr;
    BNode* pRight = new BNode(MAX_KEY_COUNT);
    BNode* pChild = nullptr;

    if (pPivotOrNull == nullptr)
    {
        pChild = mpRoot;
        pLeft = new BNode(MAX_KEY_COUNT);

        const int mid = MAX_KEY_COUNT / 2;

        int i;
        for (i = 0; i < mid; ++i)
        {
            pLeft->Keys.push_back(pChild->Keys[i]);
            pLeft->Children[i] = pChild->Children[i];
        }
        pLeft->Children[i] = pChild->Children[i];

        for (++i; i < MAX_KEY_COUNT; ++i)
        {
            pRight->Keys.push_back(pChild->Keys[i]);
            pRight->Children[i - mid - 1] = pChild->Children[i];
        }
        pRight->Children[i - mid - 1] = pChild->Children[i];

        const int midKey = pChild->Keys[mid];

        pChild->Keys.clear();
        std::fill(pChild->Children.begin(), pChild->Children.end(), nullptr);

        addKey(pChild, midKey, pLeft, pRight);
    }
    else
    {
        int i;
        for (i = 0; i < pPivotOrNull->Keys.size(); ++i)
        {
            if (key < pPivotOrNull->Keys[i])
            {
                break;
            }
        }
        pLeft = pPivotOrNull->Children[i];

        const int mid = MAX_KEY_COUNT / 2;

        for (i = mid + 1; i < MAX_KEY_COUNT; ++i)
        {
            pRight->Keys.push_back(pLeft->Keys[i]);
            pRight->Children[i - mid - 1] = pLeft->Children[i];

            pLeft->Children[i] = nullptr;
        }
        pRight->Children[i - mid - 1] = pLeft->Children[i];
        pLeft->Children[i] = nullptr;

        const int midKey = pLeft->Keys[mid];

        pLeft->Keys.resize(mid);

        addKey(pPivotOrNull, midKey, pLeft, pRight);

        pChild = pPivotOrNull;
    }

    return pChild;
}

void BTree::eraseKey(BNode* const pNode, const int index)
{
    assert(pNode != nullptr);
    assert(index >= 0);

    pNode->Keys.erase(pNode->Keys.begin() + index);

    for (int i = index + 1; i < pNode->Children.size(); ++i)
    {
        pNode->Children[i - 1] = pNode->Children[i];
    }

    pNode->Children[pNode->Keys.size() + 1] = nullptr;
}

bool BTree::tryBorrowKey(BNode* const pNode, const int index)
{
    assert(pNode != nullptr);
    assert(index >= 0);

    int from = -1;
    int to = -1;
    if (pNode->Keys.size() == index)
    {
        from = index - 1;
        to = index;
    }
    else
    {
        from = index + 1;
        to = index;
    }

    BNode* pFrom = pNode->Children[from];
    BNode* pTo = pNode->Children[to];

    if (pFrom == nullptr || pFrom->Keys.size() <= MAX_KEY_COUNT / 2)
    {
        return false;
    }

    if (from > to)
    {
        addKey(pTo, pNode->Keys[to], pTo->Children[pTo->Keys.size()], pFrom->Children[0]);
        pNode->Keys[to] = pFrom->Keys[0];

        eraseKey(pFrom, 0);
    }
    else
    {
        addKey(pTo, pNode->Keys[from], pFrom->Children[pFrom->Keys.size()], pTo->Children[0]);
        pNode->Keys[from] = pFrom->Keys[pFrom->Keys.size() - 1];

        eraseKey(pFrom, static_cast<int>(pFrom->Keys.size() - 1));
    }

    return true;
}

BTree::BNode* BTree::bindNode(BNode* const pNode, const int index)
{
    assert(pNode != nullptr);
    assert(index >= 0);

    BNode* pLeft = nullptr;
    BNode* pRight = nullptr;

    int idx = index;
    if (index == pNode->Keys.size())
    {
        --idx;
    }

    pLeft = pNode->Children[idx];
    pRight = pNode->Children[idx + 1];

    pLeft->Keys.push_back(pNode->Keys[idx]);

    int i;
    for (i = 0; i < pRight->Keys.size(); ++i)
    {
        pLeft->Children[pLeft->Keys.size()] = pRight->Children[i];
        pLeft->Keys.push_back(pRight->Keys[i]);
    }
    pLeft->Children[pLeft->Keys.size()] = pRight->Children[i];

    eraseKey(pNode, idx);

    pNode->Children[idx] = pLeft;

    delete pRight;

    if (pNode->Keys.size() == 0)
    {
        delete pNode;

        mpRoot = pLeft;
    }

    return pLeft;
}

void BTree::makeSwap(BNode* const pNode, const int index, int& outKey)
{
    assert(pNode != nullptr);
    assert(index >= 0);

    BNode* pCenterSide = pNode;
    BNode* pCenter = pCenterSide->Children[index + 1];

    while (pCenter->Children[0] != nullptr)
    {
        pCenterSide = pCenter;
        pCenter = pCenter->Children[0];
    }

    pNode->Keys[index] = pCenter->Keys[0];
    outKey = pCenter->Keys[0];
}

void BTree::printTreeRecursive(const BNode* const pNodeOrNull, const int depth) const
{
    assert(depth >= 0);

    if (pNodeOrNull == nullptr)
    {
        return;
    }

    for (int i = 0; i < depth; ++i)
    {
        std::cout << "    ";
    }
    std::cout << "* ";

    for (const int key : pNodeOrNull->Keys)
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i <= pNodeOrNull->Keys.size(); ++i)
    {
        printTreeRecursive(pNodeOrNull->Children[i], depth + 1);
    }
}
