#pragma once

#include <cassert>

namespace search_array
{
	int search_sequential(const int* const p_nums, const int len, const int key);
	int search_sequential_unfilled_array(int* const p_nums, const int len, const int capacity, const int key);

	int search_binary_recursive(const int* const p_sorted_nums, const int len, const int begin, const int end, const int key);
	int search_binary(const int* const p_sorted_nums, const int len, const int key);

	typedef struct entry {
		int key;
		int index;
	} entry_t;

	int search_indexed(
		const int* const p_sorted_nums, 
		const int arr_len, 
		const entry_t* const p_sorted_entry, 
		const int index_table_len, 
		const int key
	);

	int search_interpolation_recursive(const int* const p_nums, const int len, const int begin, const int end, const int key);
}