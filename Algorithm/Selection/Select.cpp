#include "Select.h"

static void swap(std::vector<int>& v, const int l, const int r)
{
    assert(l >= 0);
    assert(l < v.size());
    assert(r >= 0);
    assert(r < v.size());

    int tmp = v[l];
    v[l] = v[r];
    v[r] = tmp;
}

static int partition(std::vector<int>& v, const int begin, const int end, const int pivot)
{
    assert(begin >= 0);
    assert(begin < v.size());
    assert(end >= 0);
    assert(end < v.size());

    int pivotOffset;
    for (pivotOffset = begin; pivotOffset < end; ++pivotOffset)
    {
        if (v[pivotOffset] == pivot)
        {
            break;
        }
    }

    swap(v, pivotOffset, end);

    int pivotIndex = begin;
    for (int i = begin; i < end; ++i)
    {
        if (v[i] < pivot)
        {
            swap(v, i, pivotIndex);

            ++pivotIndex;
        }
    }

    swap(v, pivotIndex, end);

    return pivotIndex;
}

static int selectKthRecursive(std::vector<int>& v, const int begin, const int end, const int k)
{
    assert(k > 0);

    if (begin > end)
    {
        return -1;
    }

    const int pivotIndex = partition(v, begin, end, v[end]);

    const int pivotOrder = pivotIndex - begin + 1;

    if (pivotOrder == k)
    {
        return v[pivotIndex];
    }

    if (k < pivotOrder)
    {
        return selectKthRecursive(v, begin, pivotIndex - 1, k);
    }

    return selectKthRecursive(v, pivotIndex + 1, end, k - pivotOrder);
}

int Selection::SelectKthNum(std::vector<int>& v, const int k)
{
    assert(k > 0);

    std::vector<int> copiedV = v;

    return selectKthRecursive(copiedV, 0, static_cast<int>(v.size() - 1), k);
}

static int getMedianOfMedian(std::vector<int>& v, const int begin, const int end)
{
    assert(begin >= 0);
    assert(begin < v.size());
    assert(end >= 0);
    assert(end < v.size());

    constexpr int UNIT_SIZE = 5;

    const int groupCount = static_cast<int>(round(v.size() / UNIT_SIZE));

    std::vector<int> medians;
    medians.reserve(groupCount);

    for (int i = 0; i < groupCount; ++i)
    {
        const int groupBegin = begin + i * UNIT_SIZE;
        const int groupNext = static_cast<int>(std::min(begin + (i + 1) * UNIT_SIZE, end + 1));

        const int mid = (groupNext - groupBegin + 1) / 2;

        const int median = selectKthRecursive(v, groupBegin, groupNext - 1, mid);

        medians.push_back(median);
    }

    const int medianOfMedian = selectKthRecursive(medians, 0, groupCount - 1, groupCount / 2);

    return medianOfMedian;
}

static int selectLinearRecursive(std::vector<int>& v, const int begin, const int end, const int k)
{
    assert(k > 0);

    if (begin > end)
    {
        return -1;
    }

    if (end - begin + 1 <= 5)
    {
        return selectKthRecursive(v, begin, end, k);
    }

    const int medianOfMedian = getMedianOfMedian(v, begin, end);
    const int pivotIndex = partition(v, begin, end, medianOfMedian);

    const int pivotOrder = pivotIndex - begin + 1;

    if (pivotOrder == k)
    {
        return v[pivotIndex];
    }

    if (k < pivotOrder)
    {
        return selectLinearRecursive(v, begin, pivotIndex - 1, k);
    }

    return selectLinearRecursive(v, pivotIndex + 1, end, k - pivotOrder);
}

int Selection::SelectLinear(std::vector<int>& v, const int k)
{
    assert(k > 0);

    std::vector<int> copiedV = v;

    return selectLinearRecursive(v, 0, static_cast<int>(v.size() - 1), k);
}
