#pragma once

#include <cassert>
#include <cstdlib>
#include <cstring>

namespace stack
{
	template<typename T>
	struct stack_t {
		T* p_data;

		size_t capacity;
		size_t top;
	};

	template<typename T>
	stack_t<T> create(const size_t capacity)
	{
		assert(capacity > 0);

		stack_t<T> result;
		result.p_data = static_cast<T*>(malloc(sizeof(T) * capacity));
		
		result.capacity = capacity;
		result.top = 0;

		return result;
	}

	template<typename T>
	void delete_stack(stack_t<T>* const p_this)
	{
		free(p_this->p_data);
		p_this->p_data = nullptr;

		p_this->top = 0;
		p_this->capacity = 0;
	}

	template<typename T>
	bool is_full(const stack_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->top == p_this->capacity;
	}

	template<typename T>
	bool is_empty(const stack_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		return p_this->top == 0;
	}

	template<typename T>
	void push(stack_t<T>* const p_this, const T value)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);

		if (is_full(p_this)) {
			T* p_data = static_cast<T*>(malloc(sizeof(T) * p_this->capacity * 2));

			assert(p_data != nullptr);
			memcpy(p_data, p_this->p_data, sizeof(T) * p_this->capacity);

			free(p_this->p_data);

			p_this->p_data = p_data;
			p_this->capacity *= 2;
		}

		p_this->p_data[(p_this->top)++] = value;
	}

	template<typename T>
	T pop(stack_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		T backup = p_this->p_data[p_this->top - 1];
		--(p_this->top);

		return backup;
	}

	template<typename T>
	T peek(const stack_t<T>* const p_this)
	{
		assert(p_this != nullptr);
		assert(p_this->p_data != nullptr);
		assert(!is_empty(p_this));

		return p_this->p_data[p_this->top - 1];
	}
}