#pragma once

class BinarySearchTree final
{
private:
    class Node final
    {
    public:
        Node(const int key)
            : Key(key)
            , pLeft(nullptr)
            , pRight(nullptr)
        {
        }

    public:
        int Key;

        Node* pLeft;
        Node* pRight;
    };

public:
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other) = delete;
    BinarySearchTree(BinarySearchTree& other) = delete;
    BinarySearchTree(BinarySearchTree&& other) = delete;
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;
    BinarySearchTree& operator=(BinarySearchTree&& other) = delete;

    int GetSize() const;

    bool HasKey(const int key) const;
    void InsertKey(const int key);
    void RemoveKey(const int key);

private:
    Node* mpRoot;

    int mSize;

private:
    BinarySearchTree::Node* destroyRecursive(Node* const pNodeOrNull);
    const BinarySearchTree::Node* searchRecursive(const Node* const pNodeOrNull, const int key) const;
    BinarySearchTree::Node* insertKeyRecursive(Node* const pNodeOrNull, const int key);
    BinarySearchTree::Node* removeKeyRecursive(Node* const pNodeOrNull, const int key);
};