#include "sort.h"

static void print_step(const int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	for (const int* p = p_nums; p < p_nums + len; ++p) {
		printf("%d ", *p);
	}
	printf("\n");
}

void sort::print_selection_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	for (int i = 0; i < len - 1; ++i) {

		int min_index = i;
		for (int j = i + 1; j < len; ++j) {

			if (p_nums[j] < p_nums[min_index]) {
				min_index = j;
			}
		}

		swap(p_nums + i, p_nums + min_index);

		print_step(p_nums, len);
	}
}

void sort::print_insertion_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	for (int i = 1; i < len; ++i) {

		const int inserting_value = p_nums[i];

		int index = i;
		while (index > 0 && p_nums[index - 1] > inserting_value) {
			p_nums[index] = p_nums[index - 1];

			--index;
		}

		p_nums[index] = inserting_value;

		print_step(p_nums, len);
	}
}

void sort::print_bubble_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	for (int i = 0; i < len - 1; ++i) {

		for (int j = 0; j < len - 1 - i; ++j) {

			if (p_nums[j] > p_nums[j + 1]) {
				swap(p_nums + j, p_nums + j + 1);
			}
		}

		print_step(p_nums, len);
	}
}

void sort::print_shell_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	// int gap = 5;
	int gap = len / 2;

	while (gap != 0) {

		if (gap % 2 == 0) {
			++gap;
		}

		for (int i = 0; i < gap; ++i) {

			for (int r = i + gap; r < len; r += gap) {

				const int inserting_value = p_nums[r];

				int index = r;
				while (r > 0 && p_nums[index - gap] > inserting_value) {
					p_nums[index] = p_nums[index - gap];
					
					index -= gap;
				}

				p_nums[index] = inserting_value;
			}
		}

		gap /= 2;

		print_step(p_nums, len);
	}
}

static void print_merge_sort_recursive(int* const p_nums, int* const p_tmp, const int len, const int left, const int right)
{
	assert(p_nums != nullptr);
	assert(p_tmp != nullptr);
	assert(len >= 0);
	assert(left >= 0);
	assert(right >= 0);
	assert(right < len);

	if (left >= right) {
		return;
	}

	const int mid = (left + right) / 2;

	print_merge_sort_recursive(p_nums, p_tmp, len, left, mid);
	print_merge_sort_recursive(p_nums, p_tmp, len, mid + 1, right);

	int l = left;
	int r = mid + 1;
	int i = left;

	while (l <= mid && r <= right) {

		if (p_nums[l] <= p_nums[r]) {
			p_tmp[i] = p_nums[l];
			++l;
		}
		else {
			p_tmp[i] = p_nums[r];
			++r;
		}

		++i;
	}

	while (l <= mid) {
		p_tmp[i] = p_nums[l];
		++l;
		++i;
	}

	while (r <= right) {
		p_tmp[i] = p_nums[r];
		++r;
		++i;
	}

	memcpy(p_nums + left, p_tmp + left, sizeof(int) * (right - left + 1));

	print_step(p_nums, len);
}

void sort::print_merge_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	int* const p_tmp = static_cast<int* const>(malloc(sizeof(int) * len));
	{
		print_merge_sort_recursive(p_nums, p_tmp, len, 0, len - 1);
	}
	free(p_tmp);
}

static int partition_lomuto(int* const p_nums, const int left, const int right)
{
	assert(p_nums != nullptr);
	assert(left >= 0);
	assert(right >= 0);
	assert(left < right);

	const int pivot = p_nums[right];

	int pivot_pos = left;
	for (int i = left; i < right; ++i) {

		if (p_nums[i] < pivot) {
			sort::swap(p_nums + pivot_pos, p_nums + i);

			++pivot_pos;
		}
	}

	sort::swap(p_nums + pivot_pos, p_nums + right);

	return pivot_pos;
}

static int partition_hoare(int* const p_nums, const int left, const int right)
{
	assert(p_nums != nullptr);
	assert(left >= 0);
	assert(right >= 0);
	assert(left < right);

	const int pivot = p_nums[(left + right) / 2];

	int l = left - 1;
	int r = right + 1;
	while (true) {

		do {
			++l;
		} while (p_nums[l] < pivot);

		do {
			--r;
		} while (p_nums[r] > pivot);

		if (l >= r) {
			break;
		}

		sort::swap(p_nums + l, p_nums + r);
	}

	return r;
}

static void print_quick_sort_recursive(int* const p_nums, const int len, const int left, const int right, const bool is_hoare)
{
	assert(p_nums != nullptr);
	assert(len >= 0);
	assert(left >= 0);
	assert(right < len);

	if (left >= right) {
		return;
	}

	int pivot_index;

	if (is_hoare) {

		pivot_index = partition_hoare(p_nums, left, right);

		print_step(p_nums, len);

		print_quick_sort_recursive(p_nums, len, left, pivot_index, is_hoare);
		print_quick_sort_recursive(p_nums, len, pivot_index + 1, right, is_hoare);
	}
	else {

		pivot_index = partition_lomuto(p_nums, left, right);

		print_step(p_nums, len);

		print_quick_sort_recursive(p_nums, len, left, pivot_index - 1, is_hoare);
		print_quick_sort_recursive(p_nums, len, pivot_index + 1, right, is_hoare);
	}
}

void sort::print_quick_sort_lomuto(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	print_quick_sort_recursive(p_nums, len, 0, len - 1, false);
}

void sort::print_quick_sort_hoare(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	print_step(p_nums, len);

	print_quick_sort_recursive(p_nums, len, 0, len - 1, true);
}

void sort::print_heap_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	heap_t<int> heap = create_heap<int>(len);
	{
		for (const int* p = p_nums; p < p_nums + len; ++p) {

			add(&heap, *p);
		}

		int* p = p_nums;
		while (!is_empty(&heap)) {
			*p++ = poll(&heap);

			print_step(p_nums, static_cast<int>(p - p_nums));
		}
	}
	delete_heap(&heap);
}

void sort::print_radix_sort(int* const p_nums, const int len)
{
	assert(p_nums != nullptr);
	assert(len >= 0);

	constexpr int RADIX = 10;

	ring_queue_t<int> queue[RADIX];
	for (int i = RADIX - 1; i >= 0; --i) {
		
		queue[i] = create<int>(len);
	}
	{
		print_step(p_nums, len);

		int max_value = *p_nums;
		for (const int* p = p_nums + 1; p < p_nums + len; ++p) {

			if (*p > max_value) {
				max_value = *p;
			}
		}

		int weight = 1;
		for (int digits = static_cast<int>(log10(max_value)) + 1; digits > 0; --digits) {

			for (const int* p = p_nums; p < p_nums + len; ++p) {

				const int digit = *p % (weight * RADIX) / weight;

				enqueue(queue + digit, *p);
			}

			weight *= RADIX;

			int* p = p_nums;
			for (int i = 0; i < RADIX; ++i) {
				
				while (!is_empty(queue + i)) {

					*p++ = dequeue(queue + i);
				}
			}

			print_step(p_nums, len);
		}
	}
	for (int i = RADIX - 1; i >= 0; --i) {

		delete_ring_queue(queue + i);
	}
}
