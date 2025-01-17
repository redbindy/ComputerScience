#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>

class RedBlackTree final
{
private:
    class RedBlackNode final
    {
    public:
        RedBlackNode(const int key)
            : RedBlackNode(key, nullptr)
        {
        }

        RedBlackNode(const int key, RedBlackNode* pNil)
            : Key(key)
            , pLeft(pNil)
            , pRight(pNil)
            , IsBlack(false)
        {
        }

        inline void SwapColor()
        {
            IsBlack = !IsBlack;
        }

    public:
        int Key;

        RedBlackNode* pLeft;
        RedBlackNode* pRight;

        bool IsBlack;
    };

public:
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree& other) = delete;
    RedBlackTree(RedBlackTree&& other) = delete;
    RedBlackTree& operator=(const RedBlackTree& other) = delete;
    RedBlackTree& operator=(RedBlackTree&& other) = delete;

    bool HasKey(const int key) const;
    void InsertKey(const int key);
    void RemoveKey(const int key);

    void PrintTree() const ;

private:
    RedBlackNode* mpRoot;
    RedBlackNode* mpNil;

private:
    RedBlackTree::RedBlackNode* destroyRecursive(RedBlackNode* const pNode);
    const RedBlackTree::RedBlackNode* searchRecursive(const RedBlackNode* const pNode, const int key) const;
    RedBlackTree::RedBlackNode* insertKeyRecursive(RedBlackNode* const pNode, const int key);
    RedBlackTree::RedBlackNode* removeKeyRecursive(RedBlackNode* const pNode, const int key, bool& outIsFinished);
    RedBlackTree::RedBlackNode* executeRemoveStrategyRecursive(RedBlackNode* const pNode, const int key, bool& outIsFinished);

    RedBlackTree::RedBlackNode* rotateLeft(RedBlackNode* const pNode);
    RedBlackTree::RedBlackNode* rotateRight(RedBlackNode* const pNode);

    void writeTreeDataRecursive(RedBlackNode* const pNode, const int depth, const int index, const int gap, std::vector<RedBlackNode*>& outScreenData) const;
};