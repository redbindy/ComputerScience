#include "search_array.h"

int search_array::search_sequential(const int* const p_nums, const int len, const int key)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	for (const int* p = p_nums; p < p_nums + len; ++p) {

		if (*p == key) {
			return static_cast<int>(p - p_nums);
		}
	}

	return -1;
}

int search_array::search_sequential_unfilled_array(int* const p_nums, const int len, const int capacity, const int key)
{
	assert(p_nums != nullptr);
	assert(len >= 0);
	assert(capacity >= 0);
	assert(len < capacity);

	p_nums[len] = key;

	const int* p = p_nums;
	while (*p != key) {
		++p;
	}

	if (p == p_nums + len) {
		return -1;
	}

	return static_cast<int>(p - p_nums);
}

int search_array::search_binary_recursive(const int* const p_sorted_nums, const int len, const int begin, const int end, const int key)
{
	assert(p_sorted_nums != nullptr);
	assert(len >= 0);

	if (begin > end) {
		return -1;
	}

	const int mid = (begin + end) / 2;
	const int mid_value = p_sorted_nums[mid];

	if (mid_value == key) {
		return mid;
	}

	if (key < mid_value) {
		return search_binary_recursive(p_sorted_nums, len, begin, mid - 1, key);
	}

	return search_binary_recursive(p_sorted_nums, len, mid + 1, end, key);
}

int search_array::search_binary(const int* const p_sorted_nums, const int len, const int key)
{
	assert(p_sorted_nums != nullptr);
	assert(len >= 0);

	int begin = 0;
	int end = len - 1;
	while (begin <= end) {

		const int mid = (begin + end) / 2;
		const int mid_value = p_sorted_nums[mid];

		if (mid_value == key) {
			return mid;
		}

		if (key < mid_value) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}

	return -1;
}

int search_array::search_indexed(
	const int* const p_sorted_nums,
	const int arr_len,
	const entry_t* const p_sorted_entry,
	const int index_table_len,
	const int key
)
{
	assert(p_sorted_nums != nullptr);
	assert(p_sorted_entry != nullptr);

	if (key < p_sorted_nums[0] || key > p_sorted_nums[arr_len - 1]) {
		return -1;
	}

	int i;
	for (i = 0; i < index_table_len - 1; ++i) {

		entry_t entry = p_sorted_entry[i];

		if (key >= p_sorted_entry[i].key && key <= p_sorted_entry[i + 1].key) {
			break;
		}
	}

	const int begin = p_sorted_entry[i].index;
	const int end = i == index_table_len - 1 ? arr_len - 1 : p_sorted_entry[i + 1].index;

	for (int j = begin; j <= end; ++j) {

		if (p_sorted_nums[j] == key) {
			return j;
		}
	}

	return -1;
}

int search_array::search_interpolation_recursive(const int* const p_nums, const int len, const int begin, const int end, const int key)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	if (key < p_nums[begin] || key > p_nums[end]) {
		return -1;
	}

	const int interpolation_pos = static_cast<int>(begin + (key - p_nums[begin]) * (end - begin) / static_cast<float>((p_nums[end] - p_nums[begin])));
	const int value = p_nums[interpolation_pos];

	if (value == key) {
		return interpolation_pos;
	}

	if (key < value) {
		return search_interpolation_recursive(p_nums, len, begin, interpolation_pos - 1, key);
	}

	return search_interpolation_recursive(p_nums, len, interpolation_pos + 1, end, key);
}
