#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>

namespace array_list
{
	template<typename T>
	struct array_list_t {
		T* p_data;

		size_t capacity;
		size_t count;
	};

	template<typename T>
	array_list_t<T> create(const size_t capacity)
	{
		assert(capacity > 0);

		array_list_t<T> ret;
		ret.p_data = static_cast<T*>(malloc(sizeof(T) * capacity));

		ret.capacity = capacity;
		ret.count = 0;

		return ret;
	}

	template<typename T>
	void delete_array_list(array_list_t<T>* const p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_data);
		p_this->p_data = nullptr;

		p_this->capacity;
		p_this->count = 0;
	}

	template<typename T>
	bool is_empty(const array_list_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->count == 0;
	}

	template<typename T>
	bool is_full(const array_list_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->count == p_this->capacity;
	}

	template<typename T>
	void clear(array_list_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		p_this->count = 0;
	}

	template<typename T>
	static void extend_array_list(array_list_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		array_list_t<T> backup_this = *p_this;
		*p_this = create<T>(backup_this.capacity * 2);

		memcpy(p_this->p_data, backup_this.p_data, sizeof(T) * backup_this.count);
		p_this->count = backup_this.count;

		delete_array_list(&backup_this);
	}

	template<typename T>
	void add_item(array_list_t<T>* const p_this, const int value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		if (is_full(p_this)) {
			extend_array_list(p_this);
		}

		p_this->p_data[p_this->count] = value;
		++(p_this->count);
	}

	template<typename T>
	void insert_at(array_list_t<T>* const p_this, const int index, const T value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(index <= p_this->count);

		if (is_full(p_this)) {
			extend_array_list(p_this);
		}

		const T* p_end = p_this->p_data + index;
		T* p_curr;
		for (p_curr = p_this->p_data + p_this->count; p_curr > p_end; --p_curr) {
			*p_curr = *(p_curr - 1);
		}
		*p_curr = value;

		++(p_this->count);
	}

	template<typename T>
	T get_item(const array_list_t<T>* const p_this, const int index)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(index < p_this->count);

		return p_this->p_data[index];
	}
}