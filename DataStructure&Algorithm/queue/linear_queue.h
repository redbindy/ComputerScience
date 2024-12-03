#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>

namespace linear_queue
{
	template<typename T>
	struct linear_queue_t {
		T* p_data;

		int front;
		int back;

		size_t capacity;
	};

	template<typename T>
	linear_queue_t<T> create(const size_t capacity)
	{
		assert(capacity > 0);

		linear_queue_t<T> ret;
		ret.p_data = static_cast<T*>(malloc(sizeof(T) * capacity));

		ret.front = -1;
		ret.back = 0;

		ret.capacity = capacity;

		return ret;
	}

	template<typename T>
	void delete_linear_queue(linear_queue_t<T>* p_this)
	{
		assert(p_this != nullptr);

		free(p_this->p_data);
		p_this->p_data = nullptr;

		p_this->front = -1;
		p_this->back = -1;
	}

	template<typename T>
	bool is_empty(const linear_queue_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->front + 1 == p_this->back;
	}

	template<typename T>
	bool is_full(const linear_queue_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->back == p_this->capacity;
	}

	template<typename T>
	void enqueue(linear_queue_t<T>* p_this, const T value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		if (is_full(p_this)) {
			T* p_data = static_cast<T*>(malloc(sizeof(T) * p_this->capacity * 2));

			assert(p_data != nullptr);
			memcpy(p_data, p_this->p_data, sizeof(T) * p_this->capacity);

			free(p_this->p_data);

			p_this->capacity *= 2;
			p_this->p_data = p_data;
		}

		p_this->p_data[p_this->back++] = value;
	}

	template<typename T>
	T dequeue(linear_queue_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		return p_this->p_data[++p_this->front];
	}

	template<typename T>
	T peek(linear_queue_t<T>* p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		return p_this->p_data[p_this->front + 1];
	}
}