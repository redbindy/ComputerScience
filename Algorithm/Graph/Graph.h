#pragma once

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <stack>
#include <queue>
#include <cstring>

#include "../DisjointSet/TTreeDisjointSet.h"

enum
{
    DEFAULT_NEIGHBOR_NUMS = 8
};

class Graph
{
private:
    struct Edge
    {
        int from;
        int to;
        int weight;
    };

    struct compare
    {
        bool operator()(const Edge& e0, const Edge& e1)
        {
            return e0.weight > e1.weight;
        }
    };

    class Node
    {
    public:
        Node(const int id)
            : Id(id)
        {
        }

    public:
        int Id;

        std::list<Edge> Edges;
        // std::vector<Edge>
        // std::unordered_set<Edge>
    };

public:
    Graph(const int capacity);
    ~Graph();
    Graph(const Graph& other) = default;
    Graph(Graph&& other) = default;
    Graph& operator=(const Graph& other) = default;
    Graph& operator=(Graph&& other) = default;

    inline int GetNodeCount() const;
    inline int GetEdgeCount() const;

    void AddNode();

    void AddDirectedEdge(const int from, const int to);
    void AddDirectedEdge(const int from, const int to, const int weight);
    void AddUndirectedEdge(const int from, const int to);
    void AddUndirectedEdge(const int from, const int to, const int weight);

    void RemoveNode(const int id);
    void RemoveDirectedEdge(const int from, const int to);
    void RemoveUndirectedEdge(const int from, const int to);
    void PrintDFS() const;
    void PrintBFS() const;

    int SolveMSTPrim() const;
    int SolveMSTKruskal() const;

    void PrintTopologicalSorting() const;

    void PrintDijkstra(const int start) const;
    void PrintBellmanFord(const int start) const;
    void PrintFloydWarshall() const;

    void PrintSCCKosaraju() const;

private:
    // std::unordered_map<Node*>
    std::vector<Node*> mAdjacentList;
    std::vector<int> mInDegrees;
    
    int mEdgeCount;

private:
    void printDFSRecursive(const int id, bool* const bDiscovered) const;

    void searchDepthFirstPostOrderRecursive(const int id, bool* const bDiscovered, std::stack<int>& outStack) const;
};

int Graph::GetNodeCount() const
{
    return static_cast<int>(mAdjacentList.size());
}

int Graph::GetEdgeCount() const
{
    return mEdgeCount;
}