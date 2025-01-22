#include "DynamicProgramming.h"

int GetFibonacciRecursive(const int n, const int nToPrint)
{
    assert(n >= 0);
    assert(nToPrint >= 0);

    if (n == nToPrint)
    {
        std::cout << "Called fib(" << nToPrint << ')' << std::endl;
    }

    if (n <= 1)
    {
        return n;
    }

    return GetFibonacciRecursive(n - 2, nToPrint) + GetFibonacciRecursive(n - 1, nToPrint);
}

int GetFibonacciBottomUp(const int n)
{
    assert(n >= 0);

    int result = -1;

    int* const pSequence = new int[n + 1];
    {
        pSequence[0] = 0;
        pSequence[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            pSequence[i] = pSequence[i - 2] + pSequence[i - 1];
        }

        result = pSequence[n];
    }
    delete[] pSequence;

    assert(result >= 0);

    return result;
}

int GetFibonacciTopDownRecursive(const int n, int sequence[], const int nToPrint)
{
    assert(n >= 0);

    if (sequence[n] == -1)
    {
        if (n == nToPrint)
        {
            std::cout << "Called fib(" << nToPrint << ')' << std::endl;
        }

        if (n <= 1)
        {
            sequence[n] = n;
        }
        else
        {
            sequence[n] = GetFibonacciTopDownRecursive(n - 2, sequence, nToPrint) + GetFibonacciTopDownRecursive(n - 1, sequence, nToPrint);
        }
    }

    return sequence[n];
}

int SolveMatrixPathProblemRecursive(const int* const pMat, const int n, const int row, const int col)
{
    assert(pMat != nullptr);
    assert(n >= 1);

    if (row == -1 || col == -1)
    {
        return 0;
    }

    const int leftScore = SolveMatrixPathProblemRecursive(pMat, n, row, col - 1);
    const int upScore = SolveMatrixPathProblemRecursive(pMat, n, row - 1, col);

    return pMat[row * n + col] + std::max(leftScore, upScore);
}

int SolveMatrixPathProblemBottomUp(const int* const pMat, const int n)
{
    assert(pMat != nullptr);
    assert(n >= 1);

    int result = INT32_MIN;
    int* const pScoreTable = new int[n * n];
    {
        memset(pScoreTable, 0, sizeof(int) * n * n);

        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                const int upIndex = std::max(0, row - 1) * n + col;
                const int leftIndex = row * n + std::max(0, col - 1);

                pScoreTable[row * n + col]
                    = pMat[row * n + col] + std::max(pScoreTable[upIndex], pScoreTable[leftIndex]);
            }
        }

        result = pScoreTable[n * n - 1];
    }
    delete[] pScoreTable;

    return result;
}

int SolveMatrixPathProblemTopDownRecursive(const int* pMat, const int n, const int row, const int col, int* const pCache)
{
    if (row == -1 || col == -1)
    {
        return 0;
    }

    const int index = row * n + col;

    if (pCache[index] == -1)
    {
        pCache[index] = pMat[index]
            + std::max(SolveMatrixPathProblemTopDownRecursive(pMat, n, row - 1, col, pCache),
                       SolveMatrixPathProblemTopDownRecursive(pMat, n, row, col - 1, pCache));
    }

    return pCache[index];
}

static int getPatternScore(const int* const pMat, const int n, const int col, const EPattern pattern)
{
    assert(pMat != nullptr);
    assert(n >= 1);
    assert(col >= 0);

    const int row0 = col;
    const int row1 = n + col;
    const int row2 = 2 * n + col;

    int patternScore = INT32_MIN;
    switch (pattern)
    {
    case EPattern::P0:
        patternScore = pMat[row0];
        break;

    case EPattern::P1:
        patternScore = pMat[row1];
        break;

    case EPattern::P2:
        patternScore = pMat[row2];
        break;

    case EPattern::P0_2:
        patternScore = pMat[row0] + pMat[row2];
        break;

    default:
        assert(false);
        break;
    }

    return patternScore;
}

static void getLegalPatterns(const EPattern pattern, EPattern outPatterns[static_cast<int>(EPattern::PATTERN_COUNT)], int& outLegalCount)
{
    outLegalCount = 0;
    switch (pattern)
    {
    case EPattern::P0:
        {
            outPatterns[outLegalCount++] = EPattern::P1;
            outPatterns[outLegalCount++] = EPattern::P2;
        }
        break;

    case EPattern::P1:
        {
            outPatterns[outLegalCount++] = EPattern::P0;
            outPatterns[outLegalCount++] = EPattern::P2;
            outPatterns[outLegalCount++] = EPattern::P0_2;
        }
        break;

    case EPattern::P2:
        {
            outPatterns[outLegalCount++] = EPattern::P0;
            outPatterns[outLegalCount++] = EPattern::P1;
        }
        break;

    case EPattern::P0_2:
        {
            outPatterns[outLegalCount++] = EPattern::P1;
        }
        break;

    default:
        assert(false);
        break;
    }
}

int SolvePebblePlacementProblemRecursive(const int* const pMat, const int n, const int col, const EPattern pattern)
{
    assert(pMat != nullptr);
    assert(n >= 1);
    assert(col >= 0);

    int patternScore = getPatternScore(pMat, n, col, pattern);

    if (col == 0)
    {
        return patternScore;
    }

    EPattern legalPatterns[static_cast<int>(EPattern::PATTERN_COUNT)];
    int legalCount = 0;

    getLegalPatterns(pattern, legalPatterns, legalCount);

    int max = INT32_MIN;
    for (int i = 0; i < legalCount; ++i)
    {
        const int tmp = SolvePebblePlacementProblemRecursive(pMat, n, col - 1, legalPatterns[i]);
        if (tmp > max)
        {
            max = tmp;
        }
    }

    return max + patternScore;
}

int SolvePebblePlacementProblemBottomUp(const int* const pMat, const int n)
{
    assert(pMat != nullptr);
    assert(n >= 1);

    int result = INT32_MIN;
    int* const pPebbles = new int[static_cast<int>(EPattern::PATTERN_COUNT) * n];
    {
        for (int i = 0; i < static_cast<int>(EPattern::PATTERN_COUNT); ++i)
        {
            pPebbles[i * n] = getPatternScore(pMat, n, 0, static_cast<EPattern>(i));
        }

        for (int col = 1; col < n; ++col)
        {
            for (int i = 0; i < static_cast<int>(EPattern::PATTERN_COUNT); ++i)
            {
                EPattern legalPatterns[static_cast<int>(EPattern::PATTERN_COUNT)];
                int legalCount = 0;

                EPattern pattern = static_cast<EPattern>(i);
                getLegalPatterns(pattern, legalPatterns, legalCount);

                const int patternScore = getPatternScore(pMat, n, col, pattern);

                int max = INT32_MIN;
                for (int i = 0; i < legalCount; ++i)
                {
                    const int tmp = pPebbles[static_cast<int>(legalPatterns[i]) * n + col - 1];

                    max = std::max(tmp, max);
                }

                pPebbles[i * n + col] = max + patternScore;
            }
        }

        for (int i = 0; i < static_cast<int>(EPattern::PATTERN_COUNT); ++i)
        {
            result = std::max(result, pPebbles[i * n + n - 1]);
        }
    }
    delete[] pPebbles;

    return result;
}

int SolvePebblePlacementProblemTopDownRecursive(const int* const pMat, const int n, const int col, const EPattern pattern, int* const pCache)
{
    assert(pMat != nullptr);
    assert(n >= 1);
    assert(col >= 0);
    assert(pCache != nullptr);

    int patternScore = getPatternScore(pMat, n, col, pattern);

    if (col == 0)
    {
        return patternScore;
    }

    EPattern legalPatterns[static_cast<int>(EPattern::PATTERN_COUNT)];
    int legalCount = 0;

    getLegalPatterns(pattern, legalPatterns, legalCount);

    int max = INT32_MIN;
    for (int i = 0; i < legalCount; ++i)
    {
        const int cacheIndex = static_cast<int>(legalPatterns[i]) * n + col - 1;
        const int cache = pCache[cacheIndex];

        int tmp = INT32_MIN;
        if (cache == INT32_MIN)
        {
            std::cout << "called " << static_cast<int>(legalPatterns[i]) << ' ' << col << std::endl;
            tmp = SolvePebblePlacementProblemTopDownRecursive(pMat, n, col - 1, legalPatterns[i], pCache);

            pCache[cacheIndex] = tmp;
        }
        else
        {
            tmp = cache;
        }

        if (tmp > max)
        {
            max = tmp;
        }
    }

    return max + patternScore;
}

int SolveMatrixChainProblemRecursive(const RowColSize* const pMatrixChain, const int begin, const int end)
{
    assert(pMatrixChain != nullptr);
    assert(begin >= 0);
    assert(end >= 0);

    if (begin == end)
    {
        return 0;
    }

    int min = INT32_MAX;
    for (int i = begin; i < end; ++i)
    {
        int tmp = SolveMatrixChainProblemRecursive(pMatrixChain, begin, i)
            + SolveMatrixChainProblemRecursive(pMatrixChain, i + 1, end)
            + pMatrixChain[begin].rowSize * pMatrixChain[i].colSize * pMatrixChain[end].colSize;

        min = std::min(min, tmp);
    }

    return min;
}

int SolveMatrixChainProblemBottomUp(const RowColSize* const pMatrixChain, const int n)
{
    assert(pMatrixChain != nullptr);
    assert(n > 0);

    int result = INT32_MAX;
    int* const pCache = new int[n * n];
    {
        for (int* p = pCache; p < pCache + n * n; ++p)
        {
            *p = INT16_MAX;
        }

        for (int i = 0; i < n; ++i)
        {
            pCache[i * n + i] = 0;
        }

        for (int r = 0; r < n; ++r)
        {
            for (int i = 0; i < n - r; ++i)
            {
                const int j = i + r;

                for (int k = i; k < j; ++k)
                {
                    pCache[i * n + j]
                        = std::min(pCache[i * n + j],
                                   pCache[i * n + k] + pCache[(k + 1) * n + j]
                                   + pMatrixChain[i].rowSize * pMatrixChain[k].colSize * pMatrixChain[j].colSize);
                }
            }
        }

        result = pCache[n - 1];
    }
    delete[] pCache;

    return result;
}

int SolveLCSRecursive(const char* const pStr0, const char* const pStr1, const int indx0, const int index1)
{
    assert(pStr0 != nullptr);
    assert(pStr1 != nullptr);
    assert(indx0 >= 0);
    assert(index1 >= 0);

    if (indx0 == 0 || index1 == 0)
    {
        return 0;
    }

    if (pStr0[indx0] == pStr1[index1])
    {
        return SolveLCSRecursive(pStr0, pStr1, indx0 - 1, index1 - 1) + 1;
    }

    return std::max(SolveLCSRecursive(pStr0, pStr1, indx0 - 1, index1), 
                    SolveLCSRecursive(pStr0, pStr1, indx0, index1 - 1));
}

int SolveLCSBottomUp(const char* const pStr0, const char* const pStr1)
{
    assert(pStr0 != nullptr);
    assert(pStr1 != nullptr);

    const int len0 = static_cast<int>(strlen(pStr0));
    const int len1 = static_cast<int>(strlen(pStr1));

    int result = 0;
    int* const pCache = new int[len0 * len1];
    {
        for (int i = 0; i < len0; ++i)
        {
            pCache[i * len1] = 0;
        }

        for (int i = 0; i < len1; ++i)
        {
            pCache[i] = 0;
        }

        for (int row = 1; row < len0; ++row)
        {
            for (int col = 1; col < len1; ++col)
            {
                const int cacheIndex = row * len1 + col;
                if (pStr0[row] == pStr1[col])
                {
                    pCache[cacheIndex] = pCache[(row - 1) * len1 + col - 1] + 1;
                }
                else
                {
                    pCache[cacheIndex] = std::max(pCache[(row - 1) * len1 + col],
                                                  pCache[row * len1 + col - 1]);
                }
            }
        }

        result = pCache[len0 * len1 - 1];
    }
    delete[] pCache;

    return result;
}
