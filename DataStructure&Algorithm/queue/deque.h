#pragma once

#include <cassert>
#include <cstdlib>

namespace deque
{
	template<typename T>
	struct deque_t {
		T* p_data;

		int front;
		int back;

		size_t capacity;
		size_t count;
	};

	template<typename T>
	deque_t<T> create(const size_t capacity)
	{
		assert(capacity > 0);

		deque_t<T> ret;
		ret.p_data = static_cast<T*>(malloc(sizeof(T) * capacity));

		ret.front = static_cast<int>(capacity - 1);
		ret.back = 0;

		ret.capacity = capacity;
		ret.count = 0;

		return ret;
	}

	template<typename T>
	void delete_deque(deque_t<T>* p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_data);
		p_this->p_data = nullptr;

		p_this->front = -1;
		p_this->back = -1;

		p_this->capacity = 0;
		p_this->count = 0;
	}

	template<typename T>
	bool is_empty(const deque_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->count == 0;
	}

	template<typename T>
	bool is_full(const deque_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->count == p_this->capacity;
	}

	template<typename T>
	static void extend_deque(deque_t<T>* p_this)
	{
		deque_t<T> backup_this = *p_this;

		*p_this = create<T>(backup_this.capacity * 2);

		while (!is_empty(&backup_this)) {
			const T value = remove_front(&backup_this);
			add_back(p_this, value);
		}

		delete_deque(&backup_this);
	}

	template<typename T>
	void add_front(deque_t<T>* p_this, const T value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		if (is_full(p_this)) {
			extend_deque(p_this);
		}

		p_this->p_data[p_this->front] = value;
		p_this->front = static_cast<int>((p_this->front - 1 + p_this->capacity) % p_this->capacity);

		++(p_this->count);
	}

	template<typename T>
	void add_back(deque_t<T>* p_this, const T value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		if (is_full(p_this)) {
			extend_deque(p_this);
		}

		p_this->p_data[p_this->back] = value;
		p_this->back = (p_this->back + 1) % p_this->capacity;

		++(p_this->count);
	}

	template<typename T>
	T remove_front(deque_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		p_this->front = (p_this->front + 1) % p_this->capacity;

		--(p_this->count);

		return p_this->p_data[p_this->front];
	}

	template<typename T>
	T remove_back(deque_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		p_this->back = static_cast<int>((p_this->back - 1 + p_this->capacity) % p_this->capacity);

		--(p_this->count);

		return p_this->p_data[p_this->back];
	}

	template<typename T>
	T peek_front(const deque_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		return p_this->p_data[(p_this->front + 1) % p_this->capacity];
	}

	template<typename T>
	T peek_back(const deque_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		return p_this->p_data[(p_this->back - 1 + p_this->capacity) % p_this->capacity];
	}
}