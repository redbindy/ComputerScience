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
#include "DisjointSet/TLinkedDisjointSet.h"
#include "DisjointSet/TTreeDisjointSet.h"
#include "DynamicProgramming/DynamicProgramming.h"
#include "Graph/Graph.h"
#include "Graph/TopologicalSorting.h"

void TestTArray();
void TestStack();
void TestQueue();
void TestLinkedList();
void TestSort();
void TestSelection();
void TestSearchTree();
void TestHashTable();
void TestDisjointSet();
void TestDynamicProgramming();
void TestGraph();

int main()
{
    // TestTArray();
    // TestStack();
    // TestQueue();
    // TestLinkedList();
    // TestSort();
    // TestSelection();
    // TestSearchTree();
    // TestHashTable();
    // TestDisjointSet();
    // TestDynamicProgramming();
    TestGraph();
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

void TestDisjointSet()
{
    // linked set
    {
        TLinkedDisjointSet<char> sets(8);

        for (char c = 'a'; c <= 'h'; ++c)
        {
            sets.MakeSet(c);
        }

        sets.Union('a', 'b');
        sets.Union('b', 'c');

        sets.Union('d', 'e');
        sets.Union('e', 'f');
        sets.Union('f', 'g');
        sets.Union('g', 'h');

        sets.Union('b', 'f');
    }

    // tree set
    {
        TTreeDisjointSet<char> sets(8);

        for (char c = 'a'; c <= 'h'; ++c)
        {
            sets.MakeSet(c);
        }

        sets.Union('a', 'b');
        sets.Union('a', 'c');

        sets.Union('d', 'e');
        sets.Union('d', 'f');
        sets.Union('f', 'g');
        sets.Union('d', 'h');

        sets.Union('c', 'h');

        sets.MakeSet('i');

        sets.Union('a', 'i');
    }
}

void TestDynamicProgramming()
{
    // fibonacci
    {
        constexpr int N = 7;

        std::cout << GetFibonacciRecursive(N, 2) << std::endl;

        std::cout << GetFibonacciBottomUp(N) << std::endl;

        int sequence[N + 1];
        memset(sequence, -1, sizeof(int) * (N + 1));

        std::cout << GetFibonacciTopDownRecursive(N, sequence, 2) << std::endl;
    }

    // matrix path problem
    {
        constexpr int N = 4;

        int nums[N][N] = {
            { 6, 7, 12, 5 },
            { 5, 3, 11, 8 },
            { 7, 17, 3, 3 },
            { 8, 10, 14, 9 },
        };

        std::cout << SolveMatrixPathProblemRecursive(reinterpret_cast<int*>(nums), N, N - 1, N - 1) << std::endl;

        std::cout << SolveMatrixPathProblemBottomUp(reinterpret_cast<int*>(nums), N) << std::endl;

        int cache[N][N];
        memset(cache, -1, sizeof(int) * N * N);

        std::cout << SolveMatrixPathProblemTopDownRecursive(reinterpret_cast<int*>(nums), N, N - 1, N - 1, reinterpret_cast<int*>(cache)) << std::endl;
    }

    // pebble place problem
    {
        constexpr int N = 8;

        int nums[3][N] = {
            { 6, 7, 12, -5, 5, 3, 11, 3 },
            { -8, 10, 14, 9, 7, 13, 8, 5 },
            { 11, 12, 7, 4, 8, -2, 9, 4 }
        };

        int max = INT32_MIN;
        for (int i = 0; i < 4; ++i)
        {
            const int tmp = SolvePebblePlacementProblemRecursive(reinterpret_cast<int*>(nums), N, N - 1, static_cast<EPattern>(i));
            if (tmp > max)
            {
                max = tmp;
            }
        }
        std::cout << max << std::endl;

        std::cout << SolvePebblePlacementProblemBottomUp(reinterpret_cast<int*>(nums), N) << std::endl;

        int cache[static_cast<int>(EPattern::PATTERN_COUNT)][N];

        for (int row = 0; row < static_cast<int>(EPattern::PATTERN_COUNT); ++row)
        {
            for (int col = 0; col < N; ++col)
            {
                cache[row][col] = INT32_MIN;
            }
        }

        max = INT32_MIN;
        for (int i = 0; i < 4; ++i)
        {
            const int tmp = SolvePebblePlacementProblemTopDownRecursive(reinterpret_cast<int*>(nums), N, N - 1, static_cast<EPattern>(i), reinterpret_cast<int*>(cache));
            if (tmp > max)
            {
                max = tmp;
            }
        }
        std::cout << max << std::endl;
    }

    // matrix chain problem
    {
        constexpr int N = 5;

        const RowColSize sizes[N] = {
            { 10, 4 }, { 4, 5 }, { 5, 20 }, { 20, 2 }, { 2, 50 }
        };

        std::cout << SolveMatrixChainProblemRecursive(sizes, 0, N - 1) << std::endl;

        std::cout << SolveMatrixChainProblemBottomUp(sizes, N) << std::endl;
    }

    // LCS
    {
        const char* pStr0 = "abcbdab";
        const int len0 = static_cast<int>(strlen(pStr0));

        const char* pStr1 = "bdcaba";
        const int len1 = static_cast<int>(strlen(pStr1));

        std::cout << SolveLCSRecursive(pStr0, pStr1, len0 - 1, len1 - 1) << std::endl;

        std::cout << SolveLCSBottomUp(pStr0, pStr1) << std::endl;
    }
}

void TestGraph()
{
    {
        constexpr int NODE_COUNT = 8;

        Graph graph(NODE_COUNT);

        for (int i = 0; i < NODE_COUNT; ++i)
        {
            graph.AddNode();
        }

        graph.AddDirectedEdge(0, 1);
        graph.AddDirectedEdge(0, 2);
        graph.AddDirectedEdge(0, 3);

        graph.AddDirectedEdge(1, 0);
        graph.AddDirectedEdge(1, 2);

        graph.AddDirectedEdge(2, 1);
        graph.AddDirectedEdge(2, 0);
        graph.AddDirectedEdge(2, 3);
        graph.AddDirectedEdge(2, 4);

        graph.AddDirectedEdge(3, 0);
        graph.AddDirectedEdge(3, 2);
        graph.AddDirectedEdge(3, 5);
        graph.AddDirectedEdge(3, 6);

        graph.AddDirectedEdge(4, 2);

        graph.AddDirectedEdge(5, 3);
        graph.AddDirectedEdge(5, 6);

        graph.AddDirectedEdge(6, 3);
        graph.AddDirectedEdge(6, 5);
        graph.AddDirectedEdge(6, 7);

        graph.AddDirectedEdge(7, 6);

        graph.PrintBFS();
        graph.PrintDFS();

        graph.RemoveDirectedEdge(0, 1);
        graph.RemoveDirectedEdge(1, 0);

        graph.RemoveNode(0);
    }

    // MST
    {
        constexpr int NODE_COUNT = 7;

        Graph graph(NODE_COUNT);

        for (int i = 0; i < NODE_COUNT; ++i)
        {
            graph.AddNode();
        }

        graph.AddUndirectedEdge(0, 1, 10);
        graph.AddUndirectedEdge(0, 2, 8);
        graph.AddUndirectedEdge(1, 3, 5);
        graph.AddUndirectedEdge(2, 3, 9);
        graph.AddUndirectedEdge(2, 4, 11);
        graph.AddUndirectedEdge(3, 4, 13);
        graph.AddUndirectedEdge(3, 5, 12);
        graph.AddUndirectedEdge(4, 6, 8);
        graph.AddUndirectedEdge(5, 6, 7);

        std::cout << graph.SolveMSTPrim() << std::endl;
        std::cout << graph.SolveMSTKruskal() << std::endl;
    }

    // Topological Sorting
    {
        using namespace TopologicalSorting;

        Node<const char*> nodes[] = {
            {0, "냄비에 물 붓기" },
            {1, "라면봉지 뜯기" },
            {2, "점화"},
            {3, "수프 넣기"},
            {4, "라면 넣기"},
            {5, "계란 풀어 넣기"}
        };

        nodes[0].neighbors.push_back(nodes + 2);
        nodes[1].neighbors.push_back(nodes + 3);
        nodes[1].neighbors.push_back(nodes + 4);
        nodes[2].neighbors.push_back(nodes + 3);
        nodes[2].neighbors.push_back(nodes + 4);
        nodes[2].neighbors.push_back(nodes + 5);
        nodes[3].neighbors.push_back(nodes + 5);
        nodes[4].neighbors.push_back(nodes + 5);

        std::vector<Node<const char*>*> graph;
        graph.reserve(sizeof(nodes) / sizeof(nodes[0]));

        for (int i = 0; i < 6; ++i)
        {
            graph.push_back(nodes + i);
        }

        PrintTopologicalSorting(graph);
        PrintTopologicalSortingDFS(graph);
    }

    // shortest path - dijkstra
    {
        constexpr int NODE_COUNT = 8;

        Graph graph(NODE_COUNT);

        for (int i = 0; i < NODE_COUNT; ++i)
        {
            graph.AddNode();
        }

        graph.AddDirectedEdge(0, 1, 11);
        graph.AddDirectedEdge(0, 2, 9);
        graph.AddDirectedEdge(0, 3, 8);
        graph.AddDirectedEdge(1, 4, 8);
        graph.AddDirectedEdge(1, 5, 8);
        graph.AddDirectedEdge(2, 1, 3);
        graph.AddDirectedEdge(2, 3, 6);
        graph.AddDirectedEdge(2, 6, 1);
        graph.AddDirectedEdge(3, 6, 10);
        graph.AddDirectedEdge(4, 5, 7);
        graph.AddDirectedEdge(4, 5, 7);
        graph.AddDirectedEdge(5, 2, 12);
        graph.AddDirectedEdge(5, 7, 5);
        graph.AddDirectedEdge(5, 7, 5);
        graph.AddDirectedEdge(6, 7, 2);
        graph.AddDirectedEdge(7, 4, 4);

        graph.PrintDijkstra(0);
    }

    // shortest path - bellman ford
    {
        constexpr int NODE_COUNT = 8;

        Graph graph(NODE_COUNT);

        for (int i = 0; i < NODE_COUNT; ++i)
        {
            graph.AddNode();
        }

        graph.AddDirectedEdge(0, 1, 11);
        graph.AddDirectedEdge(0, 2, 9);
        graph.AddDirectedEdge(0, 3, 8);
        graph.AddDirectedEdge(1, 4, 8);
        graph.AddDirectedEdge(1, 5, 8);
        graph.AddDirectedEdge(2, 1, 3);
        graph.AddDirectedEdge(2, 3, -15);
        graph.AddDirectedEdge(2, 6, 1);
        graph.AddDirectedEdge(3, 6, 10);
        graph.AddDirectedEdge(4, 5, 7);
        graph.AddDirectedEdge(4, 5, -7);
        graph.AddDirectedEdge(5, 2, 12);
        graph.AddDirectedEdge(5, 7, 5);
        graph.AddDirectedEdge(5, 7, 5);
        graph.AddDirectedEdge(6, 7, 2);
        graph.AddDirectedEdge(7, 4, 4);

        graph.PrintBellmanFord(0);
    }

    // shortest path - Floyd Warshall
    {
        constexpr int NODE_COUNT = 4;

        Graph graph(NODE_COUNT);

        for (int i = 0; i < NODE_COUNT; ++i)
        {
            graph.AddNode();
        }

        graph.AddUndirectedEdge(0, 1, 1);
        graph.AddUndirectedEdge(0, 2, 6);
        graph.AddUndirectedEdge(1, 2, 3);
        graph.AddUndirectedEdge(2, 3, 5);

        graph.PrintFloydWarshall();
    }

    // shortest path - DAG topological
    {
        using namespace TopologicalSorting;

        Node<int> nodes[] = {
            { 0, 0 },
            { 1, 0 },
            { 2, 0 },
            { 3, 0 },
            { 4, 0 },
            { 5, 0 }
        };

        Node<int> n02 = { 2, 3 };
        Node<int> n03 = { 3, 7 };
        Node<int> n05 = { 5, 5 };

        nodes[0].neighbors.push_back(&n02);
        nodes[0].neighbors.push_back(&n03);
        nodes[0].neighbors.push_back(&n05);

        Node<int> n10 = { 0, 6 };
        Node<int> n13 = { 3, 5 };
        nodes[1].neighbors.push_back(&n10);
        nodes[1].neighbors.push_back(&n13);

        Node<int> n24 = { 4, 4 };
        nodes[2].neighbors.push_back(&n24);

        Node<int> n34 = { 4, -2 };
        Node<int> n35 = { 5, 1 };
        nodes[3].neighbors.push_back(&n34);
        nodes[3].neighbors.push_back(&n35);

        Node<int> n45 = { 5, -3 };
        nodes[4].neighbors.push_back(&n45);

        std::vector<Node<int>*> graph;
        graph.reserve(sizeof(nodes) / sizeof(nodes[0]));

        for (int i = 0; i < sizeof(nodes) / sizeof(nodes[0]); ++i)
        {
            graph.push_back(nodes + i);
        }

        PrintDAGShortestPath(graph, 0);
    }

    // Kosaraju's algorithm
    {
        constexpr int NODE_COUNT = 7;
        Graph graph(NODE_COUNT);

        for (int i = 0; i < NODE_COUNT; ++i)
        {
            graph.AddNode();
        }

        graph.AddDirectedEdge(0, 4);
        graph.AddDirectedEdge(4, 5);
        graph.AddDirectedEdge(5, 0);
        graph.AddDirectedEdge(0, 2);
        graph.AddDirectedEdge(2, 3);
        graph.AddDirectedEdge(3, 2);
        graph.AddDirectedEdge(6, 1);
        graph.AddDirectedEdge(1, 0);

        graph.PrintSCCKosaraju();
    }
}