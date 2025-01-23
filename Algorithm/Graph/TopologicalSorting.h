#pragma once

#include <list>
#include <vector>
#include <stack>
#include <cstring>
#include <iostream>
#include <cassert>

namespace TopologicalSorting
{
    template<typename T>
    struct Node
    {
        int id;
        T data;
        
        std::list<Node*> neighbors;
    };

    void PrintTopologicalSorting(const std::vector<Node<const char*>*>& graph);
    void PrintTopologicalSortingDFS(const std::vector<Node<const char*>*>& graph);

    void PrintDAGShortestPath(const std::vector<Node<int>*>& graph, const int start);
}