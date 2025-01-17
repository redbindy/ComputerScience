#pragma once

#include <cassert>
#include <vector>
#include <functional>
#include <queue>
#include <cstdint>
#include <cmath>

#include "../DataStructure/THeap.h"

template<typename T>
class Sort final
{
public:

    static void CreateInstance();
    static Sort<T>* GetInstance();
    static void DeleteInstance();

    void SetComparator(bool (*compareFunc)(T&, T&));

    void SortSelection(std::vector<T>& v);
    void SortBubble(std::vector<T>& v);
    void SortInsertion(std::vector<T>& v);
    void SortMerge(std::vector<T>& v);
    void SortQuick(std::vector<T>& v);
    void SortHeap(std::vector<T>& v);
    void SortRadix(std::vector<uint32_t>& v, const int radix);
    void SortCounting(std::vector<int>& v);

private:
    static Sort<T>* spInstance;

    bool (*mbCompareFunc)(T&, T&);

private:
    Sort();
    ~Sort() = default;
    Sort(const Sort& other) = delete;
    Sort(const Sort&& other) = delete;
    Sort& operator=(const Sort& other) = delete;
    Sort& operator=(const Sort&& other) = delete;

    void sortMergeRecursive(std::vector<T>& v, std::vector<T>& tmp, const int begin, const int end);
    void sortQuickRecursive(std::vector<T>& v, const int begin, const int end);

    void swap(T& outA, T& outB);
    static bool compare(T& a, T& b);
};

template<typename T>
Sort<T>* Sort<T>::spInstance = nullptr;

template<typename T>
Sort<T>::Sort()
    : mbCompareFunc(&Sort<T>::compare)
{

}

template<typename T>
inline void Sort<T>::CreateInstance()
{
    spInstance = new Sort<T>();
}

template<typename T>
inline Sort<T>* Sort<T>::GetInstance()
{
    if (spInstance == nullptr)
    {
        CreateInstance();
    }

    return spInstance;
}

template<typename T>
inline void Sort<T>::DeleteInstance()
{
    delete spInstance;
}

template<typename T>
inline void Sort<T>::SetComparator(bool (*compareFunc)(T&, T&))
{
    assert(compareFunc != nullptr);

    mbCompareFunc = compareFunc;
}

template<typename T>
inline void Sort<T>::SortSelection(std::vector<T>& v)
{
    for (int i = 0; i < v.size() - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < v.size(); ++j)
        {
            if (!mbCompareFunc(v[minIndex], v[j]))
            {
                minIndex = j;
            }
        }

        swap(v[i], v[minIndex]);
    }
}

template<typename T>
inline void Sort<T>::SortBubble(std::vector<T>& v)
{
    for (int i = 0; i < v.size() - 1; ++i)
    {
        for (int j = 0; j < v.size() - 1 - i; ++j)
        {
            if (!mbCompareFunc(v[j], v[j + 1]))
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

template<typename T>
inline void Sort<T>::SortInsertion(std::vector<T>& v)
{
    for (int i = 1; i < v.size(); ++i)
    {
        T value = v[i];

        int insertionIndex = i;
        while (insertionIndex > 0
               && !mbCompareFunc(v[insertionIndex - 1], value))
        {
            v[insertionIndex] = v[insertionIndex - 1];

            --insertionIndex;
        }

        v[insertionIndex] = value;
    }
}

template<typename T>
inline void Sort<T>::SortMerge(std::vector<T>& v)
{
    std::vector<T> tmp = v;
    sortMergeRecursive(v, tmp, 0, static_cast<int>(v.size() - 1));
}

template<typename T>
inline void Sort<T>::SortQuick(std::vector<T>& v)
{
    sortQuickRecursive(v, 0, static_cast<int>(v.size() - 1));
}

template<typename T>
inline void Sort<T>::SortHeap(std::vector<T>& v)
{
    THeap<T> heap(static_cast<int>(v.size()));

    for (T& data : v)
    {
        heap.Add(data);
    }

    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = heap.Peek();

        heap.Poll();
    }
}

template<typename T>
inline void Sort<T>::SortRadix(std::vector<uint32_t>& v, const int radix)
{
    assert(radix >= 2);

    std::queue<uint32_t>* pDigits = new std::queue<uint32_t>[radix];
    {
        uint32_t max = v[0];
        for (int i = 1; i < v.size(); ++i)
        {
            if (v[i] > max)
            {
                max = v[i];
            }
        }

        const int placeCount = static_cast<int>(log10(max) / log10(radix)) + 1;

        int weight = 1;
        for (int i = placeCount; i > 0; --i)
        {
            for (const uint32_t num : v)
            {
                const uint32_t digit = num % (weight * radix) / weight;

                pDigits[digit].push(num);
            }

            v.clear();

            for (int j = 0; j < radix; ++j)
            {
                std::queue<uint32_t>& queue = pDigits[j];
                while (!queue.empty())
                {
                    v.push_back(queue.front());
                    queue.pop();
                }
            }

            weight *= radix;
        }
    }
    delete[] pDigits;
}

template<typename T>
inline void Sort<T>::SortCounting(std::vector<int>& v)
{
    int max = v[0];
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }

    std::vector<int> counter(max + 1, 0);
    std::vector<int> input = v;

    for (const int num : input)
    {
        ++counter[num];
    }

    for (int i = 1; i < counter.size(); ++i)
    {
        counter[i] += counter[i - 1];
    }

    for (int i = static_cast<int>(input.size() - 1); i >= 0; --i)
    {
        const int num = input[i];

        v[counter[num] - 1] = num;
        --counter[num];
    }
}

template<typename T>
inline void Sort<T>::sortMergeRecursive(std::vector<T>& v, std::vector<T>& tmp, const int begin, const int end)
{
    if (begin >= end)
    {
        return;
    }

    const int mid = (begin + end) / 2;

    sortMergeRecursive(v, tmp, begin, mid);
    sortMergeRecursive(v, tmp, mid + 1, end);

    int l = begin;
    int r = mid + 1;
    int i = begin;

    while (l <= mid && r <= end)
    {
        if (v[l] <= v[r])
        {
            tmp[i] = v[l];
            ++l;
        }
        else
        {
            tmp[i] = v[r];
            ++r;
        }

        ++i;
    }

    while (l <= mid)
    {
        tmp[i++] = v[l++];
    }

    while (r <= end)
    {
        tmp[i++] = v[r++];
    }

    for (i = begin; i <= end; ++i)
    {
        v[i] = tmp[i];
    }
}

template<typename T>
inline void Sort<T>::sortQuickRecursive(std::vector<T>& v, const int begin, const int end)
{
    if (begin >= end)
    {
        return;
    }

# if false /* LOMUTO */
    T pivot = v[end];

    int pivotIndex = begin;
    for (int i = begin; i < end; ++i)
    {
        if (!mbCompareFunc(pivot, v[i]))
        {
            swap(v[i], v[pivotIndex]);
            ++pivotIndex;
        }
    }

    swap(v[pivotIndex], v[end]);

    sortQuickRecursive(v, begin, pivotIndex - 1);
    sortQuickRecursive(v, pivotIndex + 1, end);
#endif /* LOMUTO */

#if true /* HOARE */
    T pivot = v[(begin + end) / 2];

    int l = begin - 1;
    int r = end + 1;

    while (true)
    {
        do
        {
            ++l;
        } while (mbCompareFunc(v[l], pivot));

        do
        {
            --r;
        } while (mbCompareFunc(pivot, v[r]));

        if (l >= r)
        {
            break;
        }

        swap(v[l], v[r]);
    }

    sortQuickRecursive(v, begin, r);
    sortQuickRecursive(v, r + 1, end);
#endif /* HOARE */
}

template<typename T>
inline void Sort<T>::swap(T& outA, T& outB)
{
    T tmp = outA;
    outA = outB;
    outB = tmp;
}

template<typename T>
inline bool Sort<T>::compare(T& a, T& b)
{
    return a < b;
}
