#pragma once

#include <cassert>
#include <vector>
#include <cstdint>
#include <iostream>
#include <queue>

namespace StateSpaceTree
{
    int GetTSP(const std::vector<std::vector<int>>& adjacentMatrix);

    struct Node
    {
        int id;
        int weight;
    };

    struct compare
    {
        bool operator()(const Node& n0, const Node& n1)
        {
            return n0.weight > n1.weight;
        }
    };

    int GetTSPBoundedBranch(const std::vector<std::vector<int>>& adjacentMatrix);

    bool CanExitMaze(const std::vector<std::vector<bool>>& adjacentMatrix, const int start, const int target);

    bool SolveColoringProblem(const std::vector<std::vector<bool>>& adjacentMatrix, const int colorCount);

    void PrintAStarShortestPath(const std::vector<std::vector<int>>& adjacentMatrix, const std::vector<int>& estimatedValues, const int start, const int terminal);
}