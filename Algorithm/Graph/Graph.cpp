#include "Graph.h"

Graph::Graph(const int capacity)
    : mEdgeCount(0)
{
    assert(capacity > 0);

    mAdjacentList.reserve(capacity);
    mInDegrees.reserve(capacity);
}

Graph::~Graph()
{
    for (Node*& pNode : mAdjacentList)
    {
        delete pNode;

        pNode = nullptr;
    }

    mAdjacentList.clear();
}

void Graph::AddNode()
{
    const int id = static_cast<int>(mAdjacentList.size());

    mAdjacentList.push_back(new Node(id));
    mInDegrees.push_back(0);
}

void Graph::AddDirectedEdge(const int from, const int to)
{
    AddDirectedEdge(from, to, 0);
}

void Graph::AddDirectedEdge(const int from, const int to, const int weight)
{
    assert(from >= 0 && from < GetNodeCount());
    assert(to >= 0 && to < GetNodeCount());

    mAdjacentList[from]->Edges.push_back({ from, to, weight });

    for (const Edge& e : mAdjacentList[to]->Edges)
    {
        if (e.to == from)
        {
            return;
        }
    }

    ++mInDegrees[to];

    ++mEdgeCount;
}

void Graph::AddUndirectedEdge(const int from, const int to)
{
    AddDirectedEdge(from, to);
    AddDirectedEdge(to, from);
}

void Graph::AddUndirectedEdge(const int from, const int to, const int weight)
{
    AddDirectedEdge(from, to, weight);
    AddDirectedEdge(to, from, weight);
}

void Graph::RemoveNode(const int id)
{
    assert(id >= 0 && id < GetNodeCount());

    for (Node* pFrom : mAdjacentList)
    {
        std::list<Edge>& edges = pFrom->Edges;

        std::list<Edge>::iterator iter = edges.begin();
        while (iter != edges.end())
        {
            if (iter->to == id)
            {
                iter = edges.erase(iter);
                --mInDegrees[iter->to];

                continue;
            }

            ++iter;
        }
    }

    mEdgeCount -= static_cast<int>(mAdjacentList[id]->Edges.size());
    delete mAdjacentList[id];

    mAdjacentList.erase(mAdjacentList.begin() + id);
}

void Graph::RemoveDirectedEdge(const int from, const int to)
{
    assert(from >= 0 && from < GetNodeCount());
    assert(to >= 0 && to < GetNodeCount());

    std::list<Edge>& edges = mAdjacentList[from]->Edges;

    std::list<Edge>::iterator it = mAdjacentList[from]->Edges.begin();

    while (it != edges.end())
    {
        if (it->to == to)
        {
            it = edges.erase(it);

            for (const Edge& e : mAdjacentList[to]->Edges)
            {
                if (e.to == from)
                {
                    return;
                }
            }

            --mInDegrees[to];
            --mEdgeCount;

            break;
        }

        ++it;
    }
}

void Graph::RemoveUndirectedEdge(const int from, const int to)
{
    RemoveDirectedEdge(from, to);
    RemoveDirectedEdge(to, from);
}

void Graph::PrintDFS() const
{
    bool* const pbVisited = new bool[GetNodeCount()];
    memset(pbVisited, false, sizeof(bool) * GetNodeCount());

    std::stack<int> stack;
    {
        for (int i = 0; i < GetNodeCount(); ++i)
        {
            if (pbVisited[i])
            {
                continue;
            }

#if false
            printDFSRecursive(i, pbVisited);
#else
            stack.push(i);
            pbVisited[i] = true;

            while (!stack.empty())
            {
                const int id = stack.top();
                stack.pop();

                std::cout << id << ' ';

                const std::list<Edge>& edges = mAdjacentList[id]->Edges;

                std::list<Edge>::const_reverse_iterator rIter = edges.rbegin();
                while (rIter != edges.rend())
                {
                    if (!pbVisited[rIter->to])
                    {
                        stack.push(rIter->to);
                        pbVisited[rIter->to] = true;
                    }

                    ++rIter;
                }
            }
#endif
        }
    }
    delete[] pbVisited;

    std::cout << std::endl;
}

void Graph::PrintBFS() const
{
    bool* const pbVisited = new bool[GetNodeCount()];
    memset(pbVisited, false, sizeof(bool) * GetNodeCount());

    std::queue<int> queue;
    {
        for (int i = 0; i < GetNodeCount(); ++i)
        {
            if (pbVisited[i])
            {
                continue;
            }

            queue.push(i);
            pbVisited[i] = true;

            while (!queue.empty())
            {
                const int id = queue.front();
                queue.pop();

                std::cout << id << ' ';

                for (const Edge e : mAdjacentList[id]->Edges)
                {
                    if (!pbVisited[e.to])
                    {
                        queue.push(e.to);
                        pbVisited[e.to] = true;
                    }
                }
            }
        }
    }
    delete[] pbVisited;

    std::cout << std::endl;
}

int Graph::SolveMSTPrim() const
{
    TTreeDisjointSet<int> sets(GetNodeCount());
    int edgeCount = 0;

    sets.MakeSet(0);

    std::priority_queue<Edge, std::vector<Edge>, compare> pq;
    for (const Edge& e : mAdjacentList[0]->Edges)
    {
        pq.push(e);
    }

    int sum = 0;
    while (edgeCount != GetNodeCount() - 1)
    {
        const Edge e = pq.top();
        pq.pop();

        sets.MakeSet(e.to);
        if (sets.FindSet(e.from) == sets.FindSet(e.to))
        {
            continue;
        }

        sets.Union(0, e.to);

        sum += e.weight;
        ++edgeCount;

        for (const Edge& e : mAdjacentList[e.to]->Edges)
        {
            pq.push(e);
        }
    }

    return sum;
}

int Graph::SolveMSTKruskal() const
{
    TTreeDisjointSet<int> sets(GetNodeCount());
    int edgeCount = 0;

    std::priority_queue<Edge, std::vector<Edge>, compare> pq;

    bool* const bExist = new bool[GetNodeCount()];
    memset(bExist, false, sizeof(bool) * GetNodeCount());
    {
        for (int i = 0; i < GetNodeCount(); ++i)
        {
            bExist[i] = true;

            for (const Edge& e : mAdjacentList[i]->Edges)
            {
                if (bExist[e.to])
                {
                    continue;
                }

                pq.push(e);
            }
        }
    }
    delete[] bExist;

    int sum = 0;
    while (!pq.empty() && edgeCount != GetNodeCount() - 1)
    {
        const Edge e = pq.top();
        pq.pop();

        sets.MakeSet(e.from);
        sets.MakeSet(e.to);
        if (sets.FindSet(e.from) == sets.FindSet(e.to))
        {
            continue;
        }

        sets.Union(e.from, e.to);

        ++edgeCount;

        sum += e.weight;
    }

    return sum;
}

void Graph::PrintTopologicalSorting() const
{
    std::vector<int> copiedInDegrees = mInDegrees;

    const Node* pNode = nullptr;
    for (int i = 0; i < copiedInDegrees.size(); ++i)
    {
        if (copiedInDegrees[i] == 0)
        {
            pNode = mAdjacentList[i];

            break;
        }
    }

    std::stack<const Node*> stack;
    stack.push(pNode);

    while (!stack.empty())
    {
        const Node* const p = stack.top();
        stack.pop();

        std::cout << p->Id << " -> " << std::endl;

        for (const Edge& e : p->Edges)
        {
            --copiedInDegrees[e.to];

            if (copiedInDegrees[e.to] == 0)
            {
                stack.push(mAdjacentList[e.to]);
            }
        }
    }
}

void Graph::PrintDijkstra(const int start) const
{
    assert(start >= 0 && start < GetNodeCount());

    const int count = GetNodeCount();

    int* const pDistances = new int[count];
    {
        for (int* p = pDistances; p < pDistances + count; ++p)
        {
            *p = INT16_MAX;
        }

        pDistances[start] = 0;

        std::priority_queue<Edge, std::vector<Edge>, compare> pq;
        pq.push({ 0, 0, 0 });

        while (!pq.empty())
        {
            const Edge edge = pq.top();
            pq.pop();

            if (edge.weight > pDistances[edge.to])
            {
                continue;
            }

            for (const Edge& e : mAdjacentList[edge.from]->Edges)
            {
                const int newDistance = pDistances[e.from] + e.weight;
                if (newDistance < pDistances[e.to])
                {
                    pDistances[e.to] = newDistance;

                    pq.push({ e.to, e.to, newDistance });
                }
            }
        }

        for (int i = 0; i < count; ++i)
        {
            std::cout << pDistances[i] << ' ';
        }
        std::cout << std::endl;
    }
    delete[] pDistances;
}

void Graph::PrintBellmanFord(const int start) const
{
    assert(start >= 0 && start < GetNodeCount());

    const int count = GetNodeCount();

    int* const pDistances = new int[count];
    {
        for (int* p = pDistances; p < pDistances + count; ++p)
        {
            *p = INT16_MAX;
        }

        pDistances[start] = 0;

        for (int i = 0; i < count - 1; ++i)
        {
            for (const Node* const pNode : mAdjacentList)
            {
                for (const Edge& e : pNode->Edges)
                {
                    const int newDistance = pDistances[e.from] + e.weight;
                    if (newDistance < pDistances[e.to])
                    {
                        pDistances[e.to] = newDistance;
                    }
                }
            }
        }

        for (const Node* const pNode : mAdjacentList)
        {
            for (const Edge& e : pNode->Edges)
            {
                const int newDistance = pDistances[e.from] + e.weight;
                if (newDistance < pDistances[e.to])
                {
                    std::cout << "해가 없음" << std::endl;

                    return;
                }
            }
        }

        for (int i = 0; i < count; ++i)
        {
            std::cout << pDistances[i] << ' ';
        }
        std::cout << std::endl;
    }
    delete[] pDistances;
}

void Graph::PrintFloydWarshall() const
{
    const int count = GetNodeCount();

    int* pMatrix = new int[count * count];
    {
        for (int i = 0; i < count * count; ++i)
        {
            pMatrix[i] = INT16_MAX;
        }

        for (int i = 0; i < count; ++i)
        {
            const int index = i * count + i;
            pMatrix[index] = 0;
        }

        for (const Node* const pNode : mAdjacentList)
        {
            for (const Edge& e : pNode->Edges)
            {
                const int index = e.from * count + e.to;
                pMatrix[index] = e.weight;
            }
        }

        for (int mid = 0; mid < count; ++mid)
        {
            for (int from = 0; from < count; ++from)
            {
                for (int to = 0; to < count; ++to)
                {
                    const int index = from * count + to;
                    const int front = from * count + mid;
                    const int back = mid * count + to;

                    pMatrix[index] = std::min(pMatrix[index], pMatrix[front] + pMatrix[back]);
                }
            }
        }

        for (int row = 0; row < count; ++row)
        {
            for (int col = 0; col < count; ++col)
            {
                std::cout << pMatrix[row * count + col] << ' ';
            }
            std::cout << std::endl;
        }
    }
    delete[] pMatrix;
}

void Graph::PrintSCCKosaraju() const
{
    const int count = GetNodeCount();

    bool* pbDiscovered = new bool[count];
    memset(pbDiscovered, false, sizeof(bool) * count);
    {
        Graph transposed(count);
        std::stack<int> stack;
        for (int i = 0; i < count; ++i)
        {
            transposed.AddNode();
            searchDepthFirstPostOrderRecursive(i, pbDiscovered, stack);
        }

        for (const Node* const pNode : mAdjacentList)
        {
            for (const Edge& e : pNode->Edges)
            {
                transposed.AddDirectedEdge(e.to, e.from, e.weight);
            }
        }

        memset(pbDiscovered, false, sizeof(bool) * count);
        while (!stack.empty())
        {
            std::stack<int> scc;
            transposed.searchDepthFirstPostOrderRecursive(stack.top(), pbDiscovered, scc);

            stack.pop();

            while (!scc.empty())
            {
                std::cout << scc.top() << ' ';
                scc.pop();
            }
            std::cout << std::endl;
        }
    }
    delete[] pbDiscovered;
}

void Graph::printDFSRecursive(const int id, bool* const pbDiscovered) const
{
    assert(id >= 0 && id < GetNodeCount());

    if (pbDiscovered[id])
    {
        return;
    }

    pbDiscovered[id] = true;
    std::cout << id << ' ';

    for (const Edge& edge : mAdjacentList[id]->Edges)
    {
        if (!pbDiscovered[edge.to])
        {
            printDFSRecursive(edge.to, pbDiscovered);
        }
    }
}

void Graph::searchDepthFirstPostOrderRecursive(const int id, bool* const pbDiscovered, std::stack<int>& outStack) const
{
    assert(id >= 0 && id < mAdjacentList.size());

    if (pbDiscovered[id])
    {
        return;
    }

    pbDiscovered[id] = true;

    for (const Edge& e : mAdjacentList[id]->Edges)
    {
        searchDepthFirstPostOrderRecursive(e.to, pbDiscovered, outStack);
    }

    outStack.push(id);
}
