#include <iostream>
#include <cassert>
#include <utility>
#include <algorithm>

#include "DataStructure/TArray.h"
#include "DataStructure/TArrayStack.h"
#include "DataStructure/TArrayQueue.h"
#include "DataStructure/TLinkedList.h"
#include "DataStructure/TLinkedStack.h"
#include "DataStructure/TLinkedQueue.h"
#include "Sort/Sort.h"
#include "Selection/Selection.h"
#include "SearchTree/BinarySearchTree.h"
#include "SearchTree/RedBlackTree.h"
#include "SearchTree/BTree.h"
#include "HashTable/TChainedHashTable.h"
#include "HashTable/TLinearHashTable.h"

void TestTArray();
void TestStack();
void TestQueue();
void TestLinkedList();
void TestSort();
void TestSelection();
void TestSearchTree();
void TestHashTable();

int main()
{
    // TestTArray();
    // TestStack();
    // TestQueue();
    // TestLinkedList();
    // TestSort();
    // TestSelection();
    // TestSearchTree();
    TestHashTable();
}

void TestTArray()
{
    TArray<int> arr(3);

    assert(!arr.IsFull());

    arr.Add(1);
    arr.Add(2);
    arr.Add(3);

    assert(arr[1] == 2);
    assert(arr.IsFull());

    arr[1] = 0;
    assert(arr[1] == 0);

    arr.Add(4);
    assert(arr.GetCapacity() == 6);
    assert(arr.GetSize() == 4);

    arr.Insert(0, 0);
    assert(arr.GetSize() == 5);

    arr.Remove(0);
    assert(arr[2] == 3);
    assert(arr.GetSize() == 4);

    arr.RemoveAt(1);
    assert(arr[1] == 3);
    assert(arr.GetSize() == 3);

    TArray<int> arr1 = arr;

    arr = std::move(arr1);
}

void TestStack()
{
    {
        TArrayStack<int> stack(3);

        stack.Push(3);
        stack.Push(2);
        stack.Push(1);

        assert(stack.IsFull());

        assert(stack.Peek() == 1);

        stack.Pop();
        assert(stack.Peek() == 2);
        assert(stack.GetSize() == 2);

        stack.Push(0);
        stack.Push(4);

        TArrayStack<int> stack1 = stack;

        stack = std::move(stack1);
    }

    {
        TLinkedStack<int> stack;

        stack.Push(3);
        stack.Push(2);
        stack.Push(1);

        assert(stack.Peek() == 1);

        stack.Pop();
        assert(stack.Peek() == 2);
        assert(stack.GetSize() == 2);

        stack.Push(0);
        stack.Push(4);

        TLinkedStack<int> stack1 = stack;

        stack = std::move(stack1);
    }
}

void TestQueue()
{
    {
        TArrayQueue<int> queue(3);

        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);

        assert(queue.IsFull());

        assert(queue.PeekFront() == 1);
        assert(queue.PeekBack() == 3);

        queue.Dequeue();
        assert(queue.PeekFront() == 2);
        assert(queue.GetSize() == 2);

        queue.Enqueue(4);
        queue.Enqueue(5);

        TArrayQueue<int> queue1 = queue;

        queue = std::move(queue1);
    }

    {
        TLinkedQueue<int> queue;

        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);

        assert(queue.PeekFront() == 1);
        assert(queue.PeekBack() == 3);

        queue.Dequeue();
        assert(queue.PeekFront() == 2);
        assert(queue.GetSize() == 2);

        queue.Enqueue(4);
        queue.Enqueue(5);

        TLinkedQueue<int> queue1 = queue;

        queue = std::move(queue1);
    }
}

void TestLinkedList()
{
    TLinkedList<int> linkedList;
    linkedList.AddFront(1);
    linkedList.AddFront(2);
    linkedList.AddFront(3);

    assert(linkedList.GetSize() == 3);

    linkedList.AddBack(3);
    linkedList.AddBack(2);
    linkedList.AddBack(1);

    assert(linkedList.GetSize() == 6);

    linkedList.Remove(1);

    assert(linkedList.GetSize() == 5);

    TLinkedList<int> linkedList1 = linkedList;

    linkedList = std::move(linkedList1);
}

void TestSort()
{
    Sort<int>* pSort = Sort<int>::GetInstance();
    {
        std::vector<int> raw = { 5, 3, 10, 1, 6 };

        std::vector<int> data = raw;
        pSort->SortSelection(data);

        data = raw;
        pSort->SortBubble(data);

        data = raw;
        pSort->SortInsertion(data);

        data = raw;
        pSort->SortMerge(data);

        data = raw;
        pSort->SortQuick(data);

        data = raw;
        pSort->SortHeap(data);

        std::vector<uint32_t> nums = { 123, 2154, 222, 4, 283, 1560, 1061, 2150 };
        pSort->SortRadix(nums, 10);

        data = raw;
        pSort->SortCounting(data);
    }
    Sort<int>::DeleteInstance();
}

void TestSelection()
{
    using namespace Selection;

    std::vector<int> v = { 31, 8, 48, 73, 11, 3, 20, 29, 65, 15 };
    std::vector<int> sortedV = v;

    std::sort(sortedV.begin(), sortedV.end());

    assert(SelectKthNum(v, 2) == sortedV[1]);

    assert(SelectLinear(v, 2) == sortedV[1]);
}

void TestSearchTree()
{
    {
        BinarySearchTree bst;

        bst.InsertKey(3);
        bst.InsertKey(5);
        bst.InsertKey(4);
        bst.InsertKey(2);
        bst.InsertKey(1);
        bst.InsertKey(6);

        assert(bst.HasKey(3));
        assert(bst.HasKey(5));
        assert(bst.HasKey(4));
        assert(bst.HasKey(2));
        assert(bst.HasKey(1));
        assert(bst.HasKey(6));


        assert(bst.GetSize() == 6);

        bst.RemoveKey(5);
        assert(!bst.HasKey(5));
        assert(bst.GetSize() == 5);

        bst.RemoveKey(2);
        assert(!bst.HasKey(2));
        assert(bst.GetSize() == 4);

        bst.RemoveKey(4);
        assert(!bst.HasKey(4));
        assert(bst.GetSize() == 3);
    }

#if false
    {
        {
            RedBlackTree RedBlackTree;

            for (int i = 1; i <= 21; ++i)
            {
                RedBlackTree.InsertKey(i);
                RedBlackTree.PrintTree();
            }

            for (int i = 1; i <= 7; ++i)
            {
                RedBlackTree.RemoveKey(i);
                RedBlackTree.PrintTree();
            }
        }

        {
            RedBlackTree RedBlackTree;

            for (int i = 21; i > 0; --i)
            {
                RedBlackTree.InsertKey(i);
                RedBlackTree.PrintTree();
            }

            for (int i = 21; i > 14; --i)
            {
                RedBlackTree.RemoveKey(i);
                RedBlackTree.PrintTree();
            }
        }

        {
            RedBlackTree RedBlackTree;

            RedBlackTree.InsertKey(10);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(85);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(15);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(70);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(20);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(60);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(30);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(50);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(65);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(80);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(90);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(40);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(5);
            RedBlackTree.PrintTree();

            RedBlackTree.InsertKey(55);
            RedBlackTree.PrintTree();
        }
    }
#endif

    {
        constexpr int MAX_KEY_COUNT = 5;

        BTree bTree(MAX_KEY_COUNT);

        for (int i = 1; i < 46; ++i)
        {
            bTree.InsertKey(i);
            bTree.PrintTree();
        }

        for (int i = 1; i < 46; ++i)
        {
            bTree.RemoveKey(i);
            bTree.PrintTree();
        }
    }
}

void TestHashTable()
{
    constexpr int TABLE_SIZE = 7;

    const char* keys[TABLE_SIZE] = { "abc", "bac", "bca", "bacg", "acb", "cab", "ddd" };

    // chained hash table
    {
        TChainedHashTable<const char*, int> ht(TABLE_SIZE);

        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            ht.Insert(keys[i], i);
        }

        int v;
        assert(ht.TryGetValue("abc", v));
        assert(v == 0);

        assert(ht["abc"] == 0);

        assert(ht.ContainsKey("ddd"));

        ht.RemoveKey("bac");
        assert(!ht.TryGetValue("bac", v));

        ht["bacg"] = 100;
    }

    // linear hash table
    {
        TLinearHashTable<const char*, int> ht(TABLE_SIZE);

        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            ht.Insert(keys[i], i);
        }

        int v;
        assert(ht.TryGetValue("abc", v));
        assert(v == 0);

        assert(ht["abc"] == 0);

        assert(ht.ContainsKey("ddd"));

        ht.RemoveKey("bac");
        assert(!ht.TryGetValue("bac", v));

        ht["bacg"] = 100;
    }
}
