#include "TopologicalSorting.h"

using namespace TopologicalSorting;

void TopologicalSorting::PrintTopologicalSorting(const std::vector<Node<const char*>*>& graph)
{
    int* const pInDegrees = new int[graph.size()];
    memset(pInDegrees, 0, sizeof(int) * graph.size());
    {
        for (const Node<const char*>* const pNode : graph)
        {
            for (const Node<const char*>* const p : pNode->neighbors)
            {
                ++pInDegrees[p->id];
            }
        }

        std::stack<const Node<const char*>*> stack;
        for (int i = 0; i < graph.size(); ++i)
        {
            if (pInDegrees[i] == 0)
            {
                stack.push(graph[i]);
            }
        }

        while (!stack.empty())
        {
            const Node<const char*>* const p = stack.top();
            stack.pop();

            std::cout << p->data << " -> ";

            for (const Node<const char*>* const pNeighbor : p->neighbors)
            {
                --pInDegrees[pNeighbor->id];

                if (pInDegrees[pNeighbor->id] == 0)
                {
                    stack.push(pNeighbor);
                }
            }
        }

        std::cout << std::endl;
    }
    delete[] pInDegrees;
}

template<typename T>
static void topologicalSortingRecursive(
    const std::vector<Node<T>*>& graph,
    const int id,
    bool* pbDiscovered,
    std::stack<const Node<T>*>& outStack
)
{
    assert(id >= 0);
    assert(pbDiscovered != nullptr);

    if (pbDiscovered[id])
    {
        return;
    }

    pbDiscovered[id] = true;

    for (const Node<T>* const pNeighbor : graph[id]->neighbors)
    {
        topologicalSortingRecursive(graph, pNeighbor->id, pbDiscovered, outStack);
    }

    outStack.push(graph[id]);
}

void TopologicalSorting::PrintTopologicalSortingDFS(const std::vector<Node<const char*>*>& graph)
{
    bool* pbDiscovered = new bool[graph.size()];
    memset(pbDiscovered, false, sizeof(bool) * graph.size());
    {
        std::stack<const Node<const char*>*> stack;
        for (int i = 0; i < graph.size(); ++i)
        {
            topologicalSortingRecursive(graph, i, pbDiscovered, stack);
        }

        while (!stack.empty())
        {
            std::cout << stack.top()->data << " -> ";
            stack.pop();
        }
        std::cout << std::endl;
    }
    delete[] pbDiscovered;
}

void TopologicalSorting::PrintDAGShortestPath(const std::vector<Node<int>*>& graph, const int start)
{
    assert(start >= 0 && start < graph.size());

    int* pDistances = new int[graph.size()];
    for (int* p = pDistances; p < pDistances + graph.size(); ++p)
    {
        *p = UINT16_MAX;
    }

    bool* pbDiscovered = new bool[graph.size()];
    memset(pbDiscovered, false, sizeof(bool) * graph.size());
    {
        std::stack<const Node<int>*> stack;
        for (int i = 0; i < graph.size(); ++i)
        {
            topologicalSortingRecursive(graph, i, pbDiscovered, stack);
        }

        pDistances[start] = 0;

        while (!stack.empty())
        {
            const Node<int>* const pNode = stack.top();
            stack.pop();

            for (const Node<int>* const pNeighbor : pNode->neighbors)
            {
                const int newDistance = pDistances[pNode->id] + pNeighbor->data;
                if (newDistance < pDistances[pNeighbor->id])
                {
                    pDistances[pNeighbor->id] = newDistance;
                }
            }
        }

        for (int* p = pDistances; p < pDistances + graph.size(); ++p)
        {
            std::cout << *p << ' ';
        }
        std::cout << std::endl;
    }
    delete[] pbDiscovered;
    delete[] pDistances;
}
