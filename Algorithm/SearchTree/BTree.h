#pragma once

#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

class BTree final
{
private:
    class BNode final
    {
    public:
        BNode(const int maxKeyCount)
            : Children(maxKeyCount + 1, nullptr)
        {
            Keys.reserve(maxKeyCount);
        }

    public:
        std::vector<int> Keys;
        std::vector<BNode*> Children;
    };

public:
    BTree(const int maxKeyCount);
    ~BTree();
    BTree(const BTree& other) = delete;
    BTree(BTree&& other) = delete;
    BTree& operator=(const BTree& other) = delete;
    BTree& operator=(BTree&& other) = delete;

    bool HasKey(const int key) const;
    void InsertKey(const int key);
    void RemoveKey(const int key);

    void PrintTree() const;

private:
    const int MAX_KEY_COUNT;

    BNode* mpRoot;

private:
    BTree::BNode* destroyRecursive(BNode* const pNodeOrNull);

    int findKeyIndex(const BNode* const pNode, const int key) const;
    void addKey(BNode* const pNode, const int key, BNode* const pLeftOrNull, BNode* const pRightOrNull);
    BTree::BNode* splitNode(BNode* const pPivotOrNull, const int key);
    void eraseKey(BNode* const pNode, const int index);
    bool tryBorrowKey(BNode* const pNode, const int index);
    BTree::BNode* bindNode(BNode* const pNode, const int index);
    void makeSwap(BNode* const pNode, const int index, int& outKey);

    void printTreeRecursive(const BNode* const pNodeOrNull, const int depth) const;
};