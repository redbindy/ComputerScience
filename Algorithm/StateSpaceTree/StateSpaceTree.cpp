#include "StateSpaceTree.h"

namespace StateSpaceTree
{
    static int getTSPRecursive(
        const std::vector<std::vector<int>>& adjacentMatrix,
        const int start,
        const int node,
        const int count,
        bool* const pbVisited,
        const int sum
    )
    {
        assert(node >= 0);
        assert(count > 0);
        assert(pbVisited != nullptr);

        if (count == adjacentMatrix.size())
        {
            return sum + adjacentMatrix[node][start];
        }

        int result = INT32_MAX;

        pbVisited[node] = true;
        {
            for (int i = 0; i < adjacentMatrix.size(); ++i)
            {
                if (pbVisited[i])
                {
                    continue;
                }

                const int tmp = getTSPRecursive(adjacentMatrix, start, i, count + 1, pbVisited, sum + adjacentMatrix[node][i]);
                if (tmp < result)
                {
                    result = tmp;
                }
            }
        }
        pbVisited[node] = false;

        return result;
    }

    int GetTSP(const std::vector<std::vector<int>>& adjacentMatrix)
    {
        int result = INT32_MAX;

        bool* const pbVisited = new bool[adjacentMatrix.size()];
        memset(pbVisited, false, sizeof(bool) * adjacentMatrix.size());
        {
            result = getTSPRecursive(adjacentMatrix, 0, 0, 1, pbVisited, 0);
        }
        delete[] pbVisited;

        return result;
    }

    static int getTSPBoundedBranchRecursive(
        const std::vector<std::vector<int>>& adjacentMatrix,
        const std::vector<int>& minValues,
        const int start,
        const Node node,
        const int count,
        bool* const pbVisited,
        const int sum
    )
    {
        assert(node.id >= 0);
        assert(count > 0);
        assert(pbVisited != nullptr);

        if (count == adjacentMatrix.size())
        {
            return sum + adjacentMatrix[node.id][start];
        }

        int result = INT32_MAX;

        pbVisited[node.id] = true;
        {
            std::priority_queue<Node, std::vector<Node>, compare> pq;

            for (int i = 0; i < adjacentMatrix.size(); ++i)
            {
                if (pbVisited[i])
                {
                    continue;
                }

                Node nextNode = { i, node.weight };
                nextNode.weight -= minValues[node.id];
                nextNode.weight += adjacentMatrix[node.id][i];

                pq.push(nextNode);
            }

            while (!pq.empty())
            {
                Node n = pq.top();
                pq.pop();

                if (n.weight > result)
                {
                    continue;
                }

                const int tmp = getTSPBoundedBranchRecursive(
                    adjacentMatrix,
                    minValues, 
                    start,
                    n,
                    count + 1,
                    pbVisited,
                    sum + adjacentMatrix[node.id][n.id]
                );

                if (tmp < result)
                {
                    result = tmp;
                }
            }
        }
        pbVisited[node.id] = false;

        return result;
    }

    int GetTSPBoundedBranch(const std::vector<std::vector<int>>& adjacentMatrix)
    {
        Node first = { 0, 0 };
        std::vector<int> minValues;
        minValues.reserve(adjacentMatrix.size());

        for (int row = 0; row < adjacentMatrix.size(); ++row)
        {
            int min = INT32_MAX;
            for (int col = 0; col < row; ++col)
            {
                min = std::min(min, adjacentMatrix[row][col]);
            }

            for (int col = row + 1; col < adjacentMatrix.size(); ++col)
            {
                min = std::min(min, adjacentMatrix[row][col]);
            }

            first.weight += min;
            minValues.push_back(min);
        }

        int result = INT32_MAX;

        bool* const pbVisited = new bool[adjacentMatrix.size()];
        memset(pbVisited, false, sizeof(bool) * adjacentMatrix.size());
        {
            result = getTSPBoundedBranchRecursive(adjacentMatrix, minValues, 0, first, 1, pbVisited, 0);
        }
        delete[] pbVisited;

        return result;
    }

    bool CanExitMazeRecursive(
        const std::vector<std::vector<bool>>& adjacentMatrix,
        const int start,
        const int target,
        bool* const pbVisited,
        std::vector<int>& prev
    )
    {
        assert(start >= 0 && start < adjacentMatrix.size());
        assert(target >= 0 && target < adjacentMatrix.size());
        assert(pbVisited != nullptr);
        assert(prev.size() == adjacentMatrix.size());

        if (start == target)
        {
            return true;
        }

        pbVisited[start] = true;

        bool result = false;
        for (int i = 0; i < adjacentMatrix.size(); ++i)
        {
            if (!adjacentMatrix[start][i] || pbVisited[i])
            {
                continue;
            }

            prev[i] = start;

            result = CanExitMazeRecursive(adjacentMatrix, i, target, pbVisited, prev);
        }

        return result;
    }

    bool CanExitMaze(const std::vector<std::vector<bool>>& adjacentMatrix, const int start, const int target)
    {
        assert(start >= 0 && start < adjacentMatrix.size());
        assert(target >= 0 && target < adjacentMatrix.size());

        std::vector<int> prev(adjacentMatrix.size(), -1);
        bool bExit = false;

        bool* const pbVisited = new bool[adjacentMatrix.size()];
        memset(pbVisited, false, sizeof(bool) * adjacentMatrix.size());
        {
            bExit = CanExitMazeRecursive(adjacentMatrix, start, target, pbVisited, prev);
        }
        delete[] pbVisited;

        if (bExit)
        {
            std::cout << "end <- ";

            int node = prev[target];
            while (prev[node] != -1)
            {
                std::cout << node << " <- ";

                node = prev[node];
            }
            std::cout << "start" << std::endl;
        }

        return bExit;
    }

    bool SolveColoringProblemRecursive(
        const std::vector<std::vector<bool>>& adjacentMatrix,
        const int colorCount,
        const int node,
        const int color,
        std::vector<int>& colors
    )
    {
        assert(color >= 0);
        assert(adjacentMatrix.size() == colors.size());

        for (int i = 0; i < node; ++i)
        {
            if (adjacentMatrix[node][i] && colors[i] == color)
            {
                return false;
            }
        }

        if (node == colors.size() - 1)
        {
            return true;
        }

        colors[node] = color;

        bool bResult = false;
        int nextColor = 0;
        while (!bResult && nextColor <= colorCount)
        {
            bResult = SolveColoringProblemRecursive(adjacentMatrix, colorCount, node + 1, nextColor, colors);
            ++nextColor;
        }

        return bResult;
    }

    bool SolveColoringProblem(const std::vector<std::vector<bool>>& adjacentMatrix, const int colorCount)
    {
        assert(colorCount > 0);

        std::vector<int> colors(adjacentMatrix.size(), -1);
        const int bCanSolve = SolveColoringProblemRecursive(adjacentMatrix, colorCount, 0, 0, colors);

        return bCanSolve;
    }

    void PrintAStarShortestPath(const std::vector<std::vector<int>>& adjacentMatrix, const std::vector<int>& estimatedValues, const int start, const int terminal)
    {
        assert(adjacentMatrix.size() == estimatedValues.size());
        assert(start >= 0 && start < estimatedValues.size());
        assert(terminal >= 0 && terminal < estimatedValues.size());

        const int nodeCount = static_cast<int>(estimatedValues.size());

        int* const pRealDists = new int[nodeCount];
        int* const pEstimatedDists = new int[nodeCount];
        {
            for (int i = 0; i < nodeCount; ++i)
            {
                pRealDists[i] = UINT8_MAX;
                pEstimatedDists[i] = UINT8_MAX;
            }
            
            pRealDists[start] = 0;
            pEstimatedDists[start] = estimatedValues[start];

            std::priority_queue<Node, std::vector<Node>, compare> pq;
            pq.push({ start, pEstimatedDists[0] });

            while (!pq.empty())
            {
                Node n = pq.top();
                pq.pop();

                if (n.id == terminal)
                {
                    break;
                }

                if (n.weight > pEstimatedDists[n.id])
                {
                    continue;
                }

                for (int i = 0; i < nodeCount; ++i)
                {
                    const int newDist = pRealDists[n.id] + adjacentMatrix[n.id][i];
                    const int newEstimatedDist = newDist + estimatedValues[i];

                    if (newEstimatedDist < pEstimatedDists[i])
                    {
                        pEstimatedDists[i] = newEstimatedDist;
                        pRealDists[i] = newDist;

                        pq.push({ i, newEstimatedDist });
                    }
                }
            }

            for (int i = 0; i < nodeCount; ++i)
            {
                std::cout << pRealDists[i] << " ";
            }
            std::cout << std::endl;
        }
        delete[] pRealDists;
        delete[] pEstimatedDists;
    }
}
