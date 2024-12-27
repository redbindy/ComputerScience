#pragma once

#include <cassert>
#include <cstdlib>

namespace heap
{
	template<typename T>
	struct heap_t {
		T* p_data;

		size_t capacity;
		size_t size;
	};

	template<typename T>
	heap_t<T> create_heap(const size_t capacity)
	{
		assert(capacity > 0);

		heap_t<T> ret;
		ret.p_data = static_cast<T*>(malloc(sizeof(T) * (capacity + 1)));

		ret.capacity = capacity;
		ret.size = 0;

		return ret;
	}

	template<typename T>
	void delete_heap(heap_t<T>* const p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_data);

		p_this->capacity = 0;
		p_this->size = 0;
	}

	template<typename T>
	bool is_empty(const heap_t<T>* p_this)
	{
		assert(p_this != nullptr);

		return p_this->size == 0;
	}

	template<typename T>
	bool is_full(const heap_t<T>* const p_this)
	{
		assert(p_this != nullptr);

		return p_this->capacity == p_this->size;
	}

	template<typename T>
	void add(heap_t<T>* p_this, const T value)
	{
		assert(p_this != nullptr);

		int (*default_comapre)(const T, const T) = [](const T a, const T b) -> int {
			if (a == b) {
				return 0;
			}

			if (a < b) {
				return -1;
			}

			return 1;
		};

		add(p_this, value, default_comapre);
	}

	template<typename T>
	void add(heap_t<T>* p_this, const T value, int (*compare)(const T, const T))
	{
		assert(p_this != nullptr);

		if (is_full(p_this)) {
			heap_t<T> backup_heap = *p_this;

			*p_this = create_heap<T>(backup_heap.size * 2);

			while (!is_empty(&backup_heap)) {
				const T value = poll(&backup_heap, compare);

				add(p_this, value, compare);
			}

			delete_heap(&backup_heap);
		}

		++p_this->size;

		size_t index = p_this->size;

		while (index != 1) {

			const size_t parent_index = index / 2;

			
			if (compare(p_this->p_data[parent_index], value) <= 0) {
				break;
			}

			p_this->p_data[index] = p_this->p_data[parent_index];

			index = parent_index;
		}

		p_this->p_data[index] = value;
	}

	template<typename T>
	T poll(heap_t<T>* p_this)
	{
		assert(p_this != nullptr);

		int (*default_comapre)(const T, const T) = [](const T a, const T b) -> int {
			if (a == b) {
				return 0;
			}

			if (a < b) {
				return -1;
			}

			return 1;
		};

		return poll(p_this, default_comapre);
	}

	template<typename T>
	T poll(heap_t<T>* p_this, int (*compare)(const T, const T))
	{
		assert(p_this != nullptr);

		const T retValue = p_this->p_data[1];

		const T last = p_this->p_data[p_this->size];
		--p_this->size;

		size_t index = 1;
		while (true) {
			size_t child_index = index * 2;

			if (child_index > p_this->size) {
				break;
			}

			if (compare(p_this->p_data[child_index], p_this->p_data[child_index + 1]) > 0) {
				++child_index;
			}

			if (compare(last, p_this->p_data[child_index]) <= 0) {
				break;
			}

			p_this->p_data[index] = p_this->p_data[child_index];

			index = child_index;
		}

		p_this->p_data[index] = last;

		return retValue;
	}
}