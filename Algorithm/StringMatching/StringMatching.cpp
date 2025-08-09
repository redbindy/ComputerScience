#include "StringMatching.h"

int GetCStringLength(const char* pStr)
{
    assert(pStr != nullptr);

    const char* p = pStr;
    while (*p != '\0')
    {
        ++p;
    }

    return static_cast<int>(p - pStr);
}

bool FindSubStringNaively(const char* pStr, const char* pSub)
{
    assert(pStr != nullptr);
    assert(pSub != nullptr);

    const int strLength = GetCStringLength(pStr);
    const int subLength = GetCStringLength(pSub);

    if (strLength < subLength)
    {
        return false;
    }

    const char* const pStrEnd = pStr + strLength;
    for (const char* p = pStr; *p != '\0'; ++p)
    {
        if (p + subLength > pStrEnd)
        {
            break;
        }

        const char* pCurr = p;
        const char* pSubCurr = pSub;
        while (*pCurr != '\0' && *pCurr == *pSubCurr)
        {
            ++pCurr;
            ++pSubCurr;
        }

        if (*pSubCurr == '\0')
        {
            return true;
            // Ȥ�� i ��ġ ��ȯ
        }
    }

    return false;
}

bool FindSubStringAutomata(const char* pStr, const char* pSub)
{
    assert(pStr != nullptr);
    assert(pSub != nullptr);

    const int strLength = GetCStringLength(pStr);
    const int subLength = GetCStringLength(pSub);

    if (strLength < subLength)
    {
        return false;
    }

    constexpr int INPUT_COUNT = std::numeric_limits<char>::max();

    const int bufferSize = (subLength + 1) * INPUT_COUNT;

    int* const pBuffer = new int[bufferSize];
    memset(pBuffer, 0, sizeof(int) * bufferSize);

    bool bResult = false;
    {
        int (*automataTable)[INPUT_COUNT] = reinterpret_cast<int(*)[INPUT_COUNT]>(pBuffer);

        // ���丶Ÿ ���̺� ����
        for (int state = 0; state <= subLength; ++state)
        {
            for (int ch = 0; ch < INPUT_COUNT; ++ch)
            {
                int nextState;
                if (state < subLength&& ch == pSub[state]) // ���°� ���� �ƴϰ� ������ ��ġ�ϸ�
                {
                    nextState = state + 1; // ���� ���·� ����
                }
                else
                {
                    // ���� ���¸� ���캸�鼭 
                    for (nextState = state; nextState > 0; --nextState)
                    {
                        // ���� ���� ���ڿ� ��ġ�ϸ�
                        if (pSub[nextState - 1] == ch)
                        {
                            int i;
                            for (i = 0; i < nextState - 1; ++i) // ó������ ���丶Ÿ�� Ȯ���ϸ鼭 ��
                            {
                                // ���� ������ ���� ���鼭 ���� ���� Ȯ��
                                if (pSub[i] != pSub[i + (state - nextState + 1)])
                                {
                                    break;
                                }
                            }

                            if (i == nextState - 1) // ������ ��ġ�ϸ� nextState�� ���� ���·� ����
                            {
                                break;
                            }
                        }
                    }
                }

                automataTable[state][ch] = nextState;
            }
        }

        int state = 0;
        for (int i = 0; i < strLength; ++i)
        {
            state = automataTable[state][pStr[i]];

            // ������ ���¿� �����ϸ� ����
            if (state == subLength)
            {
                bResult = true;
                // Ȥ�� i + m - 1 ��ġ ��ȯ

                goto RET;
            }
        }
    }
RET:
    delete[] pBuffer;

    return bResult;
}

bool FindSubStringRabinKarp(const char* pStr, const char* pSub)
{
    assert(pStr != nullptr);
    assert(pSub != nullptr);

    const int strLength = GetCStringLength(pStr);
    const int subLength = GetCStringLength(pSub);

    if (strLength < subLength)
    {
        return false;
    }

    constexpr int RADIX = 10;
    constexpr int WEIGHT = 16777619;

    uint64_t strHash = 0;
    uint64_t subHash = 0;
    for (int i = 0; i < subLength; ++i)
    {
        strHash = (strHash * RADIX + pStr[i]) % WEIGHT;
        subHash = (subHash * RADIX + pSub[i]) % WEIGHT;
    }

    if (strHash == subHash)
    {
        return true;
    }

    const uint64_t MSD_WEIGHT = static_cast<uint64_t>(pow(RADIX, subLength - 1)) % WEIGHT;

    for (int i = 1; i < strLength - subLength + 1; ++i)
    {
        strHash = (RADIX * ((strHash - MSD_WEIGHT * pStr[i - 1]) % WEIGHT) + pStr[i + subLength - 1]) % WEIGHT;

        if (strHash == subHash)
        {
            // �浹 ����ؼ� [i, i + subLength) �˻� �߰� ����

            return true;
            // Ȥ�� i ��ȯ
        }
    }

    return false;
}

bool FindSubStringKMP(const char* pStr, const char* pSub)
{
    assert(pStr != nullptr);
    assert(pSub != nullptr);

    const int strLength = GetCStringLength(pStr);
    const int subLength = GetCStringLength(pSub);

    if (strLength < subLength)
    {
        return false;
    }

    int* const lapTable = new int[subLength];
    memset(lapTable, 0, sizeof(int) * subLength);

    bool bResult = false;
    {
        int j = 0;
        for (int i = 1; i < subLength; ++i)
        {
            while (j > 0 && pSub[i] != pSub[j])
            {
                j = lapTable[j - 1];
            }

            if (pSub[i] == pSub[j])
            {
                ++j;
                lapTable[i] = j;
            }
        }

        j = 0;
        for (int i = 0; i < strLength; ++i)
        {
            while (j > 0 && pStr[i] != pSub[j])
            {
                j = lapTable[j - 1];
            }

            if (pStr[i] == pSub[j])
            {
                if (j == subLength - 1)
                {
                    bResult = true;

                    goto RET;

                    // Ȥ�� i - (m - 1) ��ȯ
                }

                ++j;
            }
        }
    }
RET:
    delete[] lapTable;

    return bResult;
}

bool FindSubStringBoyerMoore(const char* pStr, const char* pSub)
{
    assert(pStr != nullptr);
    assert(pSub != nullptr);

    const int strLength = GetCStringLength(pStr);
    const int subLength = GetCStringLength(pSub);

    if (strLength < subLength)
    {
        return false;
    }

    constexpr int INPUT_COUNT = INT8_MAX;

    int* const pJumpTable = new int[INPUT_COUNT];
    memset(pJumpTable, 0, sizeof(int) * INPUT_COUNT);

    bool bResult = false;
    {
        for (int* p = pJumpTable; p < pJumpTable + INPUT_COUNT; ++p)
        {
            *p = subLength;
        }

        for (int i = 0; i < subLength - 1; ++i)
        {
            pJumpTable[pSub[i]] = subLength - 1 - i;
        }

        for (int i = 0; i < strLength - subLength + 1;)
        {
            int j = subLength - 1;
            int k = i + subLength - 1;
            while (j > 0 && pSub[j] == pStr[k])
            {
                --j;
                --k;
            }

            if (j == 0)
            {
                bResult = true;

                goto RET;

                // Ȥ�� i ��ȯ
            }

            i += pJumpTable[pStr[i + subLength - 1]];
        }
    }
RET:;
    delete[] pJumpTable;

    return bResult;
}
