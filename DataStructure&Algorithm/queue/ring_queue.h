#pragma once

#include <cassert>
#include <cstdlib>

namespace ring_queue
{
	template<typename T>
	struct ring_queue_t {
		T* p_data;

		int front;
		int back;

		size_t capacity;
		size_t count;
	};

	template<typename T>
	ring_queue_t<T> create(const size_t capacity)
	{
		assert(capacity > 0);

		ring_queue_t<T> ret;
		ret.p_data = static_cast<T*>(malloc(sizeof(T) * capacity));

		ret.front = 0;
		ret.back = 0;

		ret.capacity = capacity;
		ret.count = 0;

		return ret;
	}

	template<typename T>
	void delete_ring_queue(ring_queue_t<T>* const p_this)
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
	bool is_empty(const ring_queue_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->count == 0;
	}

	template<typename T>
	bool is_full(const ring_queue_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->count == p_this->capacity;
	}

	template<typename T>
	void enqueue(ring_queue_t<T>* const p_this, const T value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		if (is_full(p_this)) {
			ring_queue_t<T> backup_this = *p_this;
			*p_this = create<T>(backup_this.capacity * 2);

			while (!is_empty(&backup_this)) {
				const int value = dequeue(&backup_this);
				enqueue(p_this, value);
			}

			delete_ring_queue(&backup_this);
		}

		p_this->p_data[p_this->back] = value;
		p_this->back = (p_this->back + 1) % p_this->capacity;

		++(p_this->count);
	}

	template<typename T>
	T dequeue(ring_queue_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		const int value = p_this->p_data[p_this->front];
		p_this->front = (p_this->front + 1) % p_this->capacity;

		--(p_this->count);

		return value;
	}

	template<typename T>
	T peek(const ring_queue_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		return p_this->p_data[p_this->front];
	}
}