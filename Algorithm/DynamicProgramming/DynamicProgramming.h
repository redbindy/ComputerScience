#pragma once

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

int GetFibonacciRecursive(const int n, const int nToPrint);
int GetFibonacciBottomUp(const int n);
int GetFibonacciTopDownRecursive(const int n, int sequence[], const int nToPrint);

int SolveMatrixPathProblemRecursive(const int* const pMat, const int n, const int row, const int col);
int SolveMatrixPathProblemBottomUp(const int* const pMat, const int n);
int SolveMatrixPathProblemTopDownRecursive(const int* pMat, const int n, const int row, const int col, int* const cache);

enum class EPattern
{
    P0, 
    P1, 
    P2, 
    P0_2, 
    PATTERN_COUNT
};

int SolvePebblePlacementProblemRecursive(const int* const pMat, const int n, const int col, const EPattern pattern);
int SolvePebblePlacementProblemBottomUp(const int* const pMat, const int n);
int SolvePebblePlacementProblemTopDownRecursive(const int* const pMat, const int n, const int col, const EPattern pattern, int* const pCache);

struct RowColSize
{
    int rowSize;
    int colSize;
};

int SolveMatrixChainProblemRecursive(const RowColSize* const pMatrixChain, const int begin, const int end);
int SolveMatrixChainProblemBottomUp(const RowColSize* const pMatrixChain, const int n);

int SolveLCSRecursive(const char* const pStr0, const char* const pStr1, const int index0, const int index1);
int SolveLCSBottomUp(const char* const pStr0, const char* const pStr1);