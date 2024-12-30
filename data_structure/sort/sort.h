#pragma once

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include "../priority_queue/heap.h"
#include "../queue/ring_queue.h"

namespace sort
{
	using namespace heap;
	using namespace ring_queue;

	inline void swap(int* const p_l, int* const p_r)
	{
		assert(p_l != nullptr);
		assert(p_r != nullptr);

		int tmp = *p_l;
		*p_l = *p_r;
		*p_r = tmp;
	}

	void print_selection_sort(int* const p_nums, const int len);

	void print_insertion_sort(int* const p_nums, const int len);

	void print_bubble_sort(int* const p_nums, const int len);

	void print_shell_sort(int* const p_nums, const int len);

	void print_merge_sort(int* const p_nums, const int len);

	void print_quick_sort_lomuto(int* const p_nums, const int len);
	void print_quick_sort_hoare(int* const p_nums, const int len);

	void print_heap_sort(int* const p_nums, const int len);

	void print_radix_sort(int* const p_nums, const int len);
}